/*
 * list
 */

#include "list.h"
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int copyListNodes(linkedList source, linkedList *tail) {
    linkedList node = source->next;
    while(NULL != node){
        linkedList newNode = (linkedList)malloc(sizeof(lNode));
        if(NULL == newNode){
            return 0;
        }
        newNode->data = node->data;
        newNode->next = NULL;
        (*tail)->next = newNode;
        *tail = newNode;
        node = node->next;
    }
    return 1;
}

/* 初始化list */
int initList(linkedList *list) {
    if(NULL == list){
        return 0;
    }
    *list = (linkedList)malloc(sizeof(lNode));    /* 产生头结点 */
    if(NULL == *list){
        return 0;
    }
    (*list)->data = 0;
    (*list)->next = NULL;
    return 1;
}

int initList2(sqList *list) {
    if(NULL == list){
        return 0;
    }
    list->base = (dataType*)malloc(LIST_INIT_SIZE * sizeof(dataType));
    if(NULL == list->base){
        return 0;
    }

    list->length = 0;
    list->size = LIST_INIT_SIZE;
    return 1;
}
  
/* 销毁list */
int destroyList(linkedList *list) {
    if(NULL == list){
        return 0;
    }
    if(NULL == *list){
        return 1;
    }

    linkedList tmp = (*list)->next;    /* 有头结点 */
    while(NULL != tmp){
        linkedList tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2);
        tmp2 = NULL;
    }
    free(*list);
    *list = NULL;

    return 1;
}

int destroyList2(sqList *list) {
    if(NULL == list){
        return 0;
    }
    if(NULL != list->base){
        free(list->base);
        list->base = NULL;
    }
    list->length = 0;
    list->size = 0;
    return 1;
}

/* 清空list */
int clearList(linkedList list) {
    if(NULL == list){
        return 0;
    }

    linkedList tmp = list->next;    /* 有头结点 */
    while(NULL != tmp){
        linkedList tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2);
        tmp2 = NULL;
    }

    list->data = 0;
    list->next = NULL;
    return 1;
}

void clearList2(sqList *list) {
    if(NULL == list){
        return;
    }
    if(NULL != list->base){
        memset(list->base, 0, list->size * sizeof(dataType));
    }
    list->length = 0;
}

/* list是否为空 */
int listEmpty(linkedList list) {
    if(NULL == list || NULL == list->next){    /* 有头结点 */
        return 1;
    }
    return 0;
}

int listEmpty2(sqList list) {
    if(0 == list.length){
        return 1;
    }
    return 0;
}

 /* list的长度 */
int listLength(linkedList list) {
    if(NULL == list) {
        return 0;
    }

    linkedList tmp = list->next;    /* 有头结点 */
    int length = 0;
    while(NULL != tmp){
        length++;
        tmp = tmp->next;
    }
    return length;
}

int listLength2(sqList list) {
    return list.length;
}

/* 获得list在pos位置的值 */
int listGet(linkedList list, int pos, dataType *data) {
    if(NULL == list || NULL == data){
        return 0;
    }

    /* 1 <= pos <= length */
    if(pos > listLength(list) || pos < 1){
        return 0;
    }

    linkedList tmp = list->next;    /* 有头结点 */
    int index = 0;
    while(NULL != tmp){
        index++;
        if(index == pos){
            *data = tmp->data;
            break;
        }
        tmp = tmp->next;
    }
    return 1;
}

int listGet2(sqList list, int pos, dataType *data) {
    /* 1 <= pos <= length */
    if(NULL == data || NULL == list.base || pos > list.length || pos < 1){
        return 0;
    }

    *data = list.base[pos-1];
    return 1;
}

/* 将结点插入在pos位置上 */
int listInsert(linkedList list, int pos, dataType data) {
    if(NULL == list || pos < 1){
        return 0;
    }

    linkedList tmp = list;    /* 有头结点 */
    int index = 0;

    /* 寻找第pos-1个结点 */
    while(NULL != tmp && index < pos-1){
        index++;
        tmp = tmp->next;
    }

    /* 1 <= pos <= length+1 */
    if(NULL == tmp){
        return 0;
    }

    /* tmp 位于 pos-1 处 */
    linkedList newNode = (linkedList)malloc(sizeof(lNode));
    if(NULL == newNode){
        return 0;
    }
    newNode->data = data;
    newNode->next = tmp->next;
    tmp->next = newNode;
    return 1;
}

/* 将结点插入在pos位置上 */
int listInsert2(sqList *list, int pos, dataType data) {
    /* 1 <= pos <= length+1 */
    if(NULL == list || NULL == list->base || pos < 1 ||
       list->length < 0 || list->size < 0 || list->length > list->size ||
       list->length == INT_MAX || pos - 1 > list->length){
        return 0;
    }

    if(list->length >= list->size){
        if(list->size > INT_MAX - LIST_INCREMENT){
            return 0;
        }
        int newSize = list->size + LIST_INCREMENT;
        if((size_t)newSize > SIZE_MAX/sizeof(dataType)){
            return 0;
        }
        dataType *newBase = (dataType*)realloc(
            list->base, (size_t)newSize*sizeof(dataType));
        if(NULL == newBase){
            return 0;
        }
        list->base = newBase;
        list->size = newSize;
    }

    for(int i = list->length-1; i >= pos-1 && i >= 0; i--){
        list->base[i+1] = list->base[i];
    }
    list->base[pos-1] = data;
    list->length++;
    return 1;
}

