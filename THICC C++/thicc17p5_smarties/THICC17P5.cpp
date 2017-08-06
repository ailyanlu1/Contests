/*
 * THICC17P5.cpp
 *
 *  Created on: Aug 5, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
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
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
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

#define MAXF (int) (1e6 + 5)
#define MAXN (int) (1e5 + 5)

int N, K, F[MAXN], cnt[MAXF];
ll ans = 0;

int main() {
    ri(N);
    ri(K);
    for (int i = 1; i <= N; i++) {
        ri(F[i]);
    }
    int l = 1, r = 1, k = 0;
    while (r <= N) {
        if (cnt[F[r]]++ == 0) k++;
        while (k >= K) {
            if (--cnt[F[l]] == 0) k--;
            l++;
        }
        ans += r - l + 1;
        r++;
    }
    printf("%lld\n", (ll) N * (ll) (N + 1) / 2 - ans);
    return 0;
}
