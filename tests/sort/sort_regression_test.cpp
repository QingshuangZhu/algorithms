#include "../../sort/sort.h"

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstddef>
#include <random>
#include <vector>

extern "C" void *__real_malloc(std::size_t size);
extern "C" void *__real_calloc(std::size_t count, std::size_t size);
extern "C" void *__wrap_malloc(std::size_t size);
extern "C" void *__wrap_calloc(std::size_t count, std::size_t size);

static int mallocSuccessesBeforeFailure = -1;
static int callocSuccessesBeforeFailure = -1;

extern "C" void *__wrap_malloc(std::size_t size) {
    if (mallocSuccessesBeforeFailure == 0) {
        mallocSuccessesBeforeFailure = -1;
        return NULL;
    }
    if (mallocSuccessesBeforeFailure > 0) {
        --mallocSuccessesBeforeFailure;
    }
    return __real_malloc(size);
}

extern "C" void *__wrap_calloc(std::size_t count, std::size_t size) {
    if (callocSuccessesBeforeFailure == 0) {
        callocSuccessesBeforeFailure = -1;
        return NULL;
    }
    if (callocSuccessesBeforeFailure > 0) {
        --callocSuccessesBeforeFailure;
    }
    return __real_calloc(count, size);
}

static void expectEqual(const int actual[], const int expected[], int length) {
    assert(std::equal(actual, actual + length, expected));
}

static void testInsertionSortMinimumMovesToFront() {
    int values[] = {2, 1};
    const int expected[] = {1, 2};

    insertionSort(values, 2);

    expectEqual(values, expected, 2);
}

static void testRecursiveQuickSortsHandleEmptySubranges() {
    int first[] = {2, 1};
    int second[] = {2, 1};
    const int expected[] = {1, 2};

    quickSort(first, 0, 1);
    quickSort2(second, 0, 1);

    expectEqual(first, expected, 2);
    expectEqual(second, expected, 2);

    quickSort(NULL, 0, -1);
    quickSort2(NULL, 0, -1);
}

static void testQuickSort3HandlesEmptyRange() {
    quickSort3(NULL, 0, -1);
}

static void testMergeSort2RunsFinalMergePass() {
    int pair[] = {2, 1};
    int pairTmp[2] = {0};
    const int pairExpected[] = {1, 2};
    int values[] = {4, 3, 2, 1};
    int tmp[4] = {0};
    const int expected[] = {1, 2, 3, 4};
    int subrange[] = {9, 4, 3, 2, 1, 8};
    int subrangeTmp[6] = {0};
    const int subrangeExpected[] = {9, 1, 2, 3, 4, 8};

    mergeSort2(pair, pairTmp, 0, 1);
    mergeSort2(values, tmp, 0, 3);
    mergeSort2(subrange, subrangeTmp, 1, 4);
    mergeSort2(NULL, NULL, 0, -1);

    expectEqual(pair, pairExpected, 2);
    expectEqual(values, expected, 4);
    expectEqual(subrange, subrangeExpected, 6);
}

static void testBucketSortBoundaryInputs() {
    bucketSort(NULL, 0);

    int equalValues[] = {5, 5, 5};
    const int equalExpected[] = {5, 5, 5};
    bucketSort(equalValues, 3);
    expectEqual(equalValues, equalExpected, 3);

    int sparseBuckets[] = {0, 0, 1};
    const int sparseExpected[] = {0, 0, 1};
    bucketSort(sparseBuckets, 3);
    expectEqual(sparseBuckets, sparseExpected, 3);

    int extremeValues[] = {INT_MAX, 0, INT_MIN};
    const int extremeExpected[] = {INT_MIN, 0, INT_MAX};
    bucketSort(extremeValues, 3);
    expectEqual(extremeValues, extremeExpected, 3);
}

static void testBucketSortAllocationFailuresLeaveInputUnchanged() {
    int firstAllocation[] = {3, 1, 2};
    const int firstExpected[] = {3, 1, 2};
    mallocSuccessesBeforeFailure = 0;
    bucketSort(firstAllocation, 3);
    expectEqual(firstAllocation, firstExpected, 3);

    int partialConstruction[] = {3, 1, 2};
    const int partialExpected[] = {3, 1, 2};
    mallocSuccessesBeforeFailure = 2;
    bucketSort(partialConstruction, 3);
    expectEqual(partialConstruction, partialExpected, 3);

    int partialInsertion[] = {3, 1, 2};
    const int insertionExpected[] = {3, 1, 2};
    mallocSuccessesBeforeFailure = 5;
    bucketSort(partialInsertion, 3);
    expectEqual(partialInsertion, insertionExpected, 3);
}

