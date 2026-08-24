/*
 * binary tree
 */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef char biTreeDataType;

/* linked storage structure */
typedef struct biTNode {
    biTreeDataType data;
    struct biTNode *lChild;
    struct biTNode *rChild;
} biTNode, *linkedBiTree;

/*
 * Read a preorder representation from stdin, using '#' for an empty node.
 * The output pointer must not already own a tree. On input or allocation
 * failure, return 0, release any partial tree, and set *t to NULL. On success,
 * the caller owns all returned nodes. This repository provides no public
 * destroy helper; the caller must release every node with free(), normally
 * by a postorder traversal.
 */
int createBiTree(linkedBiTree *t);

/* Other binary-tree ADT operation names are notes-only; see tree.md. */

int biTreeDepth(linkedBiTree t);
int biTreeLeaf(linkedBiTree t);
void biTreeReverse(linkedBiTree t);
void biTreeReverse2(linkedBiTree t);
void preOrderTraverse(linkedBiTree t);
void preOrderTraverse2(linkedBiTree t);
void inOrderTraverse(linkedBiTree t);
void inOrderTraverse2(linkedBiTree t);
void postOrderTraverse(linkedBiTree t);
void postOrderTraverse2(linkedBiTree t);
void levelOrderTraverse(linkedBiTree t);

#ifdef __cplusplus
}
#endif

#endif
