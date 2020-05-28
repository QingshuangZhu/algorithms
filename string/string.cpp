/*
 * pattern matching
 */

#include<stdlib.h>

/* brute force */
int bruteForce1(char *P, int m, char *T, int n){
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

    return i-j; 
}

int bruteForce2(char *P, int m, char *T, int n){
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
    return i;
}

/* KMP */
int* next(char *P, int m){
    int j = 0;                   /* "主"串指针 */
    int *N = (int*)malloc(m);    /* next表 */
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

int KMP(char *P, int m, char *T, int n){
    int *next = next(P, m);    /* 构造next表 */
    int i = 0;                 /* 文本串指针 */
    int j = 0;                 /* 模式串指针 */

    while(j < m && i < n){
        if(0 > j || T[i] == P[j]){
            i++;
            j++;
        }
        /* 否则，P右移，T不回退 */
        else{
            j = next[j];
        }
    }

    free(next);
    return i-j;
}
