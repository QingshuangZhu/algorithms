/*
 * cirular queue
 */

 #ifndef CIRCULAR_QUEUE_H
 #define CIRCULAR_QUEUE_H

 #define MAXQSIZE 100    /* 最大队列长度 */

 #ifdef __cplusplus
extern "C" {
#endif

typedef int dataType;

/* sequential storage sturcture */
typedef struct {
    dataType *base;
    int front;
    int rear;
} sqQueue;

int initCQueue(sqQueue *cQueue);
int destroyCQueue(sqQueue *cQueue);
int clearCQueue(sqQueue *cQueue);
int cQueueEmpty(sqQueue *cQueue);
int cQueueLength(sqQueue *cQueue);
int getHead(sqQueue *cQueue, dataType *data);
int enCQueue(sqQueue *cQueue, dataType data);
int deCQueue(sqQueue *cQueue, dataType *data);
void cQueueTraverse(sqQueue cQueue);

#ifdef __cplusplus
}
#endif

#endif