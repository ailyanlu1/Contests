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

int N, K, Q, A[MAXN], T[MAXN * 2], IND[MAXN * 2];

void updateT(int i, int v) {
    for (T[i += N] = v; i >>= 1;) T[i] = max(T[i << 1], T[i << 1 | 1]);
}

void updateIND(int i) {
    for (i += N; i >>= 1;) IND[i] = A[IND[i << 1]] > A[IND[i << 1 | 1]] ? IND[i << 1] : IND[i << 1 | 1];
}

int queryIND(int l, int r) {
    if (l > r) return N;
    int q = N;
    for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
        if (l & 1) {
            q = A[q] > A[IND[l]] || (A[q] == A[IND[l]] && q > IND[l]) ? q : IND[l];
            l++;
        }
        if (!(r & 1)) {
            q = A[q] > A[IND[r]] || (A[q] == A[IND[r]] && q > IND[r]) ? q : IND[r];
            r--;
        }
    }
    return q;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ri(N);
    ri(K);
    ri(Q);
    FOR(i, N) {
        ri(A[i]);
        IND[N + i] = i;
        T[i] = 0;
    }
    A[N] = 0;
    For(i, N, 2 * N) T[i] = 0;
    Rev(i, N - 1, 0) IND[i] = A[IND[i << 1]] > A[IND[i << 1 | 1]] ? IND[i << 1] : IND[i << 1 | 1];
    int l, r, l2, r2, j, x;
    FOR(i, N) {
        l = queryIND(max(0, i - K + 1), i - 1), r = queryIND(i + 1, min(i + K - 1, N - 1));
        if (A[i] >= A[l] && A[i] > A[r]) updateT(i, A[i] + max(A[l], A[r]));
    }
    int lastAns = T[1];
    printf("%d\n", lastAns);
    FOR(i, Q) {
        ri(j);
        ri(x);
        j ^= lastAns;
        x ^= lastAns;
        A[--j] = x;
        updateIND(j);
        l = queryIND(max(0, j - K + 1), j - 1), r = queryIND(j + 1, min(j + K - 1, N - 1));
        if (A[j] >= A[l] && A[j] > A[r]) updateT(j, A[j] + max(A[l], A[r]));
        else {
            updateT(j, 0);
            if (l < N) {
                l2 = queryIND(max(0, l - K + 1), l - 1), r2 = queryIND(l + 1, min(l + K - 1, N - 1));
                if (A[l] >= A[l2] && A[l] > A[r2]) updateT(l, A[l] + max(A[l2], A[r2]));
            }
            if (r < N) {
                l2 = queryIND(max(0, r - K + 1), r - 1), r2 = queryIND(r + 1, min(r + K - 1, N - 1));
                if (A[r] >= A[l2] && A[r] > A[r2]) updateT(r, A[r] + max(A[l2], A[r2]));
            }
        }
        lastAns = T[1];
        printf("%d\n", lastAns);
    }
    return 0;
}
