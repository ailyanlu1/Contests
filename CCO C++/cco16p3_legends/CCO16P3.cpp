#include <bits/stdc++.h>

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

template <typename T1, typename T2>
struct pair_hash {
    size_t operator () (const pair<T1,T2> &p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 << 31 | h2;
    }
};

struct Graph {
private:
    int V;
    int E;
    vector<int>* adjList;

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

int S, T, N, M, a, b, *dep, *par, *cnt;
bool *vis, *visEdges;
unordered_map<pii, int, pair_hash<int, int>> edgeInd;
vector<int> stk;
vector<pii> edges;
unordered_set<int> vset;
Graph *G;

void dfs(int v, int prev) {
    par[v] = prev;
    dep[v] = dep[prev] + 1;
    for (int w : G->adj(v)) {
        if (w != prev && dep[w] == -1) dfs(w, v);
    }
}

bool solve1() {
    dep = new int[N];
    par = new int[N];
    cnt = new int[N];
    for (int v = 0; v < N; v++) {
        dep[v] = -1;
        par[v] = -1;
        cnt[v] = 0;
    }
    dfs(0, 0);
    int v, w;
    for (pii e : G->edges()) {
        v = e.f;
        w = e.s;
        if (par[v] != w && par[w] != v) {
            while (v != w) {
                if (dep[v] > dep[w]) {
                    cnt[v]++;
                    v = par[v];
                } else {
                    cnt[w]++;
                    w = par[w];
                }
            }
        }
    }
    for (int v = 0; v < N; v++) {
        if (cnt[v] >= 2) return true;
    }
    return false;
}

bool solve2() {
    return M >= N;
}

bool solve3() {
    dep = new int[N];
    par = new int[N];
    cnt = new int[N];
    for (int v = 0; v < N; v++) {
        dep[v] = -1;
        par[v] = -1;
        cnt[v] = 0;
    }
    dfs(0, 0);
    int v, w, dist;
    for (pii e : G->edges()) {
        v = e.f;
        w = e.s;
        if (par[v] != w && par[w] != v) {
            dist = 0;
            while (v != w) {
                dist++;
                if (dep[v] > dep[w]) {
                    cnt[v]++;
                    v = par[v];
                } else {
                    cnt[w]++;
                    w = par[w];
                }
            }
            if (dist >= 3) return true;
        }
    }
    for (int v = 0; v < N; v++) {
        if (cnt[v] >= 2) return true;
    }
    return false;
}

bool solve4() {
    for (int v = 0; v < N; v++) {
        if (G->degree(v) >= 3) return true;
    }
    return false;
}

bool dfs5(int v, int prev) {
    vis[v] = true;
    for (int w : G->adj(v)) {
        if (w == prev) continue;
        stk.push_back(v);
        if (vis[w]) {
            vset.clear();
            bool cycle = false;
            int cycleSz = 0, deg3cnt = 0;
            for (int x : stk) {
                if (x == w || cycle) {
                    cycle = true;
                    cycleSz++;
                    for (int y : G->adj(x)) {
                        vset.insert(y);
                    }
                    if (G->degree(x) >= 3) deg3cnt++;
                }
            }
            if (vset.size() - cycleSz >= 2 && deg3cnt >= 2) {
                vis[v] = false;
                stk.pop_back();
                return true;
            }
        } else {
            int ind = edgeInd[mp(v, w)];
            if (!visEdges[ind]) {
                visEdges[ind] = true;
                if (dfs5(w, v)) {
                    vis[v] = false;
                    stk.pop_back();
                    return true;
                }
            }
        }
        stk.pop_back();
    }
    vis[v] = false;
    return false;
}

bool solve5() {
    vis = new bool[N];
    visEdges = new bool[M * 2];
    edges = G->edges();
    edgeInd.clear();
    stk.clear();
    for (int v = 0; v < N; v++) {
        vis[v] = false;
    }
    for (int e = 0; e < M; e++) {
        visEdges[e] = visEdges[e + M] = false;
        edgeInd[mp(edges[e].f, edges[e].s)] = e;
        edgeInd[mp(edges[e].s, edges[e].f)] = e + M;
    }
    return dfs5(0, -1);
}


int main() {
    ri(S);
    ri(T);
    for (int t = 0; t < T; t++) {
        ri(N);
        ri(M);
        G = new Graph(N);
        for (int i = 0; i < M; i++) {
            ri(a);
            ri(b);
            G->addEdge(a - 1, b - 1);
        }
        bool ans;
        if (S == 1) {
            ans = solve1();
        } else if (S == 2) {
            ans = solve2();
        } else if (S == 3) {
            ans = solve3();
        } else if (S == 4) {
            ans = solve4();
        } else /*if (S == 5) */{
            ans = solve5();
        }
        printf("%s\n", ans ? "YES" : "NO");
    }
    return 0;
}
