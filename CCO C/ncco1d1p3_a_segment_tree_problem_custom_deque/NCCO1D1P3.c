#include <stdio.h>

#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

#define MAXM 10005

int N, M, C, minA[MAXM], minB[MAXM], maxA[MAXM], maxB[MAXM], minFirst, minLast, maxFirst, maxLast;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    scan(N);
    scan(M);
    scan(C);
    minFirst = minLast = maxFirst = maxLast = -1;
    char ans = 0;
    int a;
    for (int i = 0; i < M - 1; i++) {
        scan(a);
        while (minFirst != -1 && minB[minLast] >= a) {
            if (minFirst == minLast) minFirst = minLast = -1;
            else if (minLast == 0) minLast = M - 1;
            else minLast--;
        }
        while (maxFirst != -1 && maxB[maxLast] <= a) {
            if (maxFirst == maxLast) maxFirst = maxLast = -1;
            else if (maxLast == 0) maxLast = M - 1;
            else maxLast--;
        }
        if (minFirst == -1) minFirst = minLast = 0;
        else if (minLast == M - 1) minLast = 0;
        else minLast++;
        if (maxFirst == -1) maxFirst = maxLast = 0;
        else if (maxLast == M - 1) maxLast = 0;
        else maxLast++;
        minA[minLast] = maxA[maxLast] = i;
        minB[minLast] = maxB[maxLast] = a;
    }
    for (int i = M - 1; i < N; i++) {
        scan(a);
        while (minFirst != -1 && minA[minFirst] <= i - M) {
            if (minFirst == minLast) minFirst = minLast = -1;
            else if (minFirst == M - 1) minFirst = 0;
            else minFirst++;
        }
        while (maxFirst != -1 && maxA[maxFirst] <= i - M) {
            if (maxFirst == maxLast) maxFirst = maxLast = -1;
            else if (maxFirst == M - 1) maxFirst = 0;
            else maxFirst++;
        }
        while (minFirst != -1 && minB[minLast] >= a) {
            if (minFirst == minLast) minFirst = minLast = -1;
            else if (minLast == 0) minLast = M - 1;
            else minLast--;
        }
        while (maxFirst != -1 && maxB[maxLast] <= a) {
            if (maxFirst == maxLast) maxFirst = maxLast = -1;
            else if (maxLast == 0) maxLast = M - 1;
            else maxLast--;
        }
        if (minFirst == -1) minFirst = minLast = 0;
        else if (minLast == M - 1) minLast = 0;
        else minLast++;
        if (maxFirst == -1) maxFirst = maxLast = 0;
        else if (maxLast == M - 1) maxLast = 0;
        else maxLast++;
        minA[minLast] = maxA[maxLast] = i;
        minB[minLast] = maxB[maxLast] = a;
        if (maxB[maxFirst] - minB[minFirst] <= C) {
            ans = 1;
            printf("%d\n", i - M + 2);
        }
    }
    if (!ans) printf("NONE\n");
    return 0;
}
