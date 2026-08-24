/*
 * merging sort
 */

#include "sort.h"

/* 一趟归并操作 */
static void merge(int array[], int tmp[], int start, int mid, int end) {
    int i = start;        /* 左边有序序列第一个位置的下标 */
    int j = mid + 1;      /* 右边有序序列第一个位置的下标 */
    int k = start;        /* 合并后有序序列第一个位置的下标 */

    while(i <= mid && j <= end){
        if(array[i] <= array[j]){
            tmp[k++] = array[i++];
        }else{
            tmp[k++] = array[j++];
        }
    }

    while(i <= mid) {
        tmp[k++] = array[i++];
    }

    while(j <= end){
        tmp[k++] = array[j++];
    }

    /* 将归并后有序子序列复制到原数组中 */
    for(int i = start; i <= end; i++){
        array[i] = tmp[i];
    }
}

/* merging sort */
void mergeSort(int array[], int tmp[], int start, int end) {
    if(start < end){
        int mid = start + ((end - start)>>1);    /* 避免int溢出 */
        mergeSort(array, tmp, start, mid);
        mergeSort(array, tmp, mid+1, end);
        merge(array, tmp, start, mid, end);
    }
}

/* 非递归实现 */
void mergeSort2(int array[], int tmp[], int start, int end) {
    const long long total = (long long)end - start + 1;

    for(long long length = 1; length < total; length *= 2){
        for(long long offset = 0; offset < total; offset += 2*length){
            int s = start + (int)offset;
            int m = start + (int)(offset + length - 1);
            if(m >= end){
                continue;
            }
            long long last = offset + 2*length - 1;
            int e = last < total ? start + (int)last : end;
            merge(array, tmp, s, m, e);
        }
    }
}
