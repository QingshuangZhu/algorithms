/*
 * pattern matching
 */

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