/*
 * bucket sort
 */

#include "sort.h"
#include "../list/list.h"
#include <stdint.h>
#include <stdlib.h>

void bucketSort(int array[], int length) {
    if(NULL == array || length <= 1){
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

    unsigned long long range = (unsigned long long)((long long)max - min);
    if(0 == range){
        return;
    }

    /* 初始化桶,桶的数量等于元素的个数，并且最后一个桶中只包含最大元素 */
    int bucketNum = length;
    if((size_t)bucketNum > SIZE_MAX/sizeof(linkedList)){
        return;
    }
    linkedList *bucketArray = (linkedList*)malloc(bucketNum*sizeof(linkedList));
    if(NULL == bucketArray){
        return;
    }

    int initialized = 0;
    int completed = 1;
    for(; initialized < bucketNum; initialized++){
        if(!initList(&bucketArray[initialized])){
            completed = 0;
            break;
        }
    }

    /* 遍历原始数组，将每个元素放入对应的桶中 */
    for(int i = 0; completed && i < length; i++){
        unsigned long long distance = (unsigned long long)((long long)array[i] - min);
        int index = (int)(distance*(unsigned int)(bucketNum - 1)/range);
        if(!listInsert(bucketArray[index], 1, array[i])){
            completed = 0;
        }
    }

    /* 对每个桶内部进行排序 */
    for(int i = 0; completed && i < bucketNum; i++){
        if(!listEmpty(bucketArray[i])){
            linkedList sortedBucket = listSort(bucketArray[i]);
            if(NULL == sortedBucket){
                completed = 0;
            }else{
                bucketArray[i] = sortedBucket;
            }
        }
    }

    /* 将排序后的元素写回原数组 */
    if(completed){
        for(int i = 0, j = 0; i < bucketNum && j < length; i++){
            linkedList tmp = bucketArray[i]->next;
            while(NULL != tmp){
                array[j++] = tmp->data;
                tmp = tmp->next;
            }
        }
    }

    /* 销毁链表 */
    for(int i = 0; i < initialized; i++){
        destroyList(&bucketArray[i]);
    }
    free(bucketArray);
}
