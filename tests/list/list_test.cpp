#include "../../list/list.h"
#include "../../list/doubleLinkedList.h"
#include "../../list/circularLinkedList.h"

#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <vector>

#ifdef TEST_WRAP_MALLOC
extern "C" void *__real_malloc(std::size_t size);
extern "C" void *__wrap_malloc(std::size_t size);

static int allocationsBeforeFailure = -1;

extern "C" void *__wrap_malloc(std::size_t size) {
    if(allocationsBeforeFailure == 0) {
        return NULL;
    }
    if(allocationsBeforeFailure > 0) {
        allocationsBeforeFailure--;
    }
    return __real_malloc(size);
}
#endif

#ifdef TEST_WRAP_REALLOC
extern "C" void *__real_realloc(void *pointer, std::size_t size);
extern "C" void *__wrap_realloc(void *pointer, std::size_t size);

static bool failReallocation = false;

extern "C" void *__wrap_realloc(void *pointer, std::size_t size) {
    if(failReallocation) {
        return NULL;
    }
    return __real_realloc(pointer, size);
}
#endif

static int failures = 0;

#define CHECK(condition)                                                        \
    do {                                                                        \
        if(!(condition)) {                                                      \
            std::fprintf(stderr, "%s:%d: check failed: %s\n",                 \
                         __FILE__, __LINE__, #condition);                       \
            failures++;                                                        \
        }                                                                       \
    } while(0)

static void checkLinkedList(linkedList list, const int *values, int length) {
    CHECK(listLength(list) == length);
    for(int i = 0; i < length; i++) {
        int value = 0;
        CHECK(listGet(list, i + 1, &value) == 1);
        CHECK(value == values[i]);
    }
}

static void checkSequentialList(sqList list, const int *values, int length) {
    CHECK(listLength2(list) == length);
    for(int i = 0; i < length; i++) {
        int value = 0;
        CHECK(listGet2(list, i + 1, &value) == 1);
        CHECK(value == values[i]);
    }
}

static void checkCircularList(cLinkedList list, const int *values, int length) {
    CHECK(cListLength(list) == length);
    for(int i = 0; i < length; i++) {
        int value = 0;
        CHECK(cListGet(list, i + 1, &value) == 1);
        CHECK(value == values[i]);
    }
}

static void checkDoubleList(duLinkedList list, const int *values, int length) {
    CHECK(duListLength(list) == length);
    for(int i = 0; i < length; i++) {
        int value = 0;
        CHECK(duListGet(list, i + 1, &value) == 1);
        CHECK(value == values[i]);
    }
}

static void testLinkedListBoundariesAndDestroy(void) {
    linkedList list = NULL;
    CHECK(initList(&list) == 1);
    CHECK(listInsert(list, 0, 1) == 0);
    CHECK(listInsert(list, 1, 10) == 1);
    CHECK(listInsert(list, 2, 20) == 1);

    int value = 0;
    CHECK(listGet(list, 2, &value) == 1);
    CHECK(value == 20);
    CHECK(listGet(list, 0, &value) == 0);
    CHECK(listGet(list, 1, NULL) == 0);
    CHECK(listDelete(list, 0, &value) == 0);

    CHECK(destroyList(&list) == 1);
    CHECK(list == NULL);
    CHECK(destroyList(&list) == 1);
}

static void testSequentialDeleteAndAttachAliases(void) {
    sqList list = {NULL, 0, 0};
    CHECK(initList2(&list) == 1);
    CHECK(listInsert2(&list, 1, 10) == 1);
    int value = 0;
    CHECK(listDelete2(&list, 2, &value) == 0);
    CHECK(list.length == 1);
    CHECK(listDelete2(&list, 1, &value) == 1);
    CHECK(value == 10);
    CHECK(list.length == 0);
    CHECK(destroyList2(&list) == 1);

    int storage = 0;
    sqList fullRange = {&storage, INT_MAX, INT_MAX};
    CHECK(listInsert2(&fullRange, 1, 7) == 0);

#ifdef TEST_WRAP_REALLOC
    CHECK(initList2(&list) == 1);
    for(int i = 0; i < LIST_INIT_SIZE; i++) {
        CHECK(listInsert2(&list, i + 1, i) == 1);
    }
    dataType *originalBase = list.base;
    failReallocation = true;
    CHECK(listInsert2(&list, LIST_INIT_SIZE + 1, 100) == 0);
    failReallocation = false;
    CHECK(list.base == originalBase);
    CHECK(list.length == LIST_INIT_SIZE);
    CHECK(list.size == LIST_INIT_SIZE);
    CHECK(destroyList2(&list) == 1);
#endif

    sqList left = {NULL, 0, 0};
    sqList right = {NULL, 0, 0};
    CHECK(initList2(&left) == 1);
    CHECK(initList2(&right) == 1);
    for(int i = 0; i < LIST_INIT_SIZE; i++) {
        CHECK(listInsert2(&left, i + 1, i) == 1);
    }
    CHECK(listInsert2(&right, 1, 100) == 1);
    CHECK(listAttach2(left, right, &left) == 1);
    CHECK(left.length == LIST_INIT_SIZE + 1);
    for(int i = 0; i <= LIST_INIT_SIZE; i++) {
        CHECK(left.base[i] == i);
    }
    const int rightExpected[] = {100};
    checkSequentialList(right, rightExpected, 1);
    CHECK(destroyList2(&left) == 1);
    CHECK(destroyList2(&right) == 1);

    sqList first = {NULL, 0, 0};
    sqList second = {NULL, 0, 0};
    CHECK(initList2(&first) == 1);
    CHECK(initList2(&second) == 1);
    CHECK(listInsert2(&first, 1, 1) == 1);
    CHECK(listInsert2(&first, 2, 2) == 1);
    CHECK(listInsert2(&second, 1, 3) == 1);
    CHECK(listAttach2(first, second, &second) == 1);
    const int attached[] = {1, 2, 3};
    checkSequentialList(second, attached, 3);
    const int firstExpected[] = {1, 2};
    checkSequentialList(first, firstExpected, 2);
    CHECK(destroyList2(&first) == 1);
    CHECK(destroyList2(&second) == 1);

#ifdef TEST_WRAP_MALLOC
    CHECK(initList2(&first) == 1);
    CHECK(initList2(&second) == 1);
    CHECK(listInsert2(&first, 1, 7) == 1);
    CHECK(listInsert2(&second, 1, 8) == 1);
    dataType *firstBase = first.base;
    allocationsBeforeFailure = 0;
    CHECK(listAttach2(first, second, &first) == 0);
    allocationsBeforeFailure = -1;
    CHECK(first.base == firstBase);
    const int unchanged[] = {7};
    checkSequentialList(first, unchanged, 1);
    CHECK(destroyList2(&first) == 1);
    CHECK(destroyList2(&second) == 1);
#endif

    sqList emptyFirst = {NULL, 0, 0};
    sqList emptySecond = {NULL, 0, 0};
    sqList emptyResult = {NULL, 0, 0};
    CHECK(initList2(&emptyFirst) == 1);
    CHECK(initList2(&emptySecond) == 1);
    CHECK(initList2(&emptyResult) == 1);
    dataType *resultBase = emptyResult.base;
    int resultSize = emptyResult.size;
    CHECK(listAttach2(emptyFirst, emptySecond, &emptyResult) == 1);
    CHECK(emptyResult.base == resultBase);
    CHECK(emptyResult.size == resultSize);
    CHECK(emptyResult.length == 0);
    CHECK(listInsert2(&emptyResult, 1, 42) == 1);
    const int reused[] = {42};
    checkSequentialList(emptyResult, reused, 1);
    CHECK(destroyList2(&emptyFirst) == 1);
    CHECK(destroyList2(&emptySecond) == 1);
    CHECK(destroyList2(&emptyResult) == 1);
}

static void testLinkedAttachCopiesInputs(void) {
    linkedList first = NULL;
    linkedList second = NULL;
    linkedList result = NULL;
    CHECK(initList(&first) == 1);
    CHECK(initList(&second) == 1);
    CHECK(listInsert(first, 1, 1) == 1);
    CHECK(listInsert(first, 2, 2) == 1);
    CHECK(listInsert(second, 1, 3) == 1);
    CHECK(listAttach(first, second, &result) == 1);

    const int expected[] = {1, 2, 3};
    checkLinkedList(result, expected, 3);
    first->next->data = 11;
    second->next->data = 33;
    checkLinkedList(result, expected, 3);

    CHECK(destroyList(&first) == 1);
    CHECK(destroyList(&second) == 1);
    CHECK(destroyList(&result) == 1);

#ifdef TEST_WRAP_MALLOC
    first = NULL;
    second = NULL;
    result = NULL;
    CHECK(initList(&first) == 1);
    CHECK(initList(&second) == 1);
    CHECK(listInsert(first, 1, 1) == 1);
    CHECK(listInsert(first, 2, 2) == 1);
    allocationsBeforeFailure = 2;
    CHECK(listAttach(first, second, &result) == 0);
    allocationsBeforeFailure = -1;
    CHECK(result == NULL);
    CHECK(destroyList(&first) == 1);
    CHECK(destroyList(&second) == 1);
#endif
}

static void testDoubleListBoundariesAndTailDelete(void) {
    duLinkedList list = NULL;
    CHECK(initDuList(&list) == 1);
    CHECK(duListInsert(list, 0, 1) == 0);
    CHECK(duListInsert(list, 1, 10) == 1);
    CHECK(duListInsert(list, 2, 20) == 1);

    int value = 0;
    CHECK(duListGet(list, 2, &value) == 1);
    CHECK(value == 20);
    CHECK(duListDelete(list, 0, &value) == 0);
    CHECK(duListDelete(list, 2, &value) == 1);
    CHECK(value == 20);
    CHECK(list->next->next == NULL);

    CHECK(destroyDuList(&list) == 1);
    CHECK(destroyDuList(&list) == 1);
}

static void testCircularAttachCopiesInputs(void) {
    cLinkedList first = NULL;
    cLinkedList second = NULL;
    cLinkedList result = NULL;
    CHECK(initCList(&first) == 1);
    CHECK(initCList(&second) == 1);
    CHECK(cListInsert(&first, 1, 1) == 1);
    CHECK(cListInsert(&first, 2, 2) == 1);
    CHECK(cListInsert(&second, 1, 3) == 1);

    CHECK(cListAttach(first, second, &result) == 1);
    const int expected[] = {1, 2, 3};
    checkCircularList(result, expected, 3);
    first->next->next->data = 11;
    second->next->next->data = 33;
    checkCircularList(result, expected, 3);

    CHECK(destroyCList(&first) == 1);
    CHECK(destroyCList(&second) == 1);
    CHECK(destroyCList(&result) == 1);
    CHECK(destroyCList(&result) == 1);

    first = NULL;
    second = NULL;
    result = NULL;
    CHECK(initCList(&first) == 1);
    CHECK(initCList(&second) == 1);
    CHECK(cListInsert(&first, 1, 4) == 1);
    CHECK(cListAttach(first, second, &result) == 1);
    const int emptySecondExpected[] = {4};
    checkCircularList(result, emptySecondExpected, 1);
    CHECK(destroyCList(&first) == 1);
    CHECK(destroyCList(&second) == 1);
    CHECK(destroyCList(&result) == 1);
}

static void testListSortKeepsTheSentinel(void) {
    linkedList empty = NULL;
    CHECK(initList(&empty) == 1);
    linkedList emptySentinel = empty;
    CHECK(listSort(empty) == emptySentinel);
    CHECK(destroyList(&empty) == 1);

    linkedList list = NULL;
    CHECK(initList(&list) == 1);
    const int input[] = {4, 1, 3, 1, 2};
    for(int i = 0; i < 5; i++) {
        CHECK(listInsert(list, i + 1, input[i]) == 1);
    }
    linkedList sentinel = list;
#ifdef TEST_WRAP_MALLOC
    allocationsBeforeFailure = 0;
#endif
    linkedList sorted = listSort(list);
#ifdef TEST_WRAP_MALLOC
    allocationsBeforeFailure = -1;
#endif
    CHECK(sorted == sentinel);
    const int expected[] = {1, 1, 2, 3, 4};
    checkLinkedList(sorted, expected, 5);
    CHECK(destroyList(&sorted) == 1);

    std::uint32_t state = 0x12345678u;
    for(int testCase = 0; testCase < 200; testCase++) {
        linkedList randomList = NULL;
        CHECK(initList(&randomList) == 1);
        state = state * 1664525u + 1013904223u;
        int length = static_cast<int>(state % 65u);
        std::vector<int> values;
        for(int i = 0; i < length; i++) {
            state = state * 1664525u + 1013904223u;
            int value = static_cast<int>(state % 21u) - 10;
            values.push_back(value);
            CHECK(listInsert(randomList, i + 1, value) == 1);
        }
        std::sort(values.begin(), values.end());
        linkedList randomSentinel = randomList;
        CHECK(listSort(randomList) == randomSentinel);
        checkLinkedList(randomList, values.data(), length);
        CHECK(destroyList(&randomList) == 1);
    }
}

static void testReverseVariants(void) {
    linkedList linked = NULL;
    sqList sequential = {NULL, 0, 0};
    CHECK(initList(&linked) == 1);
    CHECK(initList2(&sequential) == 1);
    const int values[] = {1, 2, 3, 4, 5};
    for(int i = 0; i < 5; i++) {
        CHECK(listInsert(linked, i + 1, values[i]) == 1);
        CHECK(listInsert2(&sequential, i + 1, values[i]) == 1);
    }
    CHECK(listReverse(linked) == 1);
    CHECK(listReverse2(sequential) == 1);
    const int expected[] = {5, 4, 3, 2, 1};
    checkLinkedList(linked, expected, 5);
    checkSequentialList(sequential, expected, 5);
    CHECK(destroyList(&linked) == 1);
    CHECK(destroyList2(&sequential) == 1);
}

static void testListVariantsAgainstStateModel(void) {
    linkedList linked = NULL;
    sqList sequential = {NULL, 0, 0};
    duLinkedList doubled = NULL;
    cLinkedList circular = NULL;
    std::vector<int> model;
    CHECK(initList(&linked) == 1);
    CHECK(initList2(&sequential) == 1);
    CHECK(initDuList(&doubled) == 1);
    CHECK(initCList(&circular) == 1);

    std::uint32_t state = 0x9e3779b9u;
    for(int step = 0; step < 1000; step++) {
        state = state * 1664525u + 1013904223u;
        const int operation = (int)(state % 4u);
        const bool useValidPosition = ((state >> 8) % 4u) != 0u;
        if(operation == 0) {
            int pos = useValidPosition
                ? 1 + (int)((state >> 12) % (model.size() + 1u))
                : ((state >> 16) & 1u ? 0 : (int)model.size() + 2);
            const int value = (int)((state >> 20) % 201u) - 100;
            const int expectedStatus = useValidPosition ? 1 : 0;
            CHECK(listInsert(linked, pos, value) == expectedStatus);
            CHECK(listInsert2(&sequential, pos, value) == expectedStatus);
            CHECK(duListInsert(doubled, pos, value) == expectedStatus);
            CHECK(cListInsert(&circular, pos, value) == expectedStatus);
            if(expectedStatus) {
                model.insert(model.begin() + pos - 1, value);
            }
        } else if(operation == 1) {
            const bool valid = useValidPosition && !model.empty();
            int pos = valid
                ? 1 + (int)((state >> 12) % model.size())
                : ((state >> 16) & 1u ? 0 : (int)model.size() + 1);
            int linkedValue = 12345;
            int sequentialValue = 12345;
            int doubleValue = 12345;
            int circularValue = 12345;
            const int expectedStatus = valid ? 1 : 0;
            CHECK(listDelete(linked, pos, &linkedValue) == expectedStatus);
            CHECK(listDelete2(&sequential, pos, &sequentialValue) == expectedStatus);
            CHECK(duListDelete(doubled, pos, &doubleValue) == expectedStatus);
            CHECK(cListDelete(&circular, pos, &circularValue) == expectedStatus);
            if(expectedStatus) {
                const int expectedValue = model[pos - 1];
                CHECK(linkedValue == expectedValue);
                CHECK(sequentialValue == expectedValue);
                CHECK(doubleValue == expectedValue);
                CHECK(circularValue == expectedValue);
                model.erase(model.begin() + pos - 1);
            }
        } else if(operation == 2) {
            const bool valid = useValidPosition && !model.empty();
            int pos = valid
                ? 1 + (int)((state >> 12) % model.size())
                : ((state >> 16) & 1u ? 0 : (int)model.size() + 1);
            int linkedValue = 12345;
            int sequentialValue = 12345;
            int doubleValue = 12345;
            int circularValue = 12345;
            const int expectedStatus = valid ? 1 : 0;
            CHECK(listGet(linked, pos, &linkedValue) == expectedStatus);
            CHECK(listGet2(sequential, pos, &sequentialValue) == expectedStatus);
            CHECK(duListGet(doubled, pos, &doubleValue) == expectedStatus);
            CHECK(cListGet(circular, pos, &circularValue) == expectedStatus);
            if(expectedStatus) {
                CHECK(linkedValue == model[pos - 1]);
                CHECK(sequentialValue == model[pos - 1]);
                CHECK(doubleValue == model[pos - 1]);
                CHECK(circularValue == model[pos - 1]);
            }
        } else {
            CHECK(clearList(linked) == 1);
            clearList2(&sequential);
            CHECK(clearDuList(doubled) == 1);
            CHECK(clearCList(circular) == 1);
            model.clear();
        }

        checkLinkedList(linked, model.data(), (int)model.size());
        checkSequentialList(sequential, model.data(), (int)model.size());
        checkDoubleList(doubled, model.data(), (int)model.size());
        checkCircularList(circular, model.data(), (int)model.size());
    }

    CHECK(destroyList(&linked) == 1);
    CHECK(destroyList2(&sequential) == 1);
    CHECK(destroyDuList(&doubled) == 1);
    CHECK(destroyCList(&circular) == 1);
}

int main(void) {
    testLinkedListBoundariesAndDestroy();
    testSequentialDeleteAndAttachAliases();
    testLinkedAttachCopiesInputs();
    testDoubleListBoundariesAndTailDelete();
    testCircularAttachCopiesInputs();
    testListSortKeepsTheSentinel();
    testReverseVariants();
    testListVariantsAgainstStateModel();

    if(failures != 0) {
        std::fprintf(stderr, "%d list checks failed\n", failures);
        return 1;
    }
    return 0;
}
