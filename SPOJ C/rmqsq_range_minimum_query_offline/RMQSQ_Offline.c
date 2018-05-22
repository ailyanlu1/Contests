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

int N, Q, A[MAXN], ans[MAXQ], B[MAXN];
int *q[MAXQ];

int qcmp(const void *a, const void *b) {
    int *aa = *(int**) a;
    int *bb = *(int**) b;
    if (aa[0] != bb[0]) return bb[0] - aa[0];
    return aa[1] - bb[1];
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ri(N);
    FOR(i, N) ri(A[i]);
    A[N] = 0;
    ri(Q);
    FOR(i, Q) {
        q[i] = malloc(3 * sizeof(int));
        ri(q[i][0]);
        ri(q[i][1]);
        q[i][2] = i;
    }
    qsort(q, Q, sizeof(q[0]), qcmp);
    int k = 0;
    for (int i = 0, j = N; i < Q; i++) {
        while (j >= q[i][0]) {
            while (k > 0 && A[j] <= A[B[k - 1]]) k--;
            B[k++] = j--;
        }
        int lo = 0, hi = k - 1, mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (B[mid] >= q[i][1] + 1) lo = mid + 1;
            else hi = mid - 1;
        }
        ans[q[i][2]] = A[B[hi + 1]];
    }
    FOR(i, Q) printf("%d\n", ans[i]);
    return 0;
}
