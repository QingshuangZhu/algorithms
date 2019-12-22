/*
 * radix sort
 */

#include "sort.h"
#include <stdlib.h>
#include <math.h>

void radixSort(int array[], int length) {
    int max = array[0];

    /* 数列中最大的值 */
    for(int i = 0; i < length; i++){
        if(max < array[i]){
            max = array[i];
        }
    }

    /* 最大值的位数 */
    int count = 0;
    do
    {
        count++;
        max /=10; 
    } while (0 != max);

    //int (*bucket)[10] = (int (*)[10])malloc(count * 10 * sizeof(int));

    int *sortedArray = (int*)malloc(length * sizeof(int));

    for(int i = 0; i < count; i++){    /* 一次LSD，即一次计数排序 */

        /* 创建桶，并统计相应元素个数 */
        int bucket[10] = {0};
        int radix = pow(10, i);    /* 基数 */
        for(int j = 0; j < length; j++){
            
            int index = (array[j] / radix) % 10;
            bucket[index]++;
        }

        /* 将统计数组从第2个元素开始，每元素都加上前面所有元素之和 */
        /* 让统计数组存储的元素值，等于相应整数的最终排序位置的序号 */
        for(int j = 1; j < 10; j++){
            bucket[j] += bucket[j-1];
        }

        /* 倒序遍历原始数组，从统计数组找到正确位置，输出到排序后数组 */
        for(int j = length - 1; j >= 0; j--){
            int index = (array[j] / radix) % 10;
            sortedArray[bucket[index] - 1] = array[j];
            bucket[index]--;
        }

        /* 把排序后的序列复制到原数组 */
        for(int j = 0; j < length; j++){
            array[j] = sortedArray[j];
        }
    }
    free(sortedArray);
    sortedArray = NULL;
}