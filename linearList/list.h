/*
 * linear list
 */

#ifndef LIST_H
#define LIST_H

#define LIST_INIT_SIZE 100    /* 线性表初始大小 */
#define LIST_INCREMENT 10    /* 分配增量 */

#ifdef __cplusplus
extern "C" {
#endif

typedef int dataType;

/* linked storage structure */
typedef struct lNode {
    dataType data;
    struct lNode *next;
} lNode, *linkedList;
int initList(linkedList *list);
int destroyList(linkedList *list);
int clearList(linkedList list);
int listEmpty(linkedList list);
int listLength(linkedList list);
int listGet(linkedList list, int pos, dataType *data);
int listInsert(linkedList list, int pos, dataType data);
int listDelete(linkedList list, int pos, dataType *data);
int listAttach(linkedList list1, linkedList list2, linkedList *list3);
int listReverse(linkedList list);
void listTraverse(linkedList list);

/* sequential storage structure */
typedef struct {
    dataType *base;
    int length;
    int size;    /* 当前分配的空间大小 */
}sqList;
int initList2(sqList *list);
int destroyList2(sqList *list);
void clearList2(sqList *list);
int listEmpty2(sqList list);
int listLength2(sqList list);
int listGet2(sqList list, int pos, dataType *data);
int listInsert2(sqList *list, int pos, dataType data);
int listDelete2(sqList *list, int pos, dataType *data);
int listAttach2(sqList list1, sqList list2, sqList *list3);
int listReverse2(sqList list);
void listTraverse2(sqList list);

#ifdef __cplusplus
}
#endif

#endif