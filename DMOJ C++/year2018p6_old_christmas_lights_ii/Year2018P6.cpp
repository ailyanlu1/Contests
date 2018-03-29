#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) ((x) << 1)
#define r(x) ((x) << 1 | 1)
#define m(x, y) ((x) + ((y) - (x)) / 2)
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rld(x) scanf("%Lf", &x)
#define rc(x) scanf(" %c", &x)
#define sc(x) do { scanf("%c", &x); } while (isspace(x))
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define set0(a) memset((a), 0, sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define Fill2(a, x, n, m) FOR(_, n) FOR(__, m) (a)[_][__] = (x)
#define Fill3(a, x, n, m, p) FOR(_, n) FOR(__, m) FOR(___, p) (a)[_][__][___] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))
#define sz(a) ((int) (a).size())
#define len(a) ((int) (a).length())

typedef long long ll;
typedef unsigned long long llu;
typedef long double ld;
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef map<ll, ll> mll;
typedef umap<int, int> umii;
typedef umap<int, ll> umill;
typedef umap<ll, int> umlli;
typedef umap<ll, ll> umll;
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

#define debug(fmt, x) fprintf(stderr, "%d::%s = " fmt, __LINE__, #x, (x)); fflush(stderr)
#define debug2(x) cerr << __LINE__ << "::" << #x << " = " << (x) << '\n' << flush
#define debugva(fmt, ...) fprintf(stderr, "%d::%s = " fmt, __LINE__, #__VA_ARGS__, __VA_ARGS__); fflush(stderr)
#define debugarr(fmt, x, a, b) fprintf(stderr, "%d::%s = {", __LINE__, #x); For(_, a, b) { if (_ != (a)) { fprintf(stderr, ", "); } fprintf(stderr, fmt, (x)[_]); } fprintf(stderr, "}\n"); fflush(stderr)
#define debugarr2(x, a, b) cerr << __LINE__ << "::" << #x << " = {"; For(_, a, b) { if (_ != (a)) { cerr << ", "; } cerr << (x)[_]; } cerr << "}\n" << flush

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

struct Graph {
private:
    int V;
    int E;
    vector<int> *adjList;

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

    vector<int> &adj(int v) {
        return adjList[v];
    }

    int degree(int v) {
        return adjList[v].size();
    }

    vector<pair<int, int>> &edges() {
        vector<pair<int, int>> *list = new vector<pair<int, int>>;
        for (int v = 0; v < V; v++) {
            int selfLoops = 0;
            for (int w : adj(v)) {
                if (w > v) {
                    list->push_back(make_pair(v, w));
                }
                // only add one copy of each self loop (self loops will be consecutive)
                else if (w == v) {
                    if (selfLoops % 2 == 0) list->push_back(make_pair(v, w));
                    selfLoops++;
                }
            }
        }
        return *list;
    }
};

class MoTree {
private:
    bool *vis;
    int *a, *depth, *head, **rmq, *pre, *post, *vertex, *cnt, *ans;
    int V, Q, lg, ind, cur, res;
    multiset<int> curSet, diff;

    struct Query {
        int l, r, lca, ind, block;

        bool operator < (const Query &q) const {
            if (block != q.block) return block < q.block;
            return r < q.r;
        }
    } *q;

    void dfs(Graph *G, int v, int d, int prev) {
        vertex[cur] = v;
        pre[v] = cur++;
        depth[v] = d;
        head[v] = ind;
        rmq[0][ind++] = v;
        for (int w : G->adj(v)) {
            if (w == prev) continue;
            dfs(G, w, d + 1, v);
            rmq[0][ind++] = v;
        }
        vertex[cur] = v;
        post[v] = cur++;
    }

    inline int minDepth(int v, int w) {
        return depth[v] < depth[w] ? v : w;
    }

    inline int RMQ(int l, int r) {
        int i = 31 - __builtin_clz(r - l + 1);
        return minDepth(rmq[i][l], rmq[i][r - (1 << i) + 1]);
    }

    int lca(int v, int w) {
        if (head[v] > head[w]) swap(v, w);
        return RMQ(head[v], head[w]);
    }

    void update(int v) {
        if (vis[v]) {
            curSet.erase(curSet.lower_bound(a[v]));
            if (curSet.size() > 0) {
                auto x = curSet.lower_bound(a[v]);
                if (x == curSet.begin()) {
                    diff.erase(diff.lower_bound(*x - a[v]));
                } else {
                    auto y = prev(x);
                    if (x == curSet.end()) {
                        diff.erase(diff.lower_bound(a[v] - *y));
                    } else {
                        diff.insert(*x - *y);
                        diff.erase(diff.lower_bound(a[v] - *y));
                        diff.erase(diff.lower_bound(*x - a[v]));
                    }
                }
            }
        } else {
            if (curSet.size() > 0) {
                auto x = curSet.lower_bound(a[v]);
                if (x == curSet.begin()) {
                    diff.insert(*x - a[v]);
                } else {
                    auto y = prev(x);
                    if (x == curSet.end()) {
                        diff.insert(a[v] - *y);
                    } else {
                        diff.erase(diff.lower_bound(*x - *y));
                        diff.insert(a[v] - *y);
                        diff.insert(*x - a[v]);
                    }
                }
            }
            curSet.insert(a[v]);
        }
        vis[v] = !vis[v];
    }

    void mo() {
        int l = q[0].l;
        int r = l - 1;
        int last = -1;
        for (int i = 0; i < Q; i++) {
            if (last != q[i].block) {
                curSet.clear();
                diff.clear();
                for (int i = 0; i < V; i++) vis[i] = 0;
                l = q[i].l;
                r = l - 1;
                last = q[i].block;
            }
            while (l < q[i].l) {
                update(vertex[l]);
                l++;
            }
            while (l > q[i].l) {
                l--;
                update(vertex[l]);
            }
            while (r < q[i].r) {
                r++;
                update(vertex[r]);
            }
            while (r > q[i].r) {
                update(vertex[r]);
                r--;
            }
            if (q[i].lca != vertex[l] && q[i].lca != vertex[r]) update(q[i].lca);
            ans[q[i].ind] = *diff.begin();
            if (q[i].lca != vertex[l] && q[i].lca != vertex[r]) update(q[i].lca);
        }
    }

public:
    /**
     * Computes the number of distinct integers on the path between
     * two nodes.
     * @param G the Graph
     * @param arr the array with the weights of each node
     * @param queries the array of pairs containing the queries
     * @param Q the number of queries
     */
    MoTree(Graph *G, int *arr, pair<int, int> *queries, int Q) {
        this->V = G->getV();
        this->Q = Q;
        this->lg = 32 - __builtin_clz(V * 2 - 1);
        a = new int[V];
        vis = new bool[V];
        depth = new int[V];
        head = new int[V];
        rmq = new int*[lg];
        for (int i = 0; i < lg; i++) {
            rmq[i] = new int[V * 2 - 1];
        }
        pre = new int[V];
        post = new int[V];
        vertex = new int[V * 2];
        cnt = new int[V];
        q = new Query[Q];
        ans = new int[Q];
        ind = 0;
        cur = 0;
        for (int i = 0; i < V; i++) {
            head[i] = -1;
            vis[i] = false;
        }
        dfs(G, 0, 0, -1);
        for (int i = 0; i < lg - 1; i++) {
            for (int j = 0; j < ind; j++) {
                rmq[i + 1][j] = minDepth(rmq[i][j], rmq[i][min(j + (1 << i), ind - 1)]);
            }
        }
        int sz = 600;
        for (int i = 0; i < V; i++) {
            a[i] = arr[i];
        }
        for (int i = 0; i < Q; i++) {
            int v = queries[i].first;
            int w = queries[i].second;
            q[i].lca = lca(v, w);
            if (pre[v] > pre[w]) swap(v, w);
            if (q[i].lca == v) {
                q[i].l = pre[v];
                q[i].r = pre[w];
            } else {
                q[i].l = post[v];
                q[i].r = pre[w];
            }
            q[i].ind = i;
            q[i].block = q[i].l / sz;
        }
        sort(q, q + Q);
        mo();
    }

    /**
     * Returns the answer to the ith query.
     *
     * @param i the index of the query
     * @return the answer the query
     */
    int query(int i) {
        return ans[i];
    }
};

#define MAXNQ 50010

int N, Q, C[MAXNQ];
pii queries[MAXNQ];
Graph *G;
MoTree *Mo;

int main() {
    ri(N);
    G = new Graph(N);
    ri(Q);
    FOR(i, N) ri(C[i]);
    int a, b;
    FOR(i, N - 1) {
        ri(a);
        ri(b);
        G->addEdge(a - 1, b - 1);
    }
    FOR(i, Q) {
        ri(queries[i].f); queries[i].f--;
        ri(queries[i].s); queries[i].s--;
    }
    Mo = new MoTree(G, C, queries, Q);
    FOR(i, Q) printf("%d\n", Mo->query(i));
    return 0;
}
