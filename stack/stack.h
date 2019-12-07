/*
 * stack
 */

#ifndef STACK_H
#define STACK_H

#define STACK_INIT_SIZE 100    /* 栈初始大小 */
#define STACK_INCREMENT 10    /* 分配增量 */

#ifdef __cplusplus
extern "C" {
#endif

typedef int dataType;

/* sequential storage structure */
typedef struct {
    dataType *top;
    dataType *bottom;
    int size;   /* 当前分配的空间大小 */
} sqStack;
int initStack(sqStack *s);
int destroyStack(sqStack *s);
int clearStack(sqStack *s);
int stackEmpty(sqStack *s);
int stackHeight(sqStack *s);
int top(sqStack *s, dataType *data);
int push(sqStack *s, dataType data);
int pop(sqStack *s, dataType *data);
void stackTraverse(sqStack *s);

/* linked storage structure */
typedef struct sNode {
    dataType data;
    struct sNode *next;
} stackNode;
typedef struct {
    stackNode *top;
    stackNode *bottom;
    int height;   /* 栈的高度 */
} linkedStack;
int initStack2(linkedStack *s);
int destroyStack2(linkedStack *s);
int clearStack2(linkedStack *s);
int stackEmpty2(linkedStack *s);
int stackHeight2(linkedStack *s);
int top2(linkedStack *s, dataType *data);
int push2(linkedStack *s, dataType data);
int pop2(linkedStack *s, dataType *data);
void stackTraverse2(linkedStack s);

#ifdef __cplusplus
}
#endif

#endif