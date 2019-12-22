/*
 * bucket sort
 */

#include "sort.h"
#include "../list/list.h"
#include <stdlib.h>

void bucketSort(int array[], int length) {
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

    /* 初始化桶,桶的数量等于元素的个数，并且最后一个桶中只包含最大元素 */
    int bucketNum = length;
    linkedList *bucketArray = (linkedList*)malloc(bucketNum*sizeof(linkedList));
    for(int i = 0; i < bucketNum; i++){
        initList(&bucketArray[i]);
    }

    /* 遍历原始数组，将每个元素放入对应的桶中 */
    for(int i = 0; i < length; i++){
        int index = (int)(array[i] - min)*(bucketNum - 1)/d;
        listInsert(bucketArray[index], 1, array[i]);
    }

    /* 对每个桶内部进行排序 */
    for(int i = 0; i < bucketNum; i++){
        bucketArray[i] = listSort(bucketArray[i]);
    }

    /* 将排序后的元素写回原数组 */
    for(int i = 0, j = 0; i < bucketNum && j < length; i++){
        linkedList tmp = bucketArray[i]->next;
        while(NULL != tmp){
            array[j++] = tmp->data;
            tmp = tmp->next;
        }
    }

    /* 销毁链表 */
    for(int i = 0; i < bucketNum; i++){
        destroyList(&bucketArray[i]);
    }
    free(bucketArray);
    bucketArray = NULL;
}