/*
 * heap
 */

#include "heap.h"

/* 向上调整 */
void upAdjust(int array[], int length, int index) {
    if(!array || length <= 0 || index < 1 || index >= length){
        return;
    }
    int parentIndex = (index - 1)/2;
    int tmp = array[index];    /* 孩子结点的值 */
    while(index > 0 && tmp < array[parentIndex]){    /* 最小堆 */
        array[index] = array[parentIndex];
        index = parentIndex;
        parentIndex = (parentIndex - 1)/2;
    }
    array[index] = tmp;
}

/* 向下调整 */
void downAdjust(int array[], int length, int index) {
    if(!array || length <= 0 || index < 0 || index >= length){
        return;
    }

    int tmp = array[index];    /* 父结点的值 */
    while(index < length/2) {
        int childIndex = 2*index + 1;
        /* 如果有右孩子，且右孩子小于左孩子的值，则定位到右孩子 */
        if(childIndex + 1 < length && array[childIndex+1] < array[childIndex]){
            childIndex++;
        }
        /* 父结点小于任何一个孩子的值，则直接退出 */
        if(tmp < array[childIndex]){    /* 最小堆 */
            break;
        }

        array[index] = array[childIndex];
        index = childIndex;
    }
    array[index] = tmp;
}

/* 构建堆 */
void buildHeap(int array[], int length) {
    if(!array || length <= 1){
        return;
    }

    /* 从最后一个非叶子结点开始，向下调整 */
    for(int i = (length - 2)/2; i >=0; i--){
        downAdjust(array, length, i);
    }
}
