/*
 * COCI07C1P6.cpp
 *
 *  Created on: Aug 1, 2017
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

struct Graph {
private:
    int V;
    int E;
    vector<int>* adjList;

public:
    Graph(int V) {
        this->V = V;
        this->E = 0;
        adjList = new vector<int>[V];
    }

    int getV() {
        return this->V;
    }

    int getE() {
        return this->E;
    }

    void addEdge(int v, int w) {
        adjList[v].push_back(w);
        adjList[w].push_back(v);
        E++;
    }

    vector<int> adj(int v) {
        return adjList[v];
    }

    int degree(int v) {
        return adjList[v].size();
    }
};


#define MAXN 10000
#define PATH 0
#define RING 1

int N, M, a, b, cntRings = 0, preCnt = 0, low[MAXN], pre[MAXN], dp[MAXN][2];
vector<int> bridge[MAXN], ring[MAXN], branch[MAXN];
stack<int> s;
Graph *G;

void dfs(int v, int prev) {
    pre[v] = preCnt++;
    low[v] = pre[v];
    s.push(v);
    for (int w : G->adj(v)) {
        if (w == prev) continue;
        if (pre[w] != -1) {
            low[v] = min(low[v], pre[w]);
        } else {
            dfs(w, v);
            if (low[w] < pre[v]) {
                low[v] = min(low[v], low[w]);
            } else if (low[w] == pre[v]) {
                branch[v].pb(cntRings);
                do {
                    ring[cntRings].pb(s.top());
                    s.pop();
                } while (ring[cntRings].back() != w);
                cntRings++;
            } else {
                bridge[v].pb(s.top());
                s.pop();
            }
        }
    }
}

int solve(int v, bool type) {
    if (dp[v][type] != -1) return dp[v][type];
    int ret = 0;
    int dist = 0;
    for (int w : bridge[v]) {
        dist = max(dist, solve(w, PATH) + 1);
    }
    for (int w : branch[v]) {
        ret += ring[w].size() + 1;
        int cwRing = 0;
        int ccwRing = 0;
        int cwDist = 0;
        int ccwDist = 0;
        for (int i = 0; i < ring[w].size(); i++) {
            int cwX = ring[w][i];
            int ccwX = ring[w][ring[w].size() - i - 1];
            cwDist = max(cwDist, cwRing + i + solve(cwX, PATH) + 1);
            ccwDist = max(ccwDist, ccwRing + i + solve(ccwX, PATH) + 1);
            cwRing += solve(cwX, RING);
            ccwRing += solve(ccwX, RING);
        }
        ret += cwRing;
        dist = max(dist, max(cwDist, ccwDist) - cwRing - (int) ring[w].size() - 1);
    }
    dp[v][PATH] = ret + dist;
    dp[v][RING] = ret;
    return dp[v][type];
}

int main() {
    ri(N);
    ri(M);
    G = new Graph(N);
    for (int v = 0; v < N; v++) {
        low[v] = -1;
        pre[v] = -1;
        dp[v][0] = dp[v][1] = -1;
    }
    for (int i = 0; i < M; i++) {
        ri(a);
        ri(b);
        G->addEdge(a - 1, b - 1);
    }
    dfs(0, -1);
    printf("%d\n", solve(0, PATH));
    return 0;
}
