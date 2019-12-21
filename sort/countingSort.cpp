/*
 * counting sort
 */

#include "sort.h"
#include <stdlib.h>

void countSort(int array[], int sortedArray[], int length) {
    int max = array[0];
    int min = array[0];
    int d = max - min;

    /* 得到数列的最大值和最小值，并计数其差值 */
    for(int i = 0; i < length; i++){
        if(array[i] > max){
            max = array[i];
        }

        if(array[i] < min){
            min = array[i];
        }
    }
    d = max - min;

    /* 创建统计数组并统计对应元素的个数 */
    int *countArray = (int*)calloc(d+1, sizeof(int));
    for(int i = 0; i < length; i++){
        countArray[array[i] - min]++;
    }

    /* 将统计数组从第2个元素开始，每元素都加上前面所有元素之和 */
    /* 让统计数组存储的元素值，等于相应整数的最终排序位置的序号 */
    for(int i = 1; i < d+1; i++){
        countArray[i] += countArray[i-1];
    }

    /* 倒序遍历原始数组，从统计数组找到正确位置，输出到排序后数组 */
    for(int i = length - 1; i >= 0; i--){
        sortedArray[countArray[array[i] - min] - 1] = array[i];
        countArray[array[i] - min]--;
    }

    free(countArray);
    countArray = NULL;
}