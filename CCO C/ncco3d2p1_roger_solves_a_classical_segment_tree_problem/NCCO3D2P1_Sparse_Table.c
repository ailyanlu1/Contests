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

#define MAXN 50005
#define MAXLGN 18

int N, Q, LG, minVal[MAXLGN][MAXN], maxVal[MAXLGN][MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ri(N);
    ri(Q);
    LG = 32 - __builtin_clz(N);
    FOR(i, N) {
        ri(minVal[0][i]);
        maxVal[0][i] = minVal[0][i];
    }
    FOR(i, LG - 1) {
        for (int j = 0; j + (1 << i) < N; j++) {
            minVal[i + 1][j] = min(minVal[i][j], minVal[i][j + (1 << i)]);
            maxVal[i + 1][j] = max(maxVal[i][j], maxVal[i][j + (1 << i)]);
        }
    }
    int l, r;
    FOR(q, Q) {
        ri(l);
        ri(r);
        l--; r--;
        int i = 31 - __builtin_clz(r - l + 1);
        printf("%d\n", max(maxVal[i][l], maxVal[i][r - (1 << i) + 1]) - min(minVal[i][l], minVal[i][r - (1 << i) + 1]));
    }
    return 0;
}
