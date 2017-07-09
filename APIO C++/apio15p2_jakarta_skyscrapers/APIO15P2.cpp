/*
 * APIO15P2.cpp
 *
 *  Created on: Jul 8, 2017
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

#define MAXN 30000

int N, M;
vector<int> pwr[MAXN];

int distTo[MAXN];
priority_queue<pair<double, int>, vector<pair<double, int>> , greater<pair<double, int>>> pq;

void dijkstraSP(int s, int t) {
    for (int v = 0; v < N; v++) {
        distTo[v] = INT_MAX;
    }
    distTo[s] = 0;
    pq.push({distTo[s], s});
    while (!pq.empty()) {
        int v = pq.top().second;
        pq.pop();
        if (v == t) break;
        for (int p : pwr[v]) {
            for (int i = 1; v + i * p < N; i++) {
                int w = v + i * p;
                if (distTo[w] > distTo[v] + i) {
                    distTo[w] = distTo[v] + i;
                    pq.push({distTo[w], w});
                    if (binary_search(pwr[w].begin(), pwr[w].end(), p)) break;
                }
            }
            for (int i = 1; v - i * p >= 0; i++) {
                int w = v - i * p;
                if (distTo[w] > distTo[v] + i) {
                    distTo[w] = distTo[v] + i;
                    pq.push({distTo[w], w});
                    if (binary_search(pwr[w].begin(), pwr[w].end(), p)) break;
                }
            }
        }
    }
}

int main() {
    ri(N);
    ri(M);
    int s, t;
    for (int i = 0; i < M; i++) {
        int b, p;
        ri(b);
        ri(p);
        pwr[b].pb(p);
        if (i == 0) s = b;
        else if (i == 1) t = b;
    }
    for (int i = 0; i < N; i++) {
        sort(pwr[i].begin(), pwr[i].end());
        pwr[i].erase(unique(pwr[i].begin(), pwr[i].end()), pwr[i].end());
    }
    dijkstraSP(s, t);
    printf("%d\n", distTo[t] == INT_MAX ? -1 : distTo[t]);
    return 0;
}
