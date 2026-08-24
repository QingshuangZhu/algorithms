#include "../../queue/queue.h"
#include "../../queue/circularQueue.h"

#include <cstdint>
#include <cstdio>
#include <deque>

static int failures = 0;

#define CHECK(condition)                                                        \
    do {                                                                        \
        if(!(condition)) {                                                      \
            std::fprintf(stderr, "%s:%d: check failed: %s\n",                 \
                         __FILE__, __LINE__, #condition);                       \
            failures++;                                                        \
        }                                                                       \
    } while(0)

static void testLinkedQueue(void) {
    CHECK(initQueue(NULL) == 0);

    linkedQueue queue = {NULL, NULL, 0};
    CHECK(initQueue(&queue) == 1);
    CHECK(queueEmpty(&queue) == 1);
    CHECK(queueLength(&queue) == 0);

    int value = 0;
    CHECK(getHead(&queue, &value) == 0);
    CHECK(getHead(&queue, NULL) == 0);
    CHECK(enQueue(&queue, 10) == 1);
    CHECK(enQueue(&queue, 20) == 1);
    CHECK(getHead(&queue, &value) == 1);
    CHECK(value == 10);
    CHECK(deQueue(&queue, &value) == 1);
    CHECK(value == 10);
    CHECK(clearQueue(&queue) == 1);
    CHECK(queueEmpty(&queue) == 1);
    CHECK(enQueue(&queue, 30) == 1);
    CHECK(deQueue(&queue, &value) == 1);
    CHECK(value == 30);
    CHECK(destroyQueue(&queue) == 1);
    CHECK(destroyQueue(&queue) == 1);
}

static void testCircularQueue(void) {
    sqQueue queue = {NULL, 0, 0};
    CHECK(initCQueue(&queue) == 1);

    int value = 0;
    CHECK(getCHead(&queue, &value) == 0);
    CHECK(getCHead(&queue, NULL) == 0);
    for(int i = 0; i < MAXQSIZE - 1; i++) {
        CHECK(enCQueue(&queue, i) == 1);
    }
    CHECK(enCQueue(&queue, MAXQSIZE) == 0);
    for(int i = 0; i < 50; i++) {
        CHECK(deCQueue(&queue, &value) == 1);
        CHECK(value == i);
    }
    for(int i = 0; i < 50; i++) {
        CHECK(enCQueue(&queue, 100 + i) == 1);
    }
    CHECK(getCHead(&queue, &value) == 1);
    CHECK(value == 50);
    CHECK(cQueueLength(&queue) == MAXQSIZE - 1);
    CHECK(clearCQueue(&queue) == 1);
    CHECK(cQueueEmpty(&queue) == 1);
    CHECK(destroyCQueue(&queue) == 1);
    CHECK(destroyCQueue(&queue) == 1);
}

static void testQueuesAgainstStateModel(void) {
    linkedQueue linked = {NULL, NULL, 0};
    sqQueue circular = {NULL, 0, 0};
    std::deque<int> model;
    CHECK(initQueue(&linked) == 1);
    CHECK(initCQueue(&circular) == 1);

    std::uint32_t state = 0x31415926u;
    for(int step = 0; step < 2000; step++) {
        state = state * 1664525u + 1013904223u;
        const int operation = (int)(state % 5u);
        if(operation <= 1 && model.size() < MAXQSIZE - 1u) {
            const int value = (int)(state % 201u) - 100;
            CHECK(enQueue(&linked, value) == 1);
            CHECK(enCQueue(&circular, value) == 1);
            model.push_back(value);
        } else if(operation == 2) {
            int linkedValue = 12345;
            int circularValue = 12345;
            const int expectedStatus = model.empty() ? 0 : 1;
            CHECK(deQueue(&linked, &linkedValue) == expectedStatus);
            CHECK(deCQueue(&circular, &circularValue) == expectedStatus);
            if(expectedStatus) {
                CHECK(linkedValue == model.front());
                CHECK(circularValue == model.front());
                model.pop_front();
            }
        } else if(operation == 3) {
            int linkedValue = 12345;
            int circularValue = 12345;
            const int expectedStatus = model.empty() ? 0 : 1;
            CHECK(getHead(&linked, &linkedValue) == expectedStatus);
            CHECK(getCHead(&circular, &circularValue) == expectedStatus);
            if(expectedStatus) {
                CHECK(linkedValue == model.front());
                CHECK(circularValue == model.front());
            }
        } else if(operation == 4) {
            CHECK(clearQueue(&linked) == 1);
            CHECK(clearCQueue(&circular) == 1);
            model.clear();
        }
        CHECK(queueLength(&linked) == (int)model.size());
        CHECK(cQueueLength(&circular) == (int)model.size());
        CHECK(queueEmpty(&linked) == (model.empty() ? 1 : 0));
        CHECK(cQueueEmpty(&circular) == (model.empty() ? 1 : 0));
    }

    CHECK(destroyQueue(&linked) == 1);
    CHECK(destroyCQueue(&circular) == 1);
}

int main(void) {
    testLinkedQueue();
    testCircularQueue();
    testQueuesAgainstStateModel();
    if(failures != 0) {
        std::fprintf(stderr, "%d queue checks failed\n", failures);
        return 1;
    }
    return 0;
}
