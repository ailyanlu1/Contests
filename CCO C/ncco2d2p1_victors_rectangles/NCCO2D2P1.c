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

#define x f
#define y s
#define y1 _y1

#define MAXN 1505
#define MAXK 1125005

int N, X[MAXN], Y[MAXN], x1[MAXK], y1[MAXK], x2[MAXK], y2[MAXK], A[MAXK];
ll diag[MAXK];

int cmp(const void *i, const void *j) {
    if (diag[*(int*)i] > diag[*(int*)j]) return -1;
    else if (diag[*(int*)i] < diag[*(int*)j]) return 1;
    else return (x1[*(int*)i] + x2[*(int*)i]) - (x1[*(int*)j] + x2[*(int*)j]);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    scanf("%d", &N);
    int K = 0;
    FOR(i, N) {
        scanf("%d %d", &X[i], &Y[i]);
        FOR(j, i) {
            x1[K] = X[i];
            y1[K] = Y[i];
            x2[K] = X[j];
            y2[K] = Y[j];
            ll dx = X[i] - X[j], dy = Y[i] - Y[j];
            diag[K] = dx * dx + dy * dy;
            A[K] = K;
            K++;
        }
    }
    qsort(A, K, sizeof(int), cmp);
    ll ans = 0;
    FOR(i, K) {
        int ii = A[i];
        ll dii = diag[ii];
        int sx1x2 = x1[ii] + x2[ii];
        int sy1y2 = y1[ii] + y2[ii];
        if (dii <= ans * 2) break;
        For(j, i + 1, K) {
            int jj = A[j];
            if (dii != diag[jj] || sx1x2 != x1[jj] + x2[jj]) break;
            if (sy1y2 != y1[jj] + y2[jj]) continue;
            ll dx1 = x1[ii] - x1[jj], dy1 = y1[ii] - y1[jj], dx2 = x1[ii] - x2[jj], dy2 = y1[ii] - y2[jj];
            ll area = sqrt(dx1 * dx1 + dy1 * dy1) * sqrt(dx2 * dx2 + dy2 * dy2);
            MAX(ans, area);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
