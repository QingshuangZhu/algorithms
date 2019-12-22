#ifndef SORT_H
#define SORT_H

#ifdef __cplusplus
extern "C" {
#endif

void insertionSort(int array[], int length);
void binaryInsertionSort(int array[], int length);
void shellSort(int array[], int length);

void bubbleSort(int array[], int length);
void bubbleSort2(int array[], int length);
void cocktail(int array[], int length);
void quickSort(int array[], int left, int right);
void quickSort2(int array[], int left, int right);
void quickSort3(int array[], int left, int right);

void selectionSort(int array[], int length);
void heapSort(int array[], int length);

void mergeSort(int array[], int tmp[], int start, int end);
void mergeSort2(int array[], int tmp[], int start, int end);

void countSort(int array[], int sortedArray[], int length);

void bucketSort(int array[], int length);

#ifdef __cplusplus
}
#endif

#endif