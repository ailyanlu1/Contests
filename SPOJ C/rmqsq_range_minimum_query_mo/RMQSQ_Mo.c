// http://www.spoj.com/problems/RMQSQ/
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

#define MAXN 100005
#define MAXQ 10005
#define BSZ 300

int N, Q, ans[MAXQ], sz = 0;
int *A[MAXN], *q[MAXQ], *pq[BSZ * MAXN];

void swim(int k) {
    while (k > 1 && pq[k / 2][0] > pq[k][0]) {
        int *temp = pq[k / 2];
        pq[k / 2] = pq[k];
        pq[k] = temp;
        k /= 2;
    }
}

void sink(int k) {
    while (2 * k <= sz) {
        int j = 2 * k;
        if (j < sz && pq[j][0] > pq[j + 1][0]) j++;
        if (pq[k][0] <= pq[j][0]) break;
        int *temp = pq[k];
        pq[k] = pq[j];
        pq[j] = temp;
        k = j;
    }
}

int *top() {
    return pq[1];
}

void push(int *x) {
    pq[++sz] = x;
    swim(sz);
}

void pop() {
    int *temp = pq[1];
    pq[1] = pq[sz];
    pq[sz] = temp;
    sz--;
    sink(1);
}

int qcmp(const void *a, const void *b) {
    int *aa = *(int**) a;
    int *bb = *(int**) b;
    if (aa[0] / BSZ != bb[0] / BSZ) return aa[0] / BSZ - bb[0] / BSZ;
    return aa[1] - bb[1];
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ri(N);
    FOR(i, N) {
        A[i] = malloc(2 * sizeof(int));
        ri(A[i][0]);
        A[i][1] = i;
    }
    A[N] = 0;
    ri(Q);
    FOR(i, Q) {
        q[i] = malloc(3 * sizeof(int));
        ri(q[i][0]);
        ri(q[i][1]);
        q[i][2] = i;
    }
    qsort(q, Q, sizeof(q[0]), qcmp);
    int l = q[0][0], r = l - 1;
    FOR(i, Q) {
        while (l < q[i][0]) l++;
        while (l > q[i][0]) push(A[--l]);
        while (r < q[i][1]) push(A[++r]);
        while (r > q[i][1]) r--;
        while (top()[1] < q[i][0] || top()[1] > q[i][1]) pop();
        ans[q[i][2]] = top()[0];
    }
    FOR(i, Q) printf("%d\n", ans[i]);
    return 0;
}
