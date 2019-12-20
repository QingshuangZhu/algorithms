/*
 * heap sort
 */

#include "sort.h"

/* 向下调整 */
void downAdjust(int array[], int length, int index) {
    int tmp = array[index];    /* 父结点的值 */
    int childIndex = 2*index + 1;

    while(childIndex < length){
        /* 如果有右孩子，且右孩子大于左孩子，则定位到右孩子 */
        if(childIndex + 1 < length && array[childIndex+1] > array[childIndex]){
            childIndex++;
        }
        
        /* 如果父结点大于任何一个孩子的值，则直接跳出 */
        if(tmp > array[childIndex]){    /* 最大堆 */
            break;
        }

        array[index] = array[childIndex];
        index = childIndex;
        childIndex = 2*index + 1;
    }
    array[index] = tmp;
}

 void heapSort(int array[], int length){
     /* 把无序数组构建成最大堆 */
     for(int i = (length - 2)/2; i >= 0; i--){
         downAdjust(array, length, i);
     }

     /* 循环删除堆顶元素，替换到二叉堆的末尾，调整堆产生新的堆顶 */
     for(int i = length - 1; i > 0; i--){
         int tmp = array[i];
         array[i] = array[0];
         array[0] = tmp;
         downAdjust(array, i, 0);
     }
 }