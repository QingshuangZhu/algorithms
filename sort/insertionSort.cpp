/*
 * straight insertion sort
 */

 #include "sort.h"

 void insertionSort(int array[], int length) {
     for(int i = 1; i < length; i++){
         int insertValue = array[i];
         int j = i - 1;
         for(; insertValue < array[j]; j--){
             array[j+1] = array[j];
         }
         array[j+1] = insertValue;
     }
 }

 void binaryInsertionSort(int array[], int length) {
     for(int i = 1; i < length; i++){
         int insertValue = array[i];
         int left = 0;
         int right = i-1;

         /* 用二分查找确定插入位置 */
         while(left <= right){
             int mid = (left + right)/2;
             if(insertValue < array[mid]){
                 right = mid - 1;
             }else{
                 left = mid + 1;
             }
         }

         for(int j = i - 1; j >= left; j--){
             array[j+1] = array[j];
         }

         array[left] = insertValue;
     }
 }