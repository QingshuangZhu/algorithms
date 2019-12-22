/*
 * binary tree
 */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef char dataType;

/* linked storage structure */
typedef struct biTNode {
    dataType data;
    struct biTNode *lChild;
    struct biTNode *rChild;
} biTNode, *linkedBiTree;

int initBiTree(linkedBiTree *t);
int destroyBiTree(linkedBiTree t);
int createBiTree(linkedBiTree *t);
int clearBiTree(linkedBiTree t);
int biTreeEmpty(linkedBiTree t);
biTNode* root(linkedBiTree t);
int value(linkedBiTree t, biTNode *node);
int assign(linkedBiTree t, biTNode *node, dataType data);
biTNode* parent(linkedBiTree t, biTNode *node);
biTNode* leftChild(linkedBiTree t, biTNode *node);
biTNode* rightChild(linkedBiTree t, biTNode *node);
biTNode* leftSibling(linkedBiTree t, biTNode *node);
biTNode* rightSibling(linkedBiTree t, biTNode *node);
int insertChild(linkedBiTree t, biTNode *node, int lr, linkedBiTree child);
int deleteChild(linkedBiTree t, biTNode *node, int lr);

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