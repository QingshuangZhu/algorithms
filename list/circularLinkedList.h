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
/*
 * A cLinkedList value is the tail pointer; tail->next is the sentinel.
 * Status functions return 1 on success and 0 on failure. Positions are
 * 1-based: get/delete use [1, length], and insert uses [1, length + 1].
 * Output pointers must be non-NULL. Destruction is safe to repeat.
 */
int initCList(cLinkedList *list);
int destroyCList(cLinkedList *list);
int clearCList(cLinkedList list);
int cListEmpty(cLinkedList list);
int cListLength(cLinkedList list);
int cListGet(cLinkedList list, int pos, dataType *data);
int cListInsert(cLinkedList *list, int pos, dataType data);
int cListDelete(cLinkedList *list, int pos, dataType *data);
/*
 * Builds a newly allocated deep copy of list1 followed by list2. The inputs
 * remain unchanged. On success *list3 owns the result and must be destroyed;
 * on failure *list3 is unchanged. An existing value in *list3 is not freed.
 */
int cListAttach(cLinkedList list1, cLinkedList list2, cLinkedList *list3);
void cListTraverse(cLinkedList list);

#ifdef __cplusplus
}
#endif

#endif
