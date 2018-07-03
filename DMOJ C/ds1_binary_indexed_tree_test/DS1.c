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

#define MAXNV 100005
#define BSZ 300

int N, M, cntSmall[MAXNV], cntLarge[MAXNV / BSZ + 5];
ll sumSmall[MAXNV], sumLarge[MAXNV / BSZ + 5];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ri(N);
    ri(M);
    memset(cntSmall, 0, sizeof(cntSmall));
    memset(cntLarge, 0, sizeof(cntLarge));
    memset(sumSmall, 0, sizeof(sumSmall));
    memset(sumLarge, 0, sizeof(sumLarge));
    int x, y;
    For(i, 1, N + 1) {
        ri(x);
        sumSmall[i] += x;
        sumLarge[i / BSZ] += sumSmall[i];
        cntSmall[sumSmall[i]]++;
        cntLarge[sumSmall[i] / BSZ]++;
    }
    char op;
    FOR(i, M) {
        rc(op);
        if (op == 'C') {
            ri(x);
            ri(y);
            cntSmall[sumSmall[x]]--;
            cntLarge[sumSmall[x] / BSZ]--;
            sumLarge[x / BSZ] += y - sumSmall[x];
            sumSmall[x] = y;
            cntSmall[y]++;
            cntLarge[y / BSZ]++;
        } else if (op == 'S') {
            ri(x);
            ri(y);
            ll ans = 0;
            while (x % BSZ && x <= y) ans += sumSmall[x++];
            while (x + BSZ - 1 <= y) {
                ans += sumLarge[x / BSZ];
                x += BSZ;
            }
            while (x <= y) ans += sumSmall[x++];
            printf("%lld\n", ans);
        } else if (op == 'Q') {
            x = 1;
            ri(y);
            int ans = 0;
            while (x % BSZ && x <= y) ans += cntSmall[x++];
            while (x + BSZ - 1 <= y) {
                ans += cntLarge[x / BSZ];
                x += BSZ;
            }
            while (x <= y) ans += cntSmall[x++];
            printf("%d\n", ans);
        } else {
            i--;
        }
    }
    return 0;
}
