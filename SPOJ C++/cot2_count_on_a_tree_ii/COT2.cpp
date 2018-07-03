// http://www.spoj.com/problems/COT2/
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
} *G;

class MoTree {
private:
    bool *vis;
    int *a, *depth, *parent, *chain, *size, *head, *pre, *post, *vertex, *cnt, *ans;
    int V, Q, chainNum, cur, res;

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
        parent[v] = prev;
        size[v] = 1;
        for (int w: G->adj(v)) {
            if (w != prev) {
                dfs(G, w, d + 1, v);
                size[v] += size[w];
            }
        }
        vertex[cur] = v;
        post[v] = cur++;
    }

    void hld(Graph *G, int v, int prev) {
        if (head[chainNum] == -1) head[chainNum] = v;
        chain[v] = chainNum;
        int maxIndex = -1;
        for (int w: G->adj(v)) {
            if (w != prev && (maxIndex == -1 || size[maxIndex] < size[w])) maxIndex = w;
        }
        if (maxIndex != -1) hld(G, maxIndex, v);
        for (int w: G->adj(v)) {
            if (w != prev && w != maxIndex) {
                chainNum++;
                hld(G, w, v);
            }
        }
    }

    int lca(int v, int w) {
        while (chain[v] != chain[w]) {
            if (depth[head[chain[v]]] < depth[head[chain[w]]]) w = parent[head[chain[w]]];
            else v = parent[head[chain[v]]];
        }
        if (depth[v] < depth[w]) return v;
        return w;
    }

    void check(int v) {
        if (vis[v] && --cnt[a[v]] == 0) res--;
        else if (!vis[v] && cnt[a[v]]++ == 0) res++;
        vis[v] = !vis[v];
    }

    void mo() {
        int l = q[0].l;
        int r = l - 1;
        res = 0;
        for (int i = 0; i < Q; i++) {
            while (l < q[i].l) {
                check(vertex[l]);
                l++;
            }
            while (l > q[i].l) {
                l--;
                check(vertex[l]);
            }
            while (r < q[i].r) {
                r++;
                check(vertex[r]);
            }
            while (r > q[i].r) {
                check(vertex[r]);
                r--;
            }
            if (q[i].lca != vertex[l] && q[i].lca != vertex[r]) check(q[i].lca);
            ans[q[i].ind] = res;
            if (q[i].lca != vertex[l] && q[i].lca != vertex[r]) check(q[i].lca);
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
        a = new int[V];
        vis = new bool[V];
        depth = new int[V];
        parent = new int[V];
        chain = new int[V];
        size = new int[V];
        head = new int[V];
        pre = new int[V];
        post = new int[V];
        vertex = new int[V * 2];
        cnt = new int[V];
        q = new Query[Q];
        ans = new int[Q];
        chainNum = 0;
        cur = 0;
        for (int i = 0; i < V; i++) {
            head[i] = -1;
            vis[i] = false;
        }
        dfs(G, 0, 0, -1);
        hld(G, 0, -1);
        int sz = (int) sqrt(cur);
        int *temp = new int[V];
        for (int i = 0; i < V; i++) {
            temp[i] = arr[i];
            cnt[i] = 0;
        }
        sort(temp, temp + V);
        int k = unique(temp, temp + V) - temp;
        for (int i = 0; i < V; i++) {
            a[i] = lower_bound(temp, temp + k, arr[i]) - temp;
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
} *mo;

#define MAXN 40010
#define MAXM 100010

int N, M, W[MAXN];
pii Q[MAXM];

int main() {
    ri(N);
    ri(M);
    G = new Graph(N);
    FOR(i, N) ri(W[i]);
    int u, v;
    FOR(i, N - 1) {
        ri(u);
        ri(v);
        G->addEdge(u - 1, v - 1);
    }
    FOR(i, M) {
        ri(Q[i].f); Q[i].f--;
        ri(Q[i].s); Q[i].s--;
    }
    mo = new MoTree(G, W, Q, M);
    FOR(i, M) printf("%d\n", mo->query(i));
    return 0;
}
