// http://www.spoj.com/problems/QTREE5/
#include <bits/stdc++.h>
using namespace std;

#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define f first
#define s second
#define all(a) (a).begin(), (a).end()
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pill pair<int, ll>
#define plli pair<ll, int>
#define pdd pair<double, double>
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

template<typename T1, typename T2, typename H1 = hash<T1>, typename H2 = hash<T2>>
struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * H1 {}(p.first) + H2 {}(p.second);}};

#define MAXN 100005
#define MAXLGN 18

int N, Q, lg, ind, par[MAXN], head[MAXN], depth[MAXN], rmq[MAXLGN][MAXN * 2];
bool exclude[MAXN], color[MAXN];
vector<int> adj[MAXN];
set<pii> best[MAXN];

int getSize(int v, int prev) {
    int size = 1;
    for (int w : adj[v]) if (w != prev && !exclude[w]) size += getSize(w, v);
    return size;
}

int getCentroid(int v, int prev, int treeSize) {
    int n = treeSize;
    int size = 1;
    bool hasCentroid = true;
    for (int w : adj[v]) {
        if (w == prev || exclude[w]) continue;
        int ret = getCentroid(w, v, treeSize);
        if (ret >= 0) return ret;
        hasCentroid &= -ret <= n / 2;
        size += -ret;
    }
    hasCentroid &= n - size <= n / 2;
    return hasCentroid ? v : -size;
}

void dfs(int v, int prev, int d) {
    depth[v] = d;
    head[v] = ind;
    rmq[0][ind++] = v;
    for (int w : adj[v]) {
        if (w == prev) continue;
        dfs(w, v, d + 1);
        rmq[0][ind++] = v;
    }
}

inline int minDepth(int v, int w) {
    return depth[v] < depth[w] ? v : w;
}

inline int RMQ(int l, int r) {
    int i = 31 - __builtin_clz(r - l + 1);
    return minDepth(rmq[i][l], rmq[i][r - (1 << i) + 1]);
}

inline int lca(int v, int w) {
    return head[v] < head[w] ? RMQ(head[v], head[w]) : RMQ(head[w], head[v]);
}

inline int dist(int v, int w) {
    return depth[v] + depth[w] - 2 * depth[lca(v, w)];
}

void add(int v) {
    int p = v;
    while (p != -1) {
        best[p].insert({dist(p, v), v});
        p = par[p];
    }
}

void remove(int v) {
    int p = v;
    while (p != -1) {
        best[p].erase({dist(p, v), v});
        p = par[p];
    }
}

int query(int v) {
    int ret = INT_INF;
    int p = v;
    while (p != -1) {
        if (!best[p].empty()) MIN(ret, best[p].begin()->f + dist(p, v));
        p = par[p];
    }
    return ret == INT_INF ? -1 : ret;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    lg = 32 - __builtin_clz(N * 2 - 1);
    FOR(i, N) {
        color[i] = false;
        head[i] = -1;
        exclude[i] = false;
    }
    int a, b;
    FOR(i, N - 1) {
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    queue<pii> q;
    q.push({0, -1});
    while (!q.empty()) {
        int v = q.front().f;
        int c = getCentroid(v, -1, getSize(v, -1));
        par[c] = q.front().s;
        q.pop();
        exclude[c] = true;
        for (int w : adj[c]) if (!exclude[w]) q.push({w, c});
    }
    ind = 0;
    dfs(0, -1, 0);
    FOR(i, lg - 1) FOR(j, ind) rmq[i + 1][j] = minDepth(rmq[i][j], rmq[i][min(j + (1 << i), ind - 1)]);
    cin >> Q;
    FOR(i, Q) {
        cin >> a >> b;
        b--;
        if (a == 0) {
            color[b] ^= true;
            if (color[b]) add(b);
            else remove(b);
        } else cout << query(b) << nl;
    }
    return 0;
}
