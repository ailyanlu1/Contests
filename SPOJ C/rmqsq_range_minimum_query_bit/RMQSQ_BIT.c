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

int N, Q, A[MAXN], BIT[MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ri(N);
    FOR(i, N + 1) BIT[i] = INT_MAX;
    For(i, 1, N + 1) {
        ri(A[i]);
        for (int j = i; j <= N; j += j & -j) MIN(BIT[j], A[i]);
    }
    ri(Q);
    int l, r, ans;
    FOR(i, Q) {
        ri(l);
        ri(r);
        l++, r++;
        ans = INT_MAX;
        for (; l <= r; ) {
            if (l <= r - (r & -r) + 1) {
                MIN(ans, BIT[r]);
                r -= r & -r;
            } else {
                MIN(ans, A[r]);
                r--;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
