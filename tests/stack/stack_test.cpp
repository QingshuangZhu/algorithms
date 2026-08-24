#include "../../stack/stack.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <vector>

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

static void testSequentialStackPreservesAllocationOnFailure(void) {
    sqStack stack = {NULL, NULL, 0};
    CHECK(initStack(&stack) == 1);
    for(int i = 0; i < STACK_INIT_SIZE; i++) {
        CHECK(push(&stack, i) == 1);
    }
    dataType *bottom = stack.bottom;
    dataType *topPointer = stack.top;
    int size = stack.size;

#ifdef TEST_WRAP_REALLOC
    failReallocation = true;
#endif
    CHECK(push(&stack, STACK_INIT_SIZE) == 0);
#ifdef TEST_WRAP_REALLOC
    failReallocation = false;
#endif
    CHECK(stack.bottom == bottom);
    CHECK(stack.top == topPointer);
    CHECK(stack.size == size);

    if(stack.bottom == bottom && stack.top == topPointer) {
        int value = 0;
        CHECK(push(&stack, STACK_INIT_SIZE) == 1);
        CHECK(stackHeight(&stack) == STACK_INIT_SIZE + 1);
        for(int i = STACK_INIT_SIZE; i >= 0; i--) {
            CHECK(pop(&stack, &value) == 1);
            CHECK(value == i);
        }
        CHECK(destroyStack(&stack) == 1);
        CHECK(stackEmpty(&stack) == 1);
        CHECK(stackHeight(&stack) == 0);
    }
    CHECK(stackEmpty(NULL) == 1);
    CHECK(stackHeight(NULL) == 0);
}

static void testLinkedStackClearAndReuse(void) {
    linkedStack stack = {NULL, NULL, 0};
    CHECK(initStack2(&stack) == 1);
    CHECK(push2(&stack, 1) == 1);
    CHECK(push2(&stack, 2) == 1);
    CHECK(push2(&stack, 3) == 1);
    CHECK(clearStack2(&stack) == 1);
    CHECK(stackEmpty2(&stack) == 1);
    CHECK(stackHeight2(&stack) == 0);

    int value = 0;
    CHECK(top2(&stack, &value) == 0);
    CHECK(top2(&stack, NULL) == 0);
    CHECK(pop2(&stack, &value) == 0);
    CHECK(push2(&stack, 4) == 1);
    CHECK(top2(&stack, &value) == 1);
    CHECK(value == 4);
    CHECK(pop2(&stack, &value) == 1);
    CHECK(value == 4);
    CHECK(destroyStack2(&stack) == 1);
    CHECK(stackEmpty2(&stack) == 1);
    CHECK(stackHeight2(&stack) == 0);
    CHECK(stackEmpty2(NULL) == 1);
    CHECK(stackHeight2(NULL) == 0);
}

static void testStacksAgainstStateModel(void) {
    sqStack sequential = {NULL, NULL, 0};
    linkedStack linked = {NULL, NULL, 0};
    std::vector<int> model;
    CHECK(initStack(&sequential) == 1);
    CHECK(initStack2(&linked) == 1);

    std::uint32_t state = 0x27182818u;
    for(int step = 0; step < 2000; step++) {
        state = state * 1664525u + 1013904223u;
        const int operation = (int)(state % 5u);
        if(operation <= 1) {
            const int value = (int)(state % 201u) - 100;
            CHECK(push(&sequential, value) == 1);
            CHECK(push2(&linked, value) == 1);
            model.push_back(value);
        } else if(operation == 2) {
            int sequentialValue = 12345;
            int linkedValue = 12345;
            const int expectedStatus = model.empty() ? 0 : 1;
            CHECK(pop(&sequential, &sequentialValue) == expectedStatus);
            CHECK(pop2(&linked, &linkedValue) == expectedStatus);
            if(expectedStatus) {
                CHECK(sequentialValue == model.back());
                CHECK(linkedValue == model.back());
                model.pop_back();
            }
        } else if(operation == 3) {
            int sequentialValue = 12345;
            int linkedValue = 12345;
            const int expectedStatus = model.empty() ? 0 : 1;
            CHECK(top(&sequential, &sequentialValue) == expectedStatus);
            CHECK(top2(&linked, &linkedValue) == expectedStatus);
            if(expectedStatus) {
                CHECK(sequentialValue == model.back());
                CHECK(linkedValue == model.back());
            }
        } else {
            CHECK(clearStack(&sequential) == 1);
            CHECK(clearStack2(&linked) == 1);
            model.clear();
        }
        CHECK(stackHeight(&sequential) == (int)model.size());
        CHECK(stackHeight2(&linked) == (int)model.size());
        CHECK(stackEmpty(&sequential) == (model.empty() ? 1 : 0));
        CHECK(stackEmpty2(&linked) == (model.empty() ? 1 : 0));
    }

    CHECK(destroyStack(&sequential) == 1);
    CHECK(destroyStack2(&linked) == 1);
}

int main(void) {
    testSequentialStackPreservesAllocationOnFailure();
    testLinkedStackClearAndReuse();
    testStacksAgainstStateModel();
    if(failures != 0) {
        std::fprintf(stderr, "%d stack checks failed\n", failures);
        return 1;
    }
    return 0;
}
