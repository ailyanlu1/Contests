#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
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

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXNM 100005
#define MAXT 200005

int N, M, T, A[MAXT], pre[MAXNM], low[MAXNM], cnt;
umap<int, uset<int>> form[MAXNM];
umap<pii, int, pair_hash<int, int>> fEdges[MAXNM];
umap<int, uset<int>> adj;
umap<pii, int, pair_hash<int, int>> edges;
umap<pii, int, pair_hash<int, int>> ans;

int dfs(int v, int prev) {
    int ret = 0;
    pre[v] = cnt++;
    low[v] = pre[v];
    for (int w : adj[v]) {
        if (pre[w] == -1) {
            ret += dfs(w, v);
            MIN(low[v], low[w]);
            if (low[w] == pre[w] && edges[{min(v, w), max(v, w)}] == 1) ret++;
        } else if (w != prev) {
            MIN(low[v], pre[w]);
        }
    }
    return ret;
}

int cntBridges() {
    int ret = 0;
    cnt = 0;
    for (auto v = adj.begin(); v != adj.end(); v++) pre[v->f] = low[v->f] = -1;
    for (auto v = adj.begin(); v != adj.end(); v++) if (pre[v->f] == -1) ret += dfs(v->f, -1);
    return ret;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> T;
    FOR(i, T + 1) {
        cin >> A[i];
        A[i]--;
    }
    FOR(i, M) {
        int K, x, y;
        cin >> K;
        FOR(k, K) {
            cin >> x >> y;
            form[i][x].insert(y);
            form[i][y].insert(x);
            fEdges[i][{min(x, y), max(x, y)}]++;
        }
    }
    FOR(i, T) {
        if (ans.count({min(A[i], A[i + 1]), max(A[i], A[i + 1])})) {
            cout << ans[{min(A[i], A[i + 1]), max(A[i], A[i + 1])}] << nl;
            continue;
        }
        adj.clear();
        edges.clear();
        for (auto v = form[A[i]].begin(); v != form[A[i]].end(); v++) {
            for (int w : v->s) {
                adj[v->f].insert(w);
                adj[w].insert(v->f);
                if (v->f < w) edges[{min(v->f, w), max(v->f, w)}] += fEdges[A[i]][{min(v->f, w), max(v->f, w)}];
            }
        }
        for (auto v = form[A[i + 1]].begin(); v != form[A[i + 1]].end(); v++) {
            for (int w : v->s) {
                adj[v->f].insert(w);
                adj[w].insert(v->f);
                if (v->f < w) edges[{min(v->f, w), max(v->f, w)}] += fEdges[A[i + 1]][{min(v->f, w), max(v->f, w)}];
            }
        }
        ans[{min(A[i], A[i + 1]), max(A[i], A[i + 1])}] = cntBridges();
        cout << ans[{min(A[i], A[i + 1]), max(A[i], A[i + 1])}] << nl;
    }
    return 0;
}
