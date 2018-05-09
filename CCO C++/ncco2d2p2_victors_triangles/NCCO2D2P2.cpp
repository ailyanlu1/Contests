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
#define LG 20

int N, lg, ind, color[MAXN], cnt[MAXN], SZ[MAXN], head[MAXN], depth[MAXN], rmq[LG][MAXN * 2], ans = 0;
vector<int> adj[MAXN];
umap<int, vector<int>> colors;
umap<pii, int, pair_hash<int, int>> triInd;

void dfs1(int v, int d, int prev) {
    depth[v] = d;
    head[v] = ind;
    SZ[v] = 1;
    rmq[0][ind++] = v;
    for (int w : adj[v]) {
        if (w == prev) continue;
        dfs1(w, d + 1, v);
        SZ[v] += SZ[w];
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
    if (head[v] > head[w]) swap(v, w);
    return RMQ(head[v], head[w]);
}

int dfs2(int v, int prev) {
    int tot = cnt[v];
    for (int w : adj[v]) if (w != prev) tot += dfs2(w, v);
    if (prev != -1 && tot == SZ[v]) ans++;
    return tot;
}

void initLCA() {
    lg = 32 -__builtin_clz((N - 2) * 2 - 1);
    FOR(i, lg) FOR(j, (N - 2) * 2 - 1) rmq[i][j] = 0;
    FOR(i, (N - 2)) head[i] = -1;
    ind = 0;
    dfs1(0, 0, -1);
    for (int i = 0; i < lg - 1; i++) {
        for (int j = 0; j < ind; j++) {
            rmq[i + 1][j] = minDepth(rmq[i][j], rmq[i][min(j + (1 << i), ind - 1)]);
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int V[3];
    FOR(i, N - 2) {
        cin >> V[0] >> V[1] >> V[2] >> color[i];
        colors[color[i]].pb(i);
        cnt[i] = 0;
        FOR(j, 3) V[j]--;
        FOR(j, 3) {
            FOR(k, j) {
                if (triInd.count({V[j], V[k]})) {
                    int h = triInd[{V[j], V[k]}];
                    adj[i].pb(h);
                    adj[h].pb(i);
                }
            }
        }
        FOR(j, 3) FOR(k, 3) if (j != k) triInd[{V[j], V[k]}] = i;
    }
    initLCA();
    for (pair<int, vector<int>> c : colors) {
        int LCA = -1;
        for (int v : c.s) {
            if (LCA == -1) LCA = v;
            else LCA = lca(LCA, v);
        }
        cnt[LCA] += sz(c.s);
    }
    dfs2(0, -1);
    cout << ans << nl;
    return 0;
}
