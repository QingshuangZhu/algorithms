/*
 * selection sort
 */

 #include "sort.h"

 void selectionSort(int array[], int length) {
     for(int i = 0; i < length - 1; i++){
         int minIndex = i;
         int min = array[minIndex];

         for(int j = i+1; j < length; j++){
             if(array[j] < array[minIndex]){
                 minIndex = j;
             }
         }
         min = array[minIndex];
         array[minIndex] = array[i];
         array[i] = min;
     }
 }