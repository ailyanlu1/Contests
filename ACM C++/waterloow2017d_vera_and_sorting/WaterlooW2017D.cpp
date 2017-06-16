/*
 * WaterlooW2017D.cpp
 *
 *  Created on: Jun 8, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define INT_INF 0x3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define m(x, y) x + (y - x) / 2
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf('%llu', &x)
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
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;

#define MAXN 30
#define MAXK 900
#define MOD (int) (1e9 + 7)

int N, K;
ll perm[MAXN + 1], inv[MAXN + 1], dp[MAXN + 1][MAXK + 1];

ll invert(long b) {
    ll ret = 1;
    for (int i = 0; i <= 30; i++) {
        if (((MOD - 2) >> i) % 2 == 1) ret = ret * b % MOD;
        b = b * b % MOD;
    }
    return ret;
}

int main() {
    ri(N);
    ri(K);
    perm[0] = inv[0] = 1;
    for (int i = 1; i <= N; i++) {
        perm[i] = perm[i - 1] * i % MOD;
        inv[i] = invert(perm[i]);
    }
    dp[0][0] = dp[1][1] = 1;
    for (int n = 2; n <= N; n++) {
        for (int k = n; k <= K; k++) {
            for (int m = 0; m < n; m++) {
                ll x = perm[n - 1] * inv[m] % MOD * inv[n - m - 1] % MOD;
                for (int p = m; p <= min(k - n, m * (m + 1) / 2); p++) {
                    ll y = dp[m][p] * dp[n - m - 1][k - n - p] % MOD;
                    dp[n][k] = (dp[n][k] + x * y % MOD) % MOD;
                }
            }
        }
    }
    printf("%lld\n", dp[N][K]);
    return 0;
}
