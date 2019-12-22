/*
 * circular queue
 */

#include "circularQueue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* 初始化 circular queue */
int initCQueue(sqQueue *cQueue) {
    dataType *tmp = (dataType*)malloc(MAXQSIZE*sizeof(dataType));
    if(NULL == tmp){
        return 0;
    }
    cQueue->base = tmp;
    cQueue->front = cQueue->rear = 0;
    return 1;
}

/* 销毁 circular queue */
int destroyCQueue(sqQueue *cQueue) {
    if(NULL != cQueue->base){
        free(cQueue->base);
        cQueue->base = NULL;
    }
    cQueue->front = cQueue->rear = 0;
    return 1;
}

/* 清空 circular queue */
int clearCQueue(sqQueue *cQueue) {
    if(NULL != cQueue->base){
        memset(cQueue->base, 0, MAXQSIZE*sizeof(dataType));
    }
    cQueue->front = cQueue->rear = 0;
    return 1;
}

/* circular queue 是否为空 */
int cQueueEmpty(sqQueue *cQueue) {
    if (cQueue->front == cQueue->rear){
        return 1;
    }
    return 0;
}

/* circular queue 长度 */
int cQueueLength(sqQueue *cQueue) {
    return (cQueue->rear - cQueue->front + MAXQSIZE) % MAXQSIZE;
}

/* 获取队头元素 */
int getHead(sqQueue *cQueue, dataType *data) {
    if(cQueue->front == cQueue->rear) {
        return 0;
    }

    *data = cQueue->base[cQueue->front];
    return 1;
}

/* 入队 */
int enCQueue(sqQueue *cQueue, dataType data) {
    /* 队尾指针的下一位置是队头指针则表示队列已满，会少用一个元素空间 */
    if((cQueue->rear + 1) % MAXQSIZE == cQueue->front){
        return 0;
    }
    cQueue->base[cQueue->rear] = data;
    cQueue->rear = (cQueue->rear + 1) % MAXQSIZE;
    return 1;
}

/* 出队 */
int deCQueue(sqQueue *cQueue, dataType *data) {
    if(cQueue->front == cQueue->rear){
        return 0;
    }
    *data = cQueue->base[cQueue->front];
    cQueue->front = (cQueue->front + 1) % MAXQSIZE;
    return 1;
}

/* 遍历队列 */
void cQueueTraverse(sqQueue cQueue) {
    int index = cQueue.front;
    while(index != cQueue.rear){
        printf("%d\n", cQueue.base[index]);
        index = (index + 1) % MAXQSIZE;
    }
}
