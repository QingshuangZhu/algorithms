/*
 * bubble sort
 */

#include "sort.h"

void bubbleSort(int array[], int length) {
    for(int i = 0; i < length; i++){
        for(int j = 0; j < length - i - 1; j++){
            if( array[j] > array[j+1]){
                int tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
    }
}

/* bubble sort optimization */
void bubbleSort2(int array[], int length) {
    int pos = 0 ;                    /* 最后交换的位置 */
    int sortBorder = length - 1;     /* 有序边界：从0到sortBorder是无序的，sortBorder到length-1是有序的 */
    for(int i = 0; i < length; i++){
        int isSorted = 1;            /* 有序标志 */
        for(int j = 0; j < sortBorder; j++){
            if(array[j] > array[j+1]){
                int tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
                pos = j;
                isSorted = 0;
            }
        }
        sortBorder = pos;

        if(isSorted){
            break;
        }
    }
}

/* cocktail: 双向冒泡排序 */
void cocktail(int array[], int length) {
    int left = 0;
    int right = length - 1;
    int pos = 0;                /* 最后交换的位置 */
    int isSorted = 1;           /* 有序标志 */

    while(left < right){

        /* 从左向右冒泡排序 */
        isSorted = 1;
        for(int i = 0; i < right; i++){
            if(array[i] > array[i+1]){
                int tmp = array[i];
                array[i] = array[i+1];
                array[i+1] = tmp;
                pos = i;
                isSorted = 0;
            }
        }
        right = pos;
        if(isSorted){
            break;
        }

        /* 从右向左冒泡排序 */
        isSorted = 1;           /* 有序标志在从右向左排序前重新赋为1 */
        for(int i = right; i > left; i--){
            if(array[i] < array[i-1]){
                int tmp = array[i];
                array[i] = array[i-1];
                array[i-1] = tmp;
                pos = i;
                isSorted = 0;
            }
        }
        left = pos;
        if(isSorted){
            break;
        }

    }
}