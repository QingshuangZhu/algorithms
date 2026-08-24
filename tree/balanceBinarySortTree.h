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

/*
 * Perform structural rotations without updating any node's bf field.
 * rRotate is a no-op without a root and left child; lRotate is a no-op
 * without a root and right child.
 */
void rRotate(bBSTNodeTree *p);
void lRotate(bBSTNodeTree *p);

#ifdef __cplusplus
}
#endif

#endif
