/*
 * binary tree
 */

#include "binaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>

/* 构造 binary tree */
int createBiTree(linkedBiTree *t) {
    /* 按先序次序构造binary tree */
    dataType data;
    scanf("%c", &data);
    if('#' == data){    /* #字符表示空树 */
        *t = NULL;
    }else{
        *t = (linkedBiTree)malloc(sizeof(biTNode));    /* 生成根结点 */
        if(NULL == *t){
            return 0;
        }
        (*t)->data = data;
        createBiTree(&(*t)->lChild);                  /* 构造左子树 */
        createBiTree(&(*t)->rChild);                  /* 构造右子树 */
    }
    return 1;
}

/* 树的深度 */
int biTreeDepth(linkedBiTree t) {
    int lDepth = 0;
    int rDepth = 0;

    if(NULL == t){
        return 0;
    }
    
    lDepth = biTreeDepth(t->lChild);
    rDepth = biTreeDepth(t->rChild);
    return (lDepth > rDepth) ? (lDepth+1) : (rDepth+1);
}

/* 树的叶子结点个数 */
int biTreeLeaf(linkedBiTree t) {
    if(NULL == t){
        return 0;
    }

    if(NULL == t->lChild && NULL == t->rChild){
        return 1;
    }

    return biTreeLeaf(t->lChild) + biTreeLeaf(t->rChild);
}
 
/* 反转二叉树递归实现 */
void biTreeReverse(linkedBiTree t) {
    if(NULL == t){
        return;
    }

    linkedBiTree p = t->lChild;
    t->lChild = t->rChild;
    t->rChild = p;

    biTreeReverse(t->lChild);
    biTreeReverse(t->rChild);
}

/* 反转二叉树的非递归实现 */
void biTreeReverse2(linkedBiTree t) {
    std::stack<linkedBiTree> s;
    s.push(t);

    while(!s.empty()){
        linkedBiTree p = s.top();
        linkedBiTree tmp = p->lChild;
        p->lChild = p->rChild;
        p->rChild = tmp;
        s.pop();

        if(p->lChild){
            s.push(p->lChild);
        }
        if(p->rChild){
            s.push(p->rChild);
        }
    }
}

/* 先序遍历的递归实现 */
void preOrderTraverse(linkedBiTree t) {
    if(NULL != t){
        printf("%c\n", t->data);
        preOrderTraverse(t->lChild);
        preOrderTraverse(t->rChild);
    }
}

/* 先序遍历的非递归实现 */
void preOrderTraverse2(linkedBiTree t) {
    std::stack<linkedBiTree> s;
    linkedBiTree p = t;

    while(p || !s.empty()){
        if(p){    /* 根指针进栈，访问根节点，遍历左子树 */
            s.push(p);
            printf("%c\n", p->data);
            p = p->lChild;
        }else{    /* 根指针退栈，遍历右子树 */
            p = s.top();
            s.pop();
            p = p->rChild;
        }
    }
}

/* 中序遍历的递归实现 */
void inOrderTraverse(linkedBiTree t) {
    if(NULL != t){
        inOrderTraverse(t->lChild);
        printf("%c\n", t->data);
        inOrderTraverse(t->rChild);
    }
}

/* 中序遍历的非递归实现 */
void inOrderTraverse2(linkedBiTree t) {
    std::stack<linkedBiTree> s;
    linkedBiTree p = t;

    while(p || !s.empty()){
        if(p){    /* 根指针进栈，遍历左子树 */
            s.push(p);
            p = p->lChild;
        }else{    /* 根指针退栈，访问根结点，遍历右子树 */
            p = s.top();
            printf("%c\n", p->data);
            s.pop();
            p = p->rChild;
        }
    }
}

/* 后序遍历的递归实现 */
void postOrderTraverse(linkedBiTree t) {
    if(NULL != t){
        postOrderTraverse(t->lChild);
        postOrderTraverse(t->rChild);
        printf("%c\n", t->data);
    }
}

/* 后序遍历的非递归实现 */
void postOrderTraverse2(linkedBiTree t) {
    std::stack<linkedBiTree> s;
    linkedBiTree cur = NULL;
    linkedBiTree pre = NULL;
    s.push(t);

    while(!s.empty()){
        cur = s.top();
        /* 当前结点没有孩子结点，或孩子结点都已经被访问 */
        if(((NULL == cur->lChild) && (NULL == cur->rChild)) || 
           ((NULL != pre) && ((pre == cur->lChild) || (pre == cur->rChild)))) {
               printf("%c\n", cur->data);
               s.pop();
               pre = cur;
           }else{
               if(cur->rChild){
                   s.push(cur->rChild);
               }
               if(cur->lChild){
                   s.push(cur->lChild);
               }
           }
    }
}

/* 层序遍历 */
void levelOrderTraverse(linkedBiTree t) {
    if(t){
        std::queue<linkedBiTree> q;
        linkedBiTree p = NULL;
        q.push(t);

        while(!q.empty()){
            p = q.front();
            printf("%c\n", p->data);
            q.pop();
            if(p->lChild){
                q.push(p->lChild);
            }
            if(p->rChild){
                q.push(p->rChild);
            }
        }
    }
}