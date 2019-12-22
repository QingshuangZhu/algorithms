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