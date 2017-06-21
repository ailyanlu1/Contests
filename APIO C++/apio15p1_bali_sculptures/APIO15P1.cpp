/*
 * APIO15P1.cpp
 *
 *  Created on: Jun 20, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf("%c", &x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

#define MAXN_SMALL 100
#define MAXN_LARGE 2000

int N, A, B;
ll Y[MAXN_LARGE + 1];

int dp1[MAXN_LARGE + 1], dp2[MAXN_SMALL + 1][MAXN_SMALL + 1];
ll beauty;

int f1(int x) {
    if (x == 0) return 0;
    if (~dp1[x]) return dp1[x];
    int ret = 1e9;
    for (int j = x - 1; j >= 0; j--) {
        if (((~beauty) & (Y[x] - Y[j])) == 0) {
            ret = min(ret, f1(j) + 1);
        }
    }
    return dp1[x] = ret;
}

int f2(int pos, int group) {
    if (pos == 0) return group <= B && group >= A;
    if (~dp2[pos][group]) return dp2[pos][group];
    int t = 0;
    for (int j = pos - 1; j >= 0; j--) {
        if (((~beauty) & (Y[pos] - Y[j])) == 0) {
            t |= f2(j, group + 1);
        }
    }
    return dp2[pos][group] = t;
}

ll solve1() {
    beauty = (1ll << 50) - 1;
    for (int i = 49; i >= 0; i--) {
        beauty ^= (1ll << i);
        memset(dp1, -1, sizeof(dp1));
        if (f1(N) > B) {
            beauty ^= (1ll << i);
        }
    }
    return beauty;
}

ll solve2() {
    beauty = (1ll << 50) - 1;
    for (int i = 49; i >= 0; i--) {
        beauty ^= (1ll << i);
        memset(dp2, -1, sizeof(dp2));
        if (!f2(N, 0)) {
            beauty ^= (1ll << i);
        }
    }
    return beauty;
}

int main() {
    ri(N);
    ri(A);
    ri(B);
    for (int i = 1; i <= N; i++) {
        rll(Y[i]);
        Y[i] += Y[i - 1];
    }
    ll ans;
    if (A == 1) ans = solve1();
    else ans = solve2();
    printf("%lld", ans);
    return 0;
}
