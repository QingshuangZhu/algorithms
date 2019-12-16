/*
 * circular linked list
 */

#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int dataType;

/* linked storage structure */
typedef struct cLNode {
    dataType data;
    struct cLNode *next;
} cLNode, *cLinkedList;
int initCList(cLinkedList *list);
int destroyCList(cLinkedList *list);
int clearCList(cLinkedList list);
int cListEmpty(cLinkedList list);
int cListLength(cLinkedList list);
int cListGet(cLinkedList list, int pos, dataType *data);
int cListInsert(cLinkedList *list, int pos, dataType data);
int cListDelete(cLinkedList *list, int pos, dataType *data);
int cListAttach(cLinkedList list1, cLinkedList list2, cLinkedList *list3);
void cListTraverse(cLinkedList list);

#ifdef __cplusplus
}
#endif

#endif