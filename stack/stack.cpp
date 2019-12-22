/*
 * stack
 */

#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* 初始化 stack */
int initStack(sqStack *s) {
    s->bottom = (dataType*)malloc(STACK_INIT_SIZE*sizeof(dataType));
    if(NULL == s->bottom)
    {
        return 0;
    }
    s->top = s->bottom;
    s->size = STACK_INIT_SIZE;
    return 1;
}

/* 销毁 stack */
int destroyStack(sqStack *s) {
    if (NULL != s->bottom){
        free(s->bottom);
        s->bottom = s->top = NULL;
    }
    s->size = 0;
    return 1;
}

/* 清空 stack */
int clearStack(sqStack *s) {
    if(NULL != s->bottom) {
        memset(s->bottom, 0, s->size * sizeof(dataType));
    }
    s->top = s->bottom;
    return 1;
}

/* stack 是否为空 */
int stackEmpty(sqStack *s) {
    if(s->top == s->bottom) {
        return 1;
    }else{
        return 0;
    }
}

/* stack 高度 */
int stackHeight(sqStack *s) {
    return s->top - s->bottom;
}

/* 获取栈顶元素 */
int top(sqStack *s, dataType *data) {
    if( s->top == s->bottom){
        return 0;
    }
    *data = *(s->top - 1);
    return 1; 
}

/* 入栈 */
int push(sqStack *s, dataType data) {
    if(stackHeight(s) >= s->size){  /* 栈满 */
        s->bottom = (dataType*)realloc(s->bottom, (s->size+STACK_INCREMENT)*sizeof(dataType));
        if(NULL == s->bottom){
            return 0;
        }
        s->top = s->bottom + s->size;
        s->size += STACK_INCREMENT;
    }
    *s->top = data;
    s->top++;
    return 1;
}

/* 出栈 */
int pop(sqStack *s, dataType *data) {
    if(s->top == s->bottom){
        return 0;
    }
    *data = *(--s->top);
    return 1;
}

/* 遍历栈 */
void stackTraverse(sqStack *s) {
    if(stackEmpty(s)){
        return;
    }
    int index = 0;
    
    while((s->top - index) != s->bottom){
        printf("%d\n", *(s->top - index -1));
        index++;
    }
}


int initStack2(linkedStack *s) {
    stackNode *rear = (stackNode*)malloc(sizeof(stackNode));    /* 产生尾结点 */
    if(NULL == rear){
        return 0;
    }
    s->top = s->bottom = rear;
    rear->next = NULL;
    s->height = 0;
    return 1;
}

int destroyStack2(linkedStack *s) {
    while(NULL != s->top){
        s->bottom = s->top;
        s->top = s->top->next;
        free(s->bottom);
        s->bottom = NULL;
    }
    s->height = 0;
    return 1;
}

int clearStack2(linkedStack *s) {
    if(s->top != s->bottom){
        stackNode *tmp = s->top;
        s->top = s->top->next;
        free(tmp);
        tmp = NULL;
    }
    s->height = 0;
    return 1;
}

int stackEmpty2(linkedStack *s) {
    if(s->top == s->bottom){
        return 1;
    }
    return 0;
}

int stackHeight2(linkedStack *s){
    return s->height;
}

int top2(linkedStack *s, dataType *data) {
    if(s->top == s->bottom){
        return 0;
    }
    *data = s->top->data;
    return 1;
}

int push2(linkedStack *s, dataType data) {
    stackNode *tmp = (stackNode*)malloc(sizeof(stackNode));
    if(NULL == tmp){
        return 0;
    }

    tmp->data = data;
    tmp->next = s->top;
    s->top = tmp;
    s->height++;
    return 1;
}

int pop2(linkedStack *s, dataType *data) {
    if(s->top == s->bottom) {
        return 0;
    }

    stackNode *tmp = s->top;
    *data = tmp->data;
    s->top = s->top->next;
    s->height--;
    free(tmp);
    tmp = NULL;
    return 1;
}

void stackTraverse2(linkedStack s) {
    stackNode *top = s.top;
    while(top != s.bottom){
        printf("%d\n", top->data);
        top = top->next;
    }
}