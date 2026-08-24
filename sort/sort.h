#ifndef SORT_H
#define SORT_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Unless stated otherwise, length is the number of elements and must be
 * nonnegative. array must address at least length elements when length is
 * positive; a zero-length input is a no-op and may use a NULL pointer.
 */
void insertionSort(int array[], int length);
void binaryInsertionSort(int array[], int length);
void shellSort(int array[], int length);

void bubbleSort(int array[], int length);
void bubbleSort2(int array[], int length);
void cocktail(int array[], int length);

/*
 * Range endpoints are inclusive and must identify elements of array.
 * A range with left >= right is already sorted; an empty range may use NULL.
 */
void quickSort(int array[], int left, int right);
void quickSort2(int array[], int left, int right);
void quickSort3(int array[], int left, int right);

void selectionSort(int array[], int length);
void heapSort(int array[], int length);

/*
 * start and end are inclusive. tmp must be a separate buffer covering the
 * same valid indices whenever start < end. A range with start >= end is a
 * no-op and may use NULL pointers.
 */
void mergeSort(int array[], int tmp[], int start, int end);
void mergeSort2(int array[], int tmp[], int start, int end);

/*
 * sortedArray must address length elements and must not overlap array.
 * If allocation fails, or max(array)-min(array) cannot be represented by the
 * implementation's counting range, sortedArray is left unchanged.
 */
void countSort(int array[], int sortedArray[], int length);

/* On allocation failure, array is left unchanged. */
void bucketSort(int array[], int length);

/*
 * This LSD implementation accepts nonnegative integers only. If a negative
 * element is present or allocation fails, array is left unchanged.
 */
void radixSort(int array[], int length);

#ifdef __cplusplus
}
#endif

#endif
