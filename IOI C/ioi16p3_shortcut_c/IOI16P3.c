/*
 * IOI16P3.c
 *
 *  Created on: Aug 11, 2017
 *      Author: Wesley Leung
 */

#include <stdio.h>
#include <stdlib.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
#define mid(x, y) (x + (y - x) / 2)
#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) (rand() % (b - a + 1) + a)

typedef long long ll;
typedef unsigned long long llu;

#define MAXN 1000005

int N, C, q[MAXN];
ll loSum, hiSum, loDif, hiDif;
// station info
ll start[MAXN], sum[MAXN], dif[MAXN], maxSum[MAXN], minDif[MAXN];

int trial(ll len) {
    loSum = loDif = -LL_INF;
    hiSum = hiDif = LL_INF;
    int l = -1, r = 0, ql = 0, qr = 0;
    while (r < N) {
        if (l == q[ql]) ql++;
        while (ql < qr && dif[q[ql]] < sum[r] - len) {
            if (q[ql] == ++l) ql++;
        }
        if (l >= 0) {
            loSum = max(loSum, maxSum[l] + sum[r] + C - len);
            hiSum = min(hiSum, minDif[l] + dif[r] - C + len);
            loDif = max(loDif, maxSum[l] - dif[r] + C - len);
            hiDif = min(hiDif, minDif[l] - sum[r] - C + len);
        }
        while (ql < qr && dif[q[qr - 1]] >= dif[r]) {
            qr--;
        }
        q[qr++] = r++;
    }
    if (loSum > hiSum || loDif > hiDif) return 0;
    l = 0, r = 1;
    while (r < N) {
        while (l < r && start[l] + start[r] <= hiSum && start[l] - start[r] <= hiDif) {
            l++;
        }
        while (l > 0 && (start[l] + start[r] > hiSum || start[l] - start[r] > hiDif)) {
            l--;
        }
        if (start[l] + start[r] >= loSum && start[l] + start[r] <= hiSum && start[l] - start[r] >= loDif && start[l] - start[r] <= hiDif) return 1;
        r++;
    }
    return 0;
}

long long find_shortcut(int n, int l[], int d[], int c) {
    N = n;
    C = c;
    start[0] = 0;
    sum[0] = maxSum[0] = d[0];
    dif[0] = minDif[0] = -d[0];
    int i = 0;
    for (i = 1; i < n; i++) {
        start[i] = start[i - 1] + l[i - 1];
        sum[i] = start[i] + d[i];
        dif[i] = start[i] - d[i];
        maxSum[i] = max(maxSum[i - 1], sum[i]);
        minDif[i] = min(minDif[i - 1], dif[i]);
    }
    ll lo = 0LL;
    ll hi = maxSum[n - 1] << 1;
    while (lo < hi) {
        ll mid = mid(lo, hi);
        if (trial(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    int n, c;
    ri(n);
    ri(c);
    int l[n - 1], d[n];
    int i = 0;
    for (i = 0; i < n - 1; i++) {
        ri(l[i]);
    }
    for (i = 0; i < n; i++) {
        ri(d[i]);
    }
    printf("%lld\n", find_shortcut(n, l, d, c));
    return 0;
}
