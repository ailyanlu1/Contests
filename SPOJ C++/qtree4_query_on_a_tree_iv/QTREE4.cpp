// http://www.spoj.com/problems/QTREE4/
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

int N, Q, lg, curInd, par[MAXN], cInd[MAXN], deg[MAXN], head[MAXN], depth[MAXN], distTo[MAXN], best[MAXN], rmq[MAXLGN][MAXN * 2];
int s1[MAXN], s2[MAXN], s3[MAXN], L[MAXN * 120], R[MAXN * 120], VAL1[MAXN * 120], VAL2[MAXN * 120], cnt = 0;
bool exclude[MAXN], color[MAXN];
vector<pii> adj[MAXN];

void update1(int &cur, int cL, int cR, int ind, int val) {
    if (!cur) {
        cur = ++cnt;
        L[cur] = R[cur] = 0;
    }
    if (cL == cR) {
        VAL1[cur] = val;
        return;
    }
    int m = cL + (cR - cL) / 2;
    if (ind <= m) update1(L[cur], cL, m, ind, val);
    else update1(R[cur], m + 1, cR, ind, val);
    VAL1[cur] = max(VAL1[L[cur]], VAL1[R[cur]]);
}

void update2(int &cur, int cL, int cR, int ind, int val) {
    if (!cur) {
        cur = ++cnt;
        L[cur] = R[cur] = 0;
    }
    if (cL == cR) {
        VAL1[cur] = val;
        VAL2[cur] = -INT_INF;
        return;
    }
    int m = cL + (cR - cL) / 2;
    if (ind <= m) update2(L[cur], cL, m, ind, val);
    else update2(R[cur], m + 1, cR, ind, val);
    if (VAL1[L[cur]] > VAL1[R[cur]]) {
        VAL1[cur] = VAL1[L[cur]];
        VAL2[cur] = max(VAL1[R[cur]], VAL2[L[cur]]);
    } else {
        VAL1[cur] = VAL1[R[cur]];
        VAL2[cur] = max(VAL1[L[cur]], VAL2[R[cur]]);
    }
}

int getSize(int v, int prev) {
    int size = 1;
    for (pii e : adj[v]) if (e.f != prev && !exclude[e.f]) size += getSize(e.f, v);
    return size;
}

int getCentroid(int v, int prev, int treeSize) {
    int n = treeSize;
    int size = 1;
    bool hasCentroid = true;
    for (pii e : adj[v]) {
        if (e.f == prev || exclude[e.f]) continue;
        int ret = getCentroid(e.f, v, treeSize);
        if (ret >= 0) return ret;
        hasCentroid &= -ret <= n / 2;
        size += -ret;
    }
    hasCentroid &= n - size <= n / 2;
    return hasCentroid ? v : -size;
}

void dfs(int v, int prev, int curDep, int curDist) {
    depth[v] = curDep;
    distTo[v] = curDist;
    head[v] = curInd;
    rmq[0][curInd++] = v;
    for (pii e : adj[v]) {
        if (e.f == prev) continue;
        dfs(e.f, v, curDep + 1, curDist + e.s);
        rmq[0][curInd++] = v;
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
    if (v == 0) return distTo[w];
    if (w == 0) return distTo[v];
    return distTo[v] + distTo[w] - 2 * distTo[lca(v, w)];
}

void add(int v) {
    int p = v;
    while (p != -1) {
        best[p] = -INT_INF;
        MAX(best[p], VAL1[s3[p]]);
        if (color[p]) MAX(best[p], max(0, VAL1[s2[p]]));
        MAX(best[p], VAL1[s2[p]] + VAL2[s2[p]]);
        if (p != 0) {
            update1(s3[par[p]], 0, deg[par[p]] - 1, cInd[p], best[p]);
            update1(s1[p], 1, N, v, dist(par[p], v));
            update2(s2[par[p]], 0, deg[par[p]] - 1, cInd[p], VAL1[s1[p]]);
        }
        p = par[p];
    }
}

void remove(int v) {
    int p = v;
    while (p != -1) {
        best[p] = -INT_INF;
        MAX(best[p], VAL1[s3[p]]);
        if (color[p]) MAX(best[p], max(0, VAL1[s2[p]]));
        MAX(best[p], VAL1[s2[p]] + VAL2[s2[p]]);
        if (p != 0) {
            update1(s3[par[p]], 0, deg[par[p]] - 1, cInd[p], best[p]);
            update1(s1[p], 1, N, v, -INT_INF);
            update2(s2[par[p]], 0, deg[par[p]] - 1, cInd[p], VAL1[s1[p]]);
        }
        p = par[p];
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    lg = 32 - __builtin_clz(N * 2 - 1);
    VAL1[0] = VAL2[0] = -INT_INF;
    FOR(i, N + 1) {
        head[i] = -1;
        color[i] = false;
        exclude[i] = false;
        best[i] = -INT_INF;
        s1[i] = s2[i] = s3[i] = 0;
    }
    int a, b, c;
    FOR(i, N - 1) {
        cin >> a >> b >> c;
        adj[a].eb(b, c);
        adj[b].eb(a, c);
    }
    queue<pair<int, pii>> q;
    q.push({1, {0, 0}});
    deg[0] = 1;
    while (!q.empty()) {
        int v = q.front().f;
        int c = getCentroid(v, -1, getSize(v, -1));
        par[c] = q.front().s.f;
        cInd[c] = q.front().s.s;
        q.pop();
        exclude[c] = true;
        int curInd = 0;
        for (pii e : adj[c]) if (!exclude[e.f]) q.push({e.f, {c, curInd++}});
        deg[c] = curInd;
    }
    curInd = 0;
    dfs(1, -1, 0, 0);
    par[0] = -1;
    distTo[0] = 0;
    FOR(i, lg - 1) FOR(j, curInd) rmq[i + 1][j] = minDepth(rmq[i][j], rmq[i][min(j + (1 << i), curInd - 1)]);
    For(i, 1, N + 1) {
        color[i] = true;
        add(i);
    }
    cin >> Q;
    char op;
    int v;
    FOR(i, Q) {
        cin >> op;
        if (op == 'C') {
            cin >> v;
            color[v] ^= true;
            if (color[v]) add(v);
            else remove(v);
        } else if (op == 'A') {
            if (best[0] == -INT_INF) cout << "They have disappeared." << nl;
            else cout << max(0, best[0]) << nl;
        } else {
            i--;
        }
    }
    return 0;
}
