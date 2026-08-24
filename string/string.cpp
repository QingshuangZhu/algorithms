/*
 * pattern matching
 */

#include "patternMatching.h"

#include <stdint.h>
#include <stdlib.h>

/* brute force */
int bruteForce1(const char *P, int m, const char *T, int n){
    if(m < 0 || n < 0){
        return -1;
    }
    if((m > 0 && NULL == P) || (n > 0 && NULL == T)){
        return -1;
    }
    if(0 == m){
        return 0;
    }
    if(m > n){
        return -1;
    }

    int i = 0;
    int j = 0;

    /* 自左向右逐个对比字符串 */
    while(j < m && i < n){
        /* 如匹配，则转到下一个字符 */
        if(T[i]  == P[j]){
            i++;
            j++;
        }
        /* 否则，T回退，P复位 */
        else{
            i -= j-1;
            j = 0;
        }
    }

    return j == m ? i-j : -1;
}

int bruteForce2(const char *P, int m, const char *T, int n){
    if(m < 0 || n < 0){
        return -1;
    }
    if((m > 0 && NULL == P) || (n > 0 && NULL == T)){
        return -1;
    }
    if(0 == m){
        return 0;
    }
    if(m > n){
        return -1;
    }

    int i = 0;
    int j = 0;

    for(i=0; i <= n-m; i++){
        for(j=0; j < m; j++){
            if(T[i+j] != P[j])
                break;
        }
        if(m <= j)
            break;
    }
    return i <= n-m ? i : -1;
}

/* KMP */
static int *buildNext(const char *P, int m){
    if((size_t)m > SIZE_MAX/sizeof(int)){
        return NULL;
    }

    int j = 0;                   /* "主"串指针 */
    int *N = (int*)malloc((size_t)m*sizeof(int));    /* next表 */
    if(NULL == N){
        return NULL;
    }
    int t = N[0] = -1;           /* 模式串指针（P[-1]通配符）*/

    while(j < m-1){
        /* 匹配 */
        if(0 > t || P[j] == P[t]){
            N[++j] = ++t;
 
            /* 改进 */
            /* j++;
             * t++;
             * N[j] = P[j] != P[t] ? t : N[t];
             */
        }
        /* 失配 */
        else{
            t = N[t];
        }
    }
    return N;
}

int KMP(const char *P, int m, const char *T, int n){
    if(m < 0 || n < 0){
        return -1;
    }
    if((m > 0 && NULL == P) || (n > 0 && NULL == T)){
        return -1;
    }
    if(0 == m){
        return 0;
    }
    if(m > n){
        return -1;
    }

    int *nextTable = buildNext(P, m);    /* 构造next表 */
    if(NULL == nextTable){
        return -1;
    }
    int i = 0;                 /* 文本串指针 */
    int j = 0;                 /* 模式串指针 */

    while(j < m && i < n){
        if(0 > j || T[i] == P[j]){
            i++;
            j++;
        }
        /* 否则，P右移，T不回退 */
        else{
            j = nextTable[j];
        }
    }

    free(nextTable);
    return j == m ? i-j : -1;
}