static void testCountSortBoundaryAndAllocationFailure() {
    countSort(NULL, NULL, 0);

    int values[] = {3, -1, 3, 0};
    int sorted[4] = {0};
    const int expected[] = {-1, 0, 3, 3};
    countSort(values, sorted, 4);
    expectEqual(sorted, expected, 4);

    int extremes[] = {INT_MAX, INT_MIN};
    int unchanged[] = {11, 22};
    const int unchangedExpected[] = {11, 22};
    countSort(extremes, unchanged, 2);
    expectEqual(unchanged, unchangedExpected, 2);

    int allocationInput[] = {2, 1};
    int allocationOutput[] = {7, 8};
    const int allocationExpected[] = {7, 8};
    callocSuccessesBeforeFailure = 0;
    countSort(allocationInput, allocationOutput, 2);
    expectEqual(allocationOutput, allocationExpected, 2);
}

static void testRadixSortBoundaryAndAllocationFailure() {
    radixSort(NULL, 0);

    int values[] = {INT_MAX, 10, 0, 1};
    const int expected[] = {0, 1, 10, INT_MAX};
    radixSort(values, 4);
    expectEqual(values, expected, 4);

    int negative[] = {2, -1, 0};
    const int negativeExpected[] = {2, -1, 0};
    radixSort(negative, 3);
    expectEqual(negative, negativeExpected, 3);

    int allocationInput[] = {2, 1};
    const int allocationExpected[] = {2, 1};
    mallocSuccessesBeforeFailure = 0;
    radixSort(allocationInput, 2);
    expectEqual(allocationInput, allocationExpected, 2);
}

typedef void (*LengthSortFunction)(int *, int);

static void verifyComparisonSorts(const std::vector<int>& input) {
    std::vector<int> expected(input);
    std::sort(expected.begin(), expected.end());

    LengthSortFunction lengthSorts[] = {
        insertionSort, binaryInsertionSort, shellSort,
        bubbleSort, bubbleSort2, cocktail,
        selectionSort, heapSort, bucketSort
    };
    for(std::size_t i = 0; i < sizeof(lengthSorts)/sizeof(lengthSorts[0]); i++){
        std::vector<int> actual(input);
        lengthSorts[i](actual.data(), (int)actual.size());
        assert(actual == expected);
    }

    typedef void (*RangeSortFunction)(int *, int, int);
    RangeSortFunction rangeSorts[] = {quickSort, quickSort2, quickSort3};
    for(std::size_t i = 0; i < sizeof(rangeSorts)/sizeof(rangeSorts[0]); i++){
        std::vector<int> actual(input);
        rangeSorts[i](actual.data(), 0, (int)actual.size() - 1);
        assert(actual == expected);
    }

    typedef void (*MergeSortFunction)(int *, int *, int, int);
    MergeSortFunction mergeSorts[] = {mergeSort, mergeSort2};
    for(std::size_t i = 0; i < sizeof(mergeSorts)/sizeof(mergeSorts[0]); i++){
        std::vector<int> actual(input);
        std::vector<int> tmp(input.size());
        mergeSorts[i](actual.data(), tmp.data(), 0, (int)actual.size() - 1);
        assert(actual == expected);
    }
}

static void testAllSortVariantsAgainstStandardOracle() {
    std::mt19937 generator(20260824);
    std::uniform_int_distribution<int> signedValues(-20, 20);
    std::uniform_int_distribution<int> nonnegativeValues(0, INT_MAX);

    const int extremeData[] = {INT_MAX, 0, INT_MIN, INT_MAX, -1};
    verifyComparisonSorts(std::vector<int>(
        extremeData, extremeData + sizeof(extremeData)/sizeof(extremeData[0])));
    verifyComparisonSorts(std::vector<int>());
    verifyComparisonSorts(std::vector<int>(1, 7));
    verifyComparisonSorts(std::vector<int>(8, 3));

    for(int round = 0; round < 200; round++){
        int length = round % 33;
        std::vector<int> input(length);
        for(int i = 0; i < length; i++){
            input[i] = signedValues(generator);
        }
        verifyComparisonSorts(input);

        std::vector<int> counted(length);
        std::vector<int> expected(input);
        std::sort(expected.begin(), expected.end());
        countSort(input.data(), counted.data(), length);
        assert(counted == expected);

        std::vector<int> radixInput(length);
        for(int i = 0; i < length; i++){
            radixInput[i] = nonnegativeValues(generator);
        }
        std::vector<int> radixExpected(radixInput);
        std::sort(radixExpected.begin(), radixExpected.end());
        radixSort(radixInput.data(), length);
        assert(radixInput == radixExpected);
    }
}

int main() {
    testInsertionSortMinimumMovesToFront();
    testRecursiveQuickSortsHandleEmptySubranges();
    testQuickSort3HandlesEmptyRange();
    testMergeSort2RunsFinalMergePass();
    testBucketSortBoundaryInputs();
    testBucketSortAllocationFailuresLeaveInputUnchanged();
    testCountSortBoundaryAndAllocationFailure();
    testRadixSortBoundaryAndAllocationFailure();
    testAllSortVariantsAgainstStandardOracle();
    return 0;
}
