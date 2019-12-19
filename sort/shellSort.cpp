/*
 * shell sort
 */

#include "sort.h"

/* 一次希尔插入排序 */
void shellInsert(int array[], int length, int d) {
    for(int i = d; i < length; i++){
        int insertValue = array[i];
        int j = i - d;
        for(; j >= 0 && insertValue < array[j]; j -= d){
            array[j+d] = array[j];
        }
        array[j+d] = insertValue;
    }
}

void shellSort(int array[], int length) {
    int d = length;    /* 希尔增量 */
    while(d > 1){
        d /=2;
        shellInsert(array, length, d);
    }
}