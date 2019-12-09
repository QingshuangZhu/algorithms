/*
* tree
*/

#ifndef TREE_H
#define TREE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef char dataType;

#define MAX_TREE_SIZE 100;

/* 树的双亲表存储表示 */
typedef struct pTNode {    /* 结点结构 */
    dataType data;
    int parent;            /* 双亲位置域 */
}pTNode;
typedef struct {           /* 树结构 */
    pTNode nodes[MAX_TREE_SIZE];
    int r;                 /* 根的位置 */
    int n;                 /* 结点数 */
}pTree;

/* 树的孩子链表存储表示 */
typedef struct cTNode {    /* 孩子结点 */
    int child;             /* 孩子位置域 */
    struct cTNode *next;
}child;
typedef struct {
    dataType data;
    child *firstChild;     /* 孩子链表头指针 */
}cTBox;
typedef struct {
    cTBox nodes[MAX_TREE_SIZE];
    int r;                 /* 根的位置 */
    int n;                 /* 结点数 */
}cTree;

/* 树的二叉链表（孩子-兄弟）存储表示 */
typedef struct cSNode {
    dataType data;
    struct cSNode *firstChild;
    struct cSNode *nextSibling;
}cSNode, *cSTree;

#ifdef __cplusplus
}
#endif

#endif
