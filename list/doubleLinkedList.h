/*
 * double linked list
 */

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int dataType;

/* linked storage structure */
typedef struct duLNode {
    dataType data;
    struct duLNode *prior;
    struct duLNode *next;
} duLNode, *duLinkedList;
/*
 * The list has a sentinel node. Status functions return 1 on success and 0
 * on failure. Positions are 1-based: get/delete use [1, length], and insert
 * uses [1, length + 1]. Output pointers must be non-NULL. Destruction is
 * safe to repeat and sets *list to NULL.
 */
int initDuList(duLinkedList *list);
int destroyDuList(duLinkedList *list);
int clearDuList(duLinkedList list);
int duListEmpty(duLinkedList list);
int duListLength(duLinkedList list);
int duListGet(duLinkedList list, int pos, dataType *data);
int duListInsert(duLinkedList list, int pos, dataType data);
int duListDelete(duLinkedList list, int pos, dataType *data);
void duListTraverse(duLinkedList list);

#ifdef __cplusplus
}
#endif

#endif
