#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <assert.h>
#include <stdarg.h>
#include <stddef.h>

#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rld(x) scanf("%Lf", &x)
#define rc(x) scanf(" %c", &x)
#define sc(x) do { scanf("%c", &x); } while (isspace(x))
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)

#define ll long long
#define ld long double

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
    bool ans = false;
    int a;
    FOR(i, M - 1) {
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
    For(i, M - 1, N) {
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
            ans = true;
            printf("%d\n", i - M + 2);
        }
    }
    if (!ans) printf("NONE\n");
    return 0;
}
