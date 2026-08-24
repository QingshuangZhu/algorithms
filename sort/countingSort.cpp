/*
 * counting sort
 */

#include "sort.h"
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

void countSort(int array[], int sortedArray[], int length) {
    if(NULL == array || NULL == sortedArray || length <= 0){
        return;
    }

    int max = array[0];
    int min = array[0];

    /* 得到数列的最大值和最小值 */
    for(int i = 1; i < length; i++){
        if(array[i] > max){
            max = array[i];
        }

        if(array[i] < min){
            min = array[i];
        }
    }

    unsigned long long difference = (unsigned long long)((long long)max - min);
    if(difference >= INT_MAX){
        return;
    }
    size_t range = (size_t)difference + 1;
    if(range > SIZE_MAX/sizeof(int)){
        return;
    }

    /* 创建统计数组并统计对应元素的个数 */
    int *countArray = (int*)calloc(range, sizeof(int));
    if(NULL == countArray){
        return;
    }
    for(int i = 0; i < length; i++){
        size_t index = (size_t)((long long)array[i] - min);
        countArray[index]++;
    }

    /* 将统计数组从第2个元素开始，每元素都加上前面所有元素之和 */
    /* 让统计数组存储的元素值，等于相应整数的最终排序位置的序号 */
    for(size_t i = 1; i < range; i++){
        countArray[i] += countArray[i-1];
    }

    /* 倒序遍历原始数组，从统计数组找到正确位置，输出到排序后数组 */
    for(int i = length - 1; i >= 0; i--){
        size_t index = (size_t)((long long)array[i] - min);
        sortedArray[countArray[index] - 1] = array[i];
        countArray[index]--;
    }

    free(countArray);
}
