// http://www.spoj.com/problems/LCASQ/
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

class LCA {
private:
    vector<vector<int>> adj;
    vector<int> head, depth;
    vector<vector<int>> rmq;
    int ind;
    int lg;

    void dfs(int v, int prev) {
        head[v] = ind;
        rmq[0][ind++] = v;
        for (int w : adj[v]) {
            if (w == prev) continue;
            depth[w] = depth[v] + 1;
            dfs(w, v);
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

public:
    /**
     * Initializes the structure.
     *
     * @param V the number of vertices
     */
    LCA(int V) : adj(V), head(V), depth(V) {
        lg = 32 - __builtin_clz(V * 2 - 1);
        for (int i = 0; i < lg; i++) rmq.push_back(vector<int>(V * 2 - 1));
        fill(head.begin(), head.end(), -1);
        ind = 0;
    }

    /**
     * Adds a bidirectional edge from v to w.
     *
     * @param v one vertex of the edge
     * @param w the other vertex of the edge
     */
    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    /**
     * Begins the LCA process.
     *
     * @param root the root of the tree
     */
    void compute(int root = 0) {
        depth[root] = 0;
        dfs(root, -1);
        for (int i = 0; i < lg - 1; i++) {
            for (int j = 0; j < ind; j++) {
                rmq[i + 1][j] = minDepth(rmq[i][j], rmq[i][min(j + (1 << i), ind - 1)]);
            }
        }
    }

    /**
     * Returns the lowest common ancestor of vertex {@code v} and {@code w}.
     *
     * @param v the first vertex
     * @param w the first vertex
     * @return the lowest common ancestor of vertex {@code v} and {@code w}
     */
    int lca(int v, int w) {
        if (head[v] > head[w]) swap(v, w);
        return RMQ(head[v], head[w]);
    }
};

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int V, M, Q, v, w;
    cin >> V;
    LCA lca(V);
    FOR(i, V) {
        cin >> M;
        FOR(j, M) {
            cin >> v;
            lca.addEdge(i, v);
        }
    }
    lca.compute();
    cin >> Q;
    FOR(i, Q) {
        cin >> v >> w;
        cout << lca.lca(v, w) << nl;
    }
    return 0;
}
