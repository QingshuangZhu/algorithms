#include "../../heap/heap.h"

#include <cstdlib>

#define CHECK(condition) do { if (!(condition)) return __LINE__; } while (0)

int main(int argc, char **argv) {
    if (argc != 2) {
        return 64;
    }

    const int scenario = std::atoi(argv[1]);
    if (scenario == 0) {
        downAdjust(NULL, 1, 0);
        return 0;
    }
    if (scenario == 1) {
        int value = 7;
        downAdjust(&value, 0, 0);
        CHECK(value == 7);
        downAdjust(&value, -1, 0);
        CHECK(value == 7);
        return 0;
    }
    if (scenario == 2) {
        int value = 7;
        downAdjust(&value, 1, -1);
        CHECK(value == 7);
        return 0;
    }
    if (scenario == 3) {
        int value = 7;
        downAdjust(&value, 1, 1);
        CHECK(value == 7);
        return 0;
    }
    if (scenario == 4) {
        int values[] = {5, 2, 3, 4};
        downAdjust(values, 4, 0);
        const int expected[] = {2, 4, 3, 5};
        for (int i = 0; i < 4; ++i) {
            CHECK(values[i] == expected[i]);
        }
        return 0;
    }
    if (scenario == 5) {
        int values[] = {1, 2, 3};
        downAdjust(values, 3, 2);
        CHECK(values[0] == 1);
        CHECK(values[1] == 2);
        CHECK(values[2] == 3);
        return 0;
    }
    if (scenario == 6) {
        upAdjust(NULL, 2, 1);
        return 0;
    }
    if (scenario == 7) {
        buildHeap(NULL, -2147483647 - 1);
        return 0;
    }
    if (scenario == 8) {
        int values[] = {1, 3, 2, 7, 6, 5, 0};
        upAdjust(values, 7, 6);
        const int expected[] = {0, 3, 1, 7, 6, 5, 2};
        for (int i = 0; i < 7; ++i) {
            CHECK(values[i] == expected[i]);
        }
        return 0;
    }
    if (scenario == 9) {
        int values[] = {5, 4, 3, 2, 1, 0};
        buildHeap(values, 6);
        for (int child = 1; child < 6; ++child) {
            CHECK(values[(child - 1) / 2] <= values[child]);
        }
        return 0;
    }
    return 65;
}
