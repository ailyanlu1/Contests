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

#define MAXN 1000005
#define MAXQ 100005
#define BSZ 1000

int N, K, Q, A[MAXN + BSZ], ind[MAXN], rind[MAXN + BSZ], freeInd, q[MAXQ][2], front, back, dq[MAXN], smallAns[MAXN + BSZ], exclude[MAXN + BSZ];

int intCmp(const void *a, const void *b) {
    return *(int*) a - *(int*) b;
}

int slide(int l, int r, int checkRev) {
    front = 0;
    back = -1;
    int ans = 0;
    For(i, l, r + 1) {
        while (front <= back && rind[dq[front]] <= rind[i] - K) front++;
        if (front <= back) {
            if (exclude[i]) MAX(smallAns[ind[i]], A[dq[front]]);
            else MAX(ans, A[i] + A[dq[front]]);
        }
        if (!exclude[i]) {
            while (front <= back && A[dq[back]] <= A[i]) back--;
            dq[++back] = i;
        }
    }
    if (checkRev) {
        front = 0;
        back = -1;
        Rev(i, r, l - 1) {
            while (front <= back && rind[i] + K <= rind[dq[front]]) front++;
            if (front <= back && exclude[i]) MAX(smallAns[ind[i]], A[dq[front]]);
            if (!exclude[i]) {
                while (front <= back && A[dq[back]] <= A[i]) back--;
                dq[++back] = i;
            }
        }
    }
    return ans;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    memset(exclude, 0, sizeof(exclude));
    ri(N);
    ri(K);
    ri(Q);
    FOR(i, N) {
        ri(A[i]);
        rind[i] = i;
    }
    freeInd = N;
    q[0][0] = 0;
    q[0][1] = A[0];
    For(i, 1, Q + 1) {
        ri(q[i][0]);
        q[i][0]--;
        ri(q[i][1]);
    }
    int curAnsLarge = 0;
    int curFreeInd = freeInd;
    FOR(i, Q + 1) {
        if (i % BSZ == 0) {
            freeInd = curFreeInd;
            For(j, i, min(i + BSZ, Q + 1)) {
                if (!exclude[q[j][0]]) {
                    rind[freeInd++] = q[j][0];
                    exclude[q[j][0]] = 1;
                }
            }
            qsort(rind + curFreeInd, freeInd - curFreeInd, sizeof(rind[0]), intCmp);
            For(j, curFreeInd, freeInd) {
                ind[rind[j]] = j;
                A[j] = A[rind[j]];
                smallAns[j] = 0;
            }
            curAnsLarge = slide(0, N - 1, 1);
            For(j, i, min(i + BSZ, Q + 1)) exclude[q[j][0]] = 0;
        }
        A[q[i][0]] = A[ind[q[i][0]]] = q[i][1];
        int ans = slide(curFreeInd, freeInd - 1, 0);
        MAX(ans, curAnsLarge);
        For(j, curFreeInd, freeInd) MAX(ans, A[j] + smallAns[j]);
        printf("%d\n", ans);
    }
    return 0;
}
