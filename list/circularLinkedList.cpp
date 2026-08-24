/*
 * circular linked list
 */

#include "circularLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

/* 初始化 circular linked list */
int initCList(cLinkedList *list) {    /* 注意参数是按值传递 */
    if(NULL == list){
        return 0;
    }
    (*list) = (cLinkedList)malloc(sizeof(cLNode));    /* 产生头结点 */
    if(NULL == (*list)){
        return 0;
    }

    (*list)->data = 0;
    (*list)->next = (*list);
    return 1;
}

/* 销毁 circular linked list */
int destroyCList(cLinkedList *list) {
    if(NULL == list){
        return 0;
    }
    if(NULL == *list){
        return 1;
    }

    cLinkedList head = (*list)->next;    /* list为表尾，head指向头结点 */
    while(head != *list){
        cLinkedList tmp = head;
        head = head->next;
        free(tmp);
        tmp = NULL;
    }
    
    free(*list);
    *list = NULL;
    return 1;
}

/* 清空 circular linked list */
int clearCList(cLinkedList list) {
    if(NULL == list){
        return 0;
    }

    cLinkedList head = list->next;    /* list为表尾，head指向头结点 */
    while(head != list){
        cLinkedList tmp = head;
        head = head->next;
        free(tmp);
        tmp = NULL;
    }
    
    list->data = 0;
    list->next = list;
    return 1;
}

/* circular linked list 是否为空 */
int cListEmpty(cLinkedList list) {
    if(NULL == list || list == list->next){
        return 1;
    }
    return 0;
}

int cListLength(cLinkedList list) {
    int length = 0;
    if(NULL == list){
        return 0;
    }

    cLinkedList head = list->next;    /* list为表尾，head指向头结点 */
    while(head != list){
        length++;
        head = head->next;
    }
    return length;
}

/* 获得 circular linked list 在pos位置的值 */
int cListGet(cLinkedList list, int pos, dataType *data) {
    /* 1 <= pos <= length */
    if(NULL == list || NULL == data || pos > cListLength(list) || pos < 1){
        return 0;
    }

    int index = 0;
    cLinkedList head = list->next;    /* list为表尾，head指向头结点 */
    while(index < pos){
        index++;
        head = head->next;
    }
    *data = head->data;
    return 1;
}

/* 将结点插入在pos位置上 */
int cListInsert(cLinkedList *list, int pos, dataType data) {
    /* 1 <= pos <= length+1 */
    if(NULL == list || NULL == *list ||
       pos > cListLength(*list)+1 || pos < 1){
        return 0;
    }

    int index = 0;
    cLinkedList head = (*list)->next;    /* *list为表尾，head指向头结点 */

    /* 寻找第pos-1个结点 */
    while(index < pos-1){
        index++;
        head = head->next;
    }

    cLinkedList newNode = (cLinkedList)malloc(sizeof(cLNode));
    if(NULL == newNode){
        return 0;
    }
    newNode->data = data;
    newNode->next = head->next;
    head->next = newNode;

    if(head == *list){    /* 若插入最末尾的位置，则改变尾结点 */
        *list = newNode;
    }
    return 1;
}

/* 删除第pos个结点 */
int cListDelete(cLinkedList *list, int pos, dataType *data) {
    /* 1 <= pos <= length */
    if(NULL == list || NULL == *list || NULL == data ||
       pos > cListLength(*list) || pos < 1){
        return 0;
    }

    int index = 0;
    cLinkedList head = (*list)->next;    /* *list为表尾，head指向头结点 */
        
    /* 寻找第pos-1个结点 */
    while(index < pos-1){
        index++;
        head = head->next;
    }

    cLinkedList tmp = head->next;    /* tmp 为待删除结点 */
    *data = tmp->data;
    head->next = tmp->next;

    if(tmp == *list) {    /* 若删除最末尾的结点，则改变尾结点 */
        *list = head;
    }
    free(tmp);
    return 1;
}

static int copyCListNodes(cLinkedList source, cLinkedList *result) {
    cLinkedList sourceHead = source->next;
    cLinkedList node = sourceHead->next;
    while(node != sourceHead){
        cLinkedList newNode = (cLinkedList)malloc(sizeof(cLNode));
        if(NULL == newNode){
            return 0;
        }
        newNode->data = node->data;
        newNode->next = (*result)->next;
        (*result)->next = newNode;
        *result = newNode;
        node = node->next;
    }
    return 1;
}

/* 将list1和list2连接：list1, list2, list3 分别为尾指针 */
int cListAttach(cLinkedList list1, cLinkedList list2, cLinkedList *list3) {
    if(NULL == list1 || NULL == list2 || NULL == list3){
        return 0;
    }

    cLinkedList result = NULL;
    if(!initCList(&result)){
        return 0;
    }
    if(!copyCListNodes(list1, &result) || !copyCListNodes(list2, &result)){
        destroyCList(&result);
        return 0;
    }
    *list3 = result;
    return 1;
}

void cListTraverse(cLinkedList list) {
    if(NULL == list){
        return;
    }
    cLinkedList tmp = list->next->next;    /* list为表尾，tmp指向第一个结点 */

    while (tmp != list->next)
    {
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    }
}
