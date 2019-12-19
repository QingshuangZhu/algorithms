/* 
 * quick sort
 */

#include "sort.h"
#include <stack>

 /* 双边循环法 */
void quickSort(int array[], int left, int right) {
    int pivot = array[left];    /* 基准元素 */
    int l = left;
    int r = right;

    /* 递归结束条件 */
    if(left >= right){
        return;
    }
    
    /* 一次快排：分为大于pivot和小于pivot两部分 */
    while(left < right){

        while(left < right && pivot <= array[right]){
            right--;
        }
        array[left] = array[right];

        while(left < right && array[left] <= pivot){
            left++;
        }
        array[right] = array[left];
    }
    array[left] = pivot;

    /* 分成两部分递归 */
    quickSort(array, l, left-1);
    quickSort(array, left+1, r);
}

/* 单边循环法 */
void quickSort2(int array[], int left, int right) {
    int pivot = array[left];     /* 基准元素 */
    int mark = left;             /* 小于pivot元素的边界 */

    /* 递归结束条件 */
    if(left >= right){
        return;
    }

    /* 一次快排：分为大于pivot和小于pivot两部分 */
    for(int i = left+1; i <= right; i++){
        if(array[i] < pivot){
            mark++;
            int tmp = array[mark];
            array[mark] = array[i];
            array[i] = tmp;
        }
    }
    array[left] = array[mark];
    array[mark] = pivot;

  /* 分成两部分递归 */
  quickSort2(array, left, mark-1);
  quickSort2(array, mark+1, right);
}

/* 非递归实现：把原本的递归实现转化成一个栈的实现，在栈中存储每次方法调用的参数 */
int partition(int array[], int left, int right) {
    int pivot = array[left];
    int mark = left;

    for(int i = left; i <= right; i++){
        if(array[i] < pivot){
            mark++;
            int tmp = array[mark];
            array[mark] = array[i];
            array[i] = tmp;
        }
    }
    array[left] = array[mark];
    array[mark] = pivot;
    return mark;
}
void quickSort3(int array[], int left, int right) {
    std::stack<int> s;
    s.push(left);
    s.push(right);

    while(!s.empty()){
        int r = s.top();
        s.pop();
        int l = s.top();
        s.pop();
        int pivotIndex = partition(array, l, r);
        if(l < pivotIndex - 1){
            s.push(l);
            s.push(pivotIndex - 1);
        }
        if(pivotIndex + 1 < r){
            s.push(pivotIndex + 1);
            s.push(r);
        }
    }
}