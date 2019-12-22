/*
 * tree
 */

#ifndef BALANCE_BINARY_SORT_TREE_H
#define BALANCE_BINARY_SORT_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int dataType;

/* linked storage structure */
typedef struct bBSTNode {
    dataType data;
    int bf;                    /* 结点的平衡因子 */
    struct bBSTNode *lChild;
    struct bBSTNode *rChild;
} bBSTNode, *bBSTNodeTree;

void rRotate(bBSTNodeTree *p);
void lRotate(bBSTNodeTree *p);

#ifdef __cplusplus
}
#endif

#endif
