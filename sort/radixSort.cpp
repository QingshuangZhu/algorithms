/*
 * radix sort
 */

#include "sort.h"
#include <stdint.h>
#include <stdlib.h>

void radixSort(int array[], int length) {
    if(NULL == array || length <= 1){
        return;
    }

    int max = array[0];

    /* 数列中最大的值；该实现仅接受非负整数 */
    for(int i = 0; i < length; i++){
        if(array[i] < 0){
            return;
        }
        if(max < array[i]){
            max = array[i];
        }
    }

    if((size_t)length > SIZE_MAX/sizeof(int)){
        return;
    }
    int *sortedArray = (int*)malloc(length * sizeof(int));
    if(NULL == sortedArray){
        return;
    }

    for(unsigned int radix = 1; ; radix *= 10){    /* 一次LSD，即一次计数排序 */
        /* 创建桶，并统计相应元素个数 */
        int bucket[10] = {0};
        for(int j = 0; j < length; j++){
            unsigned int index = ((unsigned int)array[j] / radix) % 10;
            bucket[index]++;
        }

        /* 将统计数组从第2个元素开始，每元素都加上前面所有元素之和 */
        /* 让统计数组存储的元素值，等于相应整数的最终排序位置的序号 */
        for(int j = 1; j < 10; j++){
            bucket[j] += bucket[j-1];
        }

        /* 倒序遍历原始数组，从统计数组找到正确位置，输出到排序后数组 */
        for(int j = length - 1; j >= 0; j--){
            unsigned int index = ((unsigned int)array[j] / radix) % 10;
            sortedArray[bucket[index] - 1] = array[j];
            bucket[index]--;
        }

        /* 把排序后的序列复制到原数组 */
        for(int j = 0; j < length; j++){
            array[j] = sortedArray[j];
        }

        if(radix > (unsigned int)max/10){
            break;
        }
    }
    free(sortedArray);
}
