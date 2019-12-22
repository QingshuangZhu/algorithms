/*
 * double linked list
 */

#include "doubleLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

/* 初始化 double linked list */
int initDuList(duLinkedList *list) {
    *list = (duLinkedList)malloc(sizeof(duLNode));    /* 产生头结点 */
    if(NULL == *list){
        return 0;
    }
    (*list)->data = 0;
    (*list)->prior = NULL;
    (*list)->next = NULL;
    return 1;
}

/* 销毁 double linked list */
int destroyDuList(duLinkedList *list) {
    if(NULL == list){
        return 0;
    }

    duLinkedList tmp = (*list)->next;    /* 有头结点 */
    while(NULL != tmp){
        duLinkedList tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2);
        tmp2 = NULL;
    }

    free(*list);
    *list = NULL;
    return 1;
}

/* 清空 double linked list */
int clearDuList(duLinkedList list) {
   if(NULL == list){
        return 0;
    }

    duLinkedList tmp = list->next;    /* 有头结点 */
    while(NULL != tmp){
        duLinkedList tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2);
        tmp2 = NULL;
    }

    list->data = 0;
    list->prior = NULL;
    list->next = NULL;
    return 1;
}

/* double linked list 是否为空 */
int duListEmpty(duLinkedList list) {
    if(NULL == list || NULL == list->next){    /* 有头结点 */
        return 1;
    }
    return 0;
}

 /* double linked list 的长度 */
int duListLength(duLinkedList list) {
    if(NULL == list) {
        return 0;
    }

    duLinkedList tmp = list->next;    /* 有头结点 */
    int length = 0;
    while(NULL != tmp){
        length++;
        tmp = tmp->next;
    }
    return length;
}

/* 获得 double linked list 在pos位置的值 */
int duListGet(duLinkedList list, int pos, dataType *data) {
    /* 1 <= pos <= length */
    if(pos > duListLength(list) || pos < 1){
        return 0;
    }

    duLinkedList tmp = list->next;    /* 有头结点 */
    int index = 0;
    while(NULL != tmp){
        index++;
        if(index == pos){
            *data = tmp->data;
            break;
        }
        tmp = tmp->next;
    }
    return index;
}

/* 将结点插入在pos位置上 */
int duListInsert(duLinkedList list, int pos, dataType data) {
    if(NULL == list){
        return 0;
    }

    duLinkedList tmp = list;    /* 有头结点 */
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
    duLinkedList newNode = (duLinkedList)malloc(sizeof(duLNode));
    if(NULL == newNode){
        return 0;
    }

    newNode->data = data;
    newNode->prior = tmp;
    newNode->next = tmp->next;
    if(NULL != tmp->next){  /* 跳过插在最后处 */
        tmp->next->prior = newNode;
    }
    tmp->next = newNode;
    return 1;
}

/* 删除第pos个结点 */
int duListDelete(duLinkedList list, int pos, dataType *data) {
    if(NULL == list){
        return 0;
    }

    duLinkedList tmp = list;    /* 有头结点 */
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
    duLinkedList tmp2 = tmp->next;
    tmp->next = tmp2->next;
    tmp2->next->prior = tmp;
    *data = tmp2->data;
    free(tmp2);
    tmp2 = NULL;
    return 1;
}

/* 遍历 double linked list */
void duListTraverse(duLinkedList list) {
    if(NULL == list){
        return;
    }
    duLinkedList tmp = list->next;    /* 有头节点 */

    while(NULL != tmp){
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    }
}