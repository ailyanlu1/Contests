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
#define BSZ 300

int N, Q, SMALL[MAXN], LARGE[MAXN / BSZ + 5];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ri(N);
    FOR(i, (N - 1) / BSZ + 1) LARGE[i] = INT_MAX;
    FOR(i, N) {
        ri(SMALL[i]);
        MIN(LARGE[i / BSZ], SMALL[i]);
    }
    ri(Q);
    int l, r, ans;
    FOR(i, Q) {
        ri(l);
        ri(r);
        ans = INT_MAX;
        while (l % BSZ && l <= r) {
            MIN(ans, SMALL[l]);
            l++;
        }
        while (l + BSZ <= r) {
            MIN(ans, LARGE[l / BSZ]);
            l += BSZ;
        }
        while (l <= r) {
            MIN(ans, SMALL[l]);
            l++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
