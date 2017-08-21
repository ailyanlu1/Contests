#include <bits/stdc++.h>
#include "factories.h"

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
#define mid(x, y) (x + (y - x) / 2)
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
#define randi(a, b) (rand() % (b - a + 1) + a)

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
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

#define MAXN 500005

int n, pre[MAXN], preCnt, depth[MAXN], parent[MAXN], chain[MAXN], size[MAXN], head[MAXN], chainNum, cur, q = 0;
ll dist1[MAXN];
int factory[MAXN], vis[MAXN];
vector<int> all;
vector<pill> G1[MAXN], G2[MAXN];

void addEdge(vector<pill> *G, int v, int w, ll weight) {
    G[v].pb(mp(w, weight));
    G[w].pb(mp(v, weight));
}

void dfs(int v, int dep, int prev, ll dist) {
    pre[v] = preCnt++;
    depth[v] = dep;
    parent[v] = prev;
    size[v] = 1;
    dist1[v] = dist;
    for (pill &e : G1[v]) {
        int w = e.f;
        if (w != prev) {
            dfs(w, dep + 1, v, dist + e.s);
            size[v] += size[w];
        }
    }
}

void hld(int v, int prev) {
    if (head[chainNum] == -1) head[chainNum] = v;
    chain[v] = chainNum;
    int maxIndex = -1;
    for (pill &e : G1[v]) {
        int w = e.f;
        if (w != prev && (maxIndex == -1 || size[maxIndex] < size[w])) maxIndex = w;
    }
    if (maxIndex != -1) hld(maxIndex, v);
    for (pill &e : G1[v]) {
        int w = e.f;
        if (w != prev && w != maxIndex) {
            chainNum++;
            hld(w, v);
        }
    }
}

void initLCA() {
    chainNum = 0;
    preCnt = 0;
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
    dfs(0, 0, -1, 0LL);
    hld(0, -1);
}

int lca(int v, int w) {
    while (chain[v] != chain[w]) {
        if (depth[head[chain[v]]] < depth[head[chain[w]]]) w = parent[head[chain[w]]];
        else v = parent[head[chain[v]]];
    }
    if (depth[v] < depth[w]) return v;
    return w;
}

void rebuild() {
    int v = all[cur++];
    while (cur < all.size() && pre[all[cur]] < pre[v] + size[v]) {
        addEdge(G2, v, all[cur], dist1[all[cur]] - dist1[v]);
        rebuild();
    }
}

bool preOrder(int v, int w) {
    return pre[v] < pre[w];
}

ll dijkstraSP(int s, int *sources) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>> , greater<pair<ll, int>>> pq;
    for (int i = 0; i < s; i++) {
        pq.push({0LL, sources[i]});
    }
    while (!pq.empty()) {
        int v = pq.top().second;
        ll curDist = pq.top().first;
        pq.pop();
        if (vis[v] == q) continue;
        vis[v] = q;
        if (factory[v] == q) return curDist;
        for (pill &e : G2[v]) {
            int w = e.f;
            if (vis[w] == q) continue;
            pq.push({curDist + e.s, w});
        }
    }
    return -1;
}

void Init(int N, int A[], int B[], int D[]) {
    n = N;
    for (int i = 0; i < N - 1; i++) {
        addEdge(G1, A[i], B[i], D[i]);
    }
    initLCA();
}

long long Query(int S, int X[], int T, int Y[]) {
    q++;
    cur = 0;
    for (int i = 0; i < S; i++) {
        all.pb(X[i]);
    }
    for (int i = 0; i < T; i++) {
        factory[Y[i]] = q;
        all.pb(Y[i]);
    }
    sort(all.begin(), all.end(), preOrder);
    for (int i = 0; i < S + T - 1; i++) {
        all.pb(lca(all[i], all[i + 1]));
    }
    sort(all.begin(), all.end(), preOrder);
    all.resize(unique(all.begin(), all.end()) - all.begin());
    rebuild();
    ll ans = dijkstraSP(S, X);
    for (int &v : all) {
        G2[v].clear();
    }
    all.clear();
    return ans;
}
