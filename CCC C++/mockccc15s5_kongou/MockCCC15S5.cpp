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

#define phii pair_hash<int, int>

#define MAXNM 100005
#define MAXT 200005

int N, M, T, A[MAXT], cnt[MAXNM];
umap<pii, int, phii> pre, low;
umap<int, uset<int>> form[MAXNM];
umap<pii, int, phii> edges[MAXNM];
umap<pii, uset<int>, phii> bridges;
vector<int> con[MAXNM];
umap<int, uset<int>> vert;
umap<int, uset<pii, phii>> adj;
umap<pii, int, phii> ans;

void dfs(int v, int prev, int i, int a) {
    if (cnt[a] == 0) cnt[a] = cnt[i];
    cout << "//" << a << sp << prev << sp << v << sp << cnt[a] << endl;
    pre[{v, a}] = low[{v, a}] = cnt[a]++;
    for (pii w : adj[v]) {
        cout << "///" << w.f << sp << w.s << endl;
        if (pre[w] == -1) {
            dfs(w.f, v, i, w.s);
            low[{v, a}] = min(low[{v, a}], low[w]);
            if (low[w] == pre[w] || (pre.count({w.f, i}) && low[w] == pre[{w.f, i}]) || (low.count({w.f, i}) && low[{w.f, i}] == pre[w])) {
                cout << "BRIDGE: " << w.s << sp << v << sp << w.f << endl;
                bridges[{min(v, w.f), max(v, w.f)}].insert(w.s);
            }
        } else if (w.f != prev) {
            low[{v, a}] = min(low[{v, a}], pre[w]);
        }
    }
}

void cntBridges(int i) {
    pre.clear();
    low.clear();
    bridges.clear();
    cnt[i] = 0;
    for (int a : con[i]) cnt[a] = 0;
    for (int v : vert[i]) pre[{v, i}] = low[{v, i}] = -1;
    for (int a : con[i]) for (int v : vert[a]) pre[{v, a}] = low[{v, a}] = -1;
    for (int v : vert[i]) if (pre[{v, i}] == -1) dfs(v, -1, i, i);
    for (int a : con[i]) for (int v : vert[a]) if (pre[{v, a}] == -1) dfs(v, -1, i, a);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> T;
    FOR(i, T + 1) {
        cin >> A[i];
        A[i]--;
        if (i > 0) con[A[i]].pb(A[i - 1]);
    }
    FOR(i, M) {
        int K, x, y;
        cin >> K;
        FOR(k, K) {
            cin >> x >> y;
            form[i][x].insert(y);
            form[i][y].insert(x);
            edges[i][{x, y}]++;
            edges[i][{y, x}]++;
        }
    }
    FOR(i, M) {
        if (con[i].empty()) continue;
        adj.clear();
        vert.clear();
        for (auto v = form[i].begin(); v != form[i].end(); v++) {
            vert[i].insert(v->f);
            for (int w : v->s) adj[v->f].insert({w, i});
        }
        for (int a : con[i]) {
            if (a == i || ans.count({i, a})) {
                continue;
            } else if (ans.count({a, i})) {
               ans[{i, a}] = ans[{a, i}];
            } else {
                for (auto v = form[a].begin(); v != form[a].end(); v++) {
                    vert[a].insert(v->f);
                    for (int w : v->s) adj[v->f].insert({w, a});
                }
            }
        }
        cout << i << ":" << endl;
        cntBridges(i);
        ans[{i, i}] = 0;
        for (auto b = bridges.begin(); b != bridges.end(); b++) {
            cout << b->f.f << sp << b->f.s << sp << b->s.size() << endl;
            if (b->s.count(i)) {
                if ((int) b->s.size() == 1 && edges[i][{b->f.f, b->f.s}] == 1) ans[{i, i}]++;
            } else {
                for (int a : b->s) if (edges[a][{b->f.f, b->f.s}] == 1) ans[{i, a}]++;
            }
        }
        for (int a : con[i]) {
            if (a != i) ans[{i, a}] += ans[{i, i}];
            cout << "/" << i << sp << a << sp << ans[{i, a}] << endl;
        }
        ans[{i, i}] = 0;
    }
    FOR(i, T) cout << ans[{A[i + 1], A[i]}] << nl;
    return 0;
}