/* 删除第pos个结点 */
int listDelete(linkedList list, int pos, dataType *data) {
    if(NULL == list || NULL == data || pos < 1){
        return 0;
    }

    linkedList tmp = list;    /* 有头结点 */
    int index = 0;

    /* 寻找第pos-1个结点 */
    while(NULL != tmp && index < pos-1){
        index++;
        tmp = tmp->next;
    }

    /* 1 <= pos <= length */
    if(NULL == tmp || NULL == tmp->next){
        return 0;
    }

    /* tmp 位于 pos-1 处 */
    linkedList tmp2 = tmp->next;
    tmp->next = tmp2->next;
    *data = tmp2->data;
    free(tmp2);
    tmp2 = NULL;
    return 1;
}

int listDelete2(sqList *list, int pos, dataType *data) {
    /* 1 <= pos <= length */
    if(NULL == list || NULL == list->base || NULL == data ||
       pos < 1 || pos > list->length){
        return 0;
    }

    *data = list->base[pos-1];
    for(int i = pos -1; i < list->length -1; i++){
        list->base[i] = list->base[i+1];
    }
    list->length--;
    return 1;
}

/* 将list1和list2连接 */
int listAttach(linkedList list1, linkedList list2, linkedList *list3) {
    if(NULL == list1 || NULL == list2 || NULL == list3){
        return 0;
    }

    linkedList result = NULL;
    if(!initList(&result)){
        return 0;
    }
    linkedList tail = result;
    if(!copyListNodes(list1, &tail) || !copyListNodes(list2, &tail)){
        destroyList(&result);
        return 0;
    }
    *list3 = result;
    return 1;
}

int listAttach2(sqList list1, sqList list2, sqList *list3) {
    if(NULL == list3 || list1.length < 0 || list2.length < 0 ||
       (list1.length > 0 && NULL == list1.base) ||
       (list2.length > 0 && NULL == list2.base) ||
       list1.length > INT_MAX - list2.length){
        return 0;
    }

    int totalLen = list1.length + list2.length;
    if(0 == totalLen){
        list3->length = 0;
        return 1;
    }
    if((size_t)totalLen > SIZE_MAX / sizeof(dataType)){
        return 0;
    }
    dataType *newBase = NULL;
    newBase = (dataType*)malloc((size_t)totalLen * sizeof(dataType));
    if(NULL == newBase){
        return 0;
    }
    for(int i = 0; i < list1.length; i++){
        newBase[i] = list1.base[i];
    }
    for(int i = 0; i < list2.length; i++){
        newBase[list1.length + i] = list2.base[i];
    }

    free(list3->base);
    list3->base = newBase;
    list3->length = totalLen;
    list3->size = totalLen;
    return 1;
}

/* 反转list */
int listReverse(linkedList list) {
    if(NULL == list){
        return 0;
    }

    linkedList tmp = NULL;
    linkedList p1 = NULL;
    linkedList p2 = list->next;    /* 有头结点 */

    while(NULL != p2){
        tmp = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = tmp;
    }
    list->next = p1;

    return 1;
}

int listReverse2(sqList list) {
    dataType tmp = 0;
    for(int i = 0; i < list.length/2; i++){
        tmp = list.base[i];
        list.base[i] = list.base[list.length - i - 1];
        list.base[list.length - i - 1] = tmp;
    }
    return 1;
}

/* 遍历list */
void listTraverse(linkedList list) {
    if(NULL == list){
        return;
    }
    linkedList tmp = list->next;    /* 有头节点 */

    while(NULL != tmp){
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    }
}

void listTraverse2(sqList list) {
    for(int i = 0; i < list.length; i++){
        printf("%d\n", list.base[i]);
    }
}

/* 一趟归并排序 */
static linkedList merge(linkedList left, linkedList right) {
    lNode head = {0, NULL};
    linkedList tail = &head;

    while(NULL != left && NULL != right){
        if(left->data <= right->data){
            tail->next = left;
            left = left->next;
        }else{
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    tail->next = (NULL != left) ? left : right;
    return head.next;
}

static linkedList sortNodes(linkedList first) {
    if(NULL == first || NULL == first->next){
        return first;
    }

    linkedList slow = first;
    linkedList fast = first->next;
    while(NULL != fast && NULL != fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }

    linkedList right = slow->next;
    slow->next = NULL;
    return merge(sortNodes(first), sortNodes(right));
}

/* 链表排序 */
linkedList listSort(linkedList list) {
    if(NULL == list){
        return NULL;
    }
    list->next = sortNodes(list->next);
    return list;
}
