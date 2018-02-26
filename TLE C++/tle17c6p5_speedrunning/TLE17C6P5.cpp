#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl "\n"

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

#define MAXN 5005

int N;
// dist = distance from root
// wt = sum of distances to leaf nodes in subtree
// cnt = number of leaf nodes in subtree
// resets = number of resets for each subtree
// cost = optimal cost for each subtree including total distance to root
ll dist[MAXN], wt[MAXN], cnt[MAXN], resets[MAXN], cost[MAXN];
vector<pill> adj[MAXN];

void dfs1(int v, int prev, ll d) {
    dist[v] = d;
    wt[v] = sz(adj[v]) == 0 ? d : 0;
    cnt[v] = sz(adj[v]) == 0 ? 1 : 0;
    for (pill e : adj[v]) {
        dfs1(e.f, v, d + e.s);
        wt[v] += wt[e.f];
        cnt[v] += cnt[e.f];
    }
}

void dfs2(int v, int prev) {
    if (sz(adj[v]) == 0) {
        cost[v] = dist[v];
        resets[v] = 1;
        return;
    }
    for (pill e : adj[v]) dfs2(e.f, v);
    ll skip = 0, resetCnt = 0;
    for (pill e : adj[v]) { // no save at current node
        skip += cost[e.f];
        resetCnt += resets[e.f];
    }
    cost[v] = skip;
    resets[v] = resetCnt;
    ll save = dist[v];
    resetCnt = 1;
    for (pill e : adj[v]) { // save at current node
        if (wt[e.f] - cnt[e.f] * dist[v] <= cost[e.f]) { // visit every node from save point
            save += wt[e.f] - cnt[e.f] * dist[v];
            resetCnt += wt[e.f] - cnt[e.f] * dist[v];
        } else { // reset and use optimal branching from subtree
            save += cost[e.f];
            resetCnt += resets[e.f];
        }
    }
    if (save <= cost[v]) {
        cost[v] = save;
        resets[v] = resetCnt;
    }
    for (pill e : adj[v]) { // last save can be overwritten by a new save lower down the tree
        if (wt[e.f] - cnt[e.f] * dist[v] <= cost[e.f]) { // no longer visiting every node from save point
            if (cost[e.f] - dist[v] <= wt[e.f] - cnt[e.f] * dist[v]) {
                if (save + (cost[e.f] - dist[v]) - (wt[e.f] - cnt[e.f] * dist[v]) <= cost[v]) {
                    cost[v] = save + (cost[e.f] - dist[v]) - (wt[e.f] - cnt[e.f] * dist[v]);
                }
            }
        } else { // no longer resetting and using optimal branching from subtree
            if (cost[e.f] - dist[v] <= cost[e.f]) {
                if (save + (cost[e.f] - dist[v]) - cost[e.f] <= cost[v]) {
                    cost[v] = save + (cost[e.f] - dist[v]) - cost[e.f];
                    resets[v] = resetCnt - resets[e.f];
                }
            }
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int u, v;
    ll t;
    FOR(i, N - 1) {
        cin >> u >> v >> t;
        u--; v--;
        adj[u].pb({v, t});
    }
    dfs1(0, -1, 0);
    dfs2(0, -1);
    cout << cost[0] << nl;
    return 0;
}
