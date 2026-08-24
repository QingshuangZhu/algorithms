/*
 * list
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

/*
 * Linked lists use a sentinel node. Functions returning a status use 1 for
 * success and 0 for failure. Positions are 1-based: get/delete accept
 * [1, length], and insert accepts [1, length + 1]. Output pointers must be
 * non-NULL. destroyList is safe to repeat and sets *list to NULL.
 */
int initList(linkedList *list);
int destroyList(linkedList *list);
int clearList(linkedList list);
int listEmpty(linkedList list);
int listLength(linkedList list);
int listGet(linkedList list, int pos, dataType *data);
int listInsert(linkedList list, int pos, dataType data);
int listDelete(linkedList list, int pos, dataType *data);
/*
 * Builds a newly allocated deep copy of list1 followed by list2. The inputs
 * remain unchanged. On success *list3 owns the result and must be destroyed;
 * on failure *list3 is unchanged. An existing value in *list3 is not freed.
 */
int listAttach(linkedList list1, linkedList list2, linkedList *list3);
int listReverse(linkedList list);
void listTraverse(linkedList list);
/* Sorts in place without allocation and returns the original sentinel. */
linkedList listSort(linkedList list);

/* sequential storage structure */
typedef struct {
    dataType *base;
    int length;
    int size;    /* 当前分配的空间大小 */
}sqList;
/*
 * Sequential-list positions and 1/0 status returns follow the rules above.
 * If listInsert2 cannot grow the allocation, the list remains unchanged.
 */
int initList2(sqList *list);
int destroyList2(sqList *list);
void clearList2(sqList *list);
int listEmpty2(sqList list);
int listLength2(sqList list);
int listGet2(sqList list, int pos, dataType *data);
int listInsert2(sqList *list, int pos, dataType data);
int listDelete2(sqList *list, int pos, dataType *data);
/*
 * Replaces *list3 with an owned concatenation of list1 and list2. list3 may
 * be the same object as either input, but it must point to an initialized
 * sqList. On allocation failure *list3 is unchanged; on success its previous
 * allocation is released. An empty result retains the current allocation so
 * that it can be reused by listInsert2.
 */
int listAttach2(sqList list1, sqList list2, sqList *list3);
int listReverse2(sqList list);
void listTraverse2(sqList list);

#ifdef __cplusplus
}
#endif

#endif
