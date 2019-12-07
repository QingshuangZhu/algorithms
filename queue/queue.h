/*
 * queue
 */

#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int dataType;

/* linked storage structure */
typedef struct qNode {
    dataType data;
    struct qNode *next;
} qNode;
typedef struct {
    qNode *front;
    qNode *rear;
    int length;    /* 队列长度 */
} linkedQueue;

int initQueue(linkedQueue *q);
int destroyQueue(linkedQueue *q);
int clearQueue(linkedQueue *q);
int queueEmpty(linkedQueue *q);
int queueLength(linkedQueue *q);
int getHead(linkedQueue *q, dataType *data);
int enQueue(linkedQueue *q, dataType data);
int deQueue(linkedQueue *q, dataType *data);
void queueTraverse(linkedQueue q);

#ifdef __cplusplus
}
#endif

#endif