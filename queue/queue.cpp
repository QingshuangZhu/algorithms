/*
 * queue
 */

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

/* 初始化 queue */
int initQueue(linkedQueue *q) {
    qNode *head = (qNode*)malloc(sizeof(qNode));    /* 产生头结点 */
    if(NULL == head){
        return 0;
    }

    q->front = q->rear = head;
    head->next = NULL;
    q->length = 0;
}

/* 销毁 queue */
int destroyQueue(linkedQueue *q) {
    while(NULL != q->front){
        q->rear = q->front;
        q->front = q->front->next;
        free(q->rear);
        q->rear = NULL;
    }
    q->length = 0;
    return 1;
}

/* 清空 queue */
int clearQueue(linkedQueue *q) {
    while(NULL != q->front->next) {
        q->rear = q->front->next;
        q->front->next = q->front->next->next;
        free(q->rear);
        q->rear = NULL;
    }
    q->rear = q->front;
    q->length = 0;
    return 1;
}

/* queue 是否为空 */
int queueEmpty(linkedQueue *q) {
    if(q->front == q->rear) {
        return 1;
    }
    return 0;
}

/* queue 长度 */
int queueLength(linkedQueue *q) {
    return q->length;
}

/* 获取队头元素 */
int getHead(linkedQueue *q, dataType *data) {
    if(q->front == q->rear){
        return 0;
    }
    *data = q->front->next->data;
    return 1;
}

/* 入队 */
int enQueue(linkedQueue *q, dataType data) {
    qNode *newNode = (qNode*)malloc(sizeof(qNode));
    if(NULL == newNode){
        return 0;
    }

    newNode->data = data;
    newNode->next = NULL;
    q->rear->next = newNode;
    q->rear = newNode;
    q->length++;
    return 1;
}

/* 出队 */
int deQueue(linkedQueue *q, dataType *data) {
    if(q->front == q->rear){
        return 0;
    }
    
    qNode *tmp = q->front->next;
    *data = tmp->data;
    q->front->next = tmp->next;
    if(q->rear == tmp){    /* 最后一个元素出队 */
        q->rear = q->front;
    }
    free(tmp);
    tmp = NULL;
    q->length--;
    return 1;
}

/* 遍历队列 */
void queueTraverse(linkedQueue q) {
    if(q.front == q.rear){
        return;
    }
    qNode *tmp = q.front->next;
    while (NULL != tmp) {
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    }
}