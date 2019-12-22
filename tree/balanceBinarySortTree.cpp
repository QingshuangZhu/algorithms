/*
 * balance binary sort tree
*/

#include "balanceBinarySortTree.h"

/* 
 * 对以*p为根的子树作右旋，处理后*p指向新的子树根，
 * 即右旋前的左子树的根结点
 */
void rRotate(bBSTNodeTree *p) {
    bBSTNodeTree lc = (*p)->lChild;    /* lc指向*p的左子树根结点 */
    (*p)->lChild = lc->rChild;         /* lc的右子树挂接为*p的左子树 */
    lc->rChild = *p;                   /* *p挂接为lc的右子树 */
    *p = lc;                           /* p指向新的根结点 */
}

/*
 * 对以*p为根的子树作左旋，处理后*p指向新的子树根，
 * 即右旋前的右子树的根结点
 */
void lRotate(bBSTNodeTree *p) {
    bBSTNodeTree rc = (*p)->rChild;     /* rc指向*p右子树根结点 */
    (*p)->rChild = rc->lChild;          /* rc的左子树挂接为*p的右子树 */
    rc->lChild = *p;                    /* *p挂接为rc的左子树 */
    *p = rc;                            /* p指向新的根结点 */
}