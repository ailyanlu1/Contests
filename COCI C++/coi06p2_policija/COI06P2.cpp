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
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
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

#define MAXN 100005

int N, E, Q, pre[MAXN], post[MAXN], low[MAXN], dep[MAXN], cnt = 0;
bool ans;
vector<int> tree[MAXN];
Graph *G;

void dfs(int v, int prev) {
    pre[v] = low[v] = cnt++;
    dep[v] = dep[prev] + 1;
    for (int w : G->adj(v)) {
        if (w == prev) continue;
        if (dep[w] == -1) {
            dfs(w, v);
            low[v] = min(low[v], low[w]);
            tree[v].pb(w);
        } else {
            low[v] = min(low[v], pre[w]);
        }
    }
    post[v] = cnt++;
}

// is w in the subtree of v
inline bool inSubtree(int v, int w) {
    return pre[v] <= pre[w] && post[v] >= post[w];
}

// find the child of v that contains w
int findSubtree(int v, int w) {
    int lo = 0, hi = tree[v].size() - 1, mid;
    while (lo <= hi) {
        mid = mid(lo, hi);
        if (pre[w] > post[tree[v][mid]]) lo = mid + 1;
        else if (pre[tree[v][mid]] > post[w]) hi = mid - 1;
        else break;
    }
    return tree[v][mid];
}

int main() {
    ri(N);
    ri(E);
    G = new Graph(N);
    for (int i = 0, a, b; i < E; i++) {
        ri(a);
        ri(b);
        G->addEdge(a - 1, b - 1);
    }
    for (int i = 0; i < N; i++) {
        dep[i] = -1;
    }
    dfs(0, 0);
    ri(Q);
    for (int i = 0, t, a, b, c, d, e, f; i < Q; i++) {
        ri(t);
        if (t == 1) {
            ri(a); ri(b); ri(c); ri(d);
            a--; b--; c--; d--;
            if (inSubtree(d, c)) swap(d, c);
            ans = dep[c] + 1 != dep[d] || low[d] < pre[d] || inSubtree(d, a) == inSubtree(d, b);
        } else {
            ri(a); ri(b); ri(c);
            a--; b--; c--;
            e = inSubtree(c, a) ? findSubtree(c, a) : -1;
            f = inSubtree(c, b) ? findSubtree(c, b) : -1;
            ans = e == f || ((e == -1 || low[e] < pre[c]) && (f == -1 || low[f] < pre[c]));
        }
        printf(ans ? "yes\n" : "no\n");
    }
    return 0;
}
