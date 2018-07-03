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

#define MAXRC 105

int R, C;
char grid[MAXRC][MAXRC];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ri(R);
    ri(C);
    FOR(i, R) rs(grid[i]);
    int cntSafe = 0;
    FOR(i, R) {
        FOR(j, C) {
            if (grid[i][j] == '.') {
                int cntGood = 0, cntBad = 0;
                For(ii, -1, 2) For(jj, -1, 2) if (0 <= i + ii && i + ii < R && 0 <= j + jj && j + jj < C && (ii || jj)) grid[i + ii][j + jj] == '.' ? cntGood++ : cntBad++;
                cntSafe += cntGood > cntBad;
            }
        }
    }
    printf("%d\n", cntSafe);
    return 0;
}
