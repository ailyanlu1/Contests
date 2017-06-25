/*
 * COCI15C1P6.cpp
 *
 *  Created on: Jun 11, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define INT_INF 0x3f3f3f3f
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

#define MAXN 10000
#define MAXV 100

int N, V[MAXN];
vector<int> edges[MAXN];
vector<pii> jokes[MAXN];
vector<int> q[MAXV + 1];
bitset<MAXV + 1> dp[MAXN][MAXV + 1];

void dfs(int v) {
    for (int w: edges[v]) {
        dfs(w);
    }
    for (int i = 0; i <= MAXV; i++) {
        q[i].clear();
    }
    for (int w: edges[v]) {
        for (pii p: jokes[w]) {
            q[p.f].pb(p.s);
        }
    }
    for (int lo = MAXV; lo >= 1; lo--) {
        if (lo == V[v]) {
            dp[v][lo] |= (dp[v][lo + 1]);
            dp[v][lo].set(lo);
        } else {
            for (int hi: q[lo]) {
                if (lo > V[v] || hi < V[v]) {
                    dp[v][lo] |= (dp[v][hi + 1]);
                    dp[v][lo].set(hi);
                }
            }
        }
        for (int hi = MAXV; hi >= lo; hi--) {
            if (dp[v][lo].test(hi) && V[v] >= lo && V[v] <= hi) {
                jokes[v].pb({lo, hi});
            }
        }
    }
}

int main() {
    ri(N);
    for (int i = 0; i < N; i++) {
        ri(V[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        ri(a);
        ri(b);
        edges[a - 1].push_back(b - 1);
    }
    dfs(0);
    printf("%d", jokes[0].size());
    return 0;
}
