#include <bits/stdc++.h>

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
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define FILL(a, x) memset((a), (x), sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<int, double> pid;
typedef pair<double, int> pdi;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef pair<llu, llu> pllu;
typedef pair<int, llu> pillu;
typedef pair<llu, int> pllui;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef map<ll, ll> mll;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;
typedef unordered_map<ll, ll> umll;

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

#define MAXN 200010

int N, R, a, b, rr, X, Y, edgeTo[MAXN], marked[MAXN];
bool RR[MAXN];

void dfs1(int v, int prev) {
    for (int w : G->adj(v)) {
        if (w == prev) continue;
        edgeTo[w] = v;
        dfs1(w, v);
    }
}

int dfs2(int v, int d) {
    marked[v] = true;
    if (RR[v]) return d;
    int ret = INT_INF;
    for (int w : G->adj(v)) {
        if (marked[w]) continue;
        MIN(ret, dfs2(w, d + 1));
    }
    return ret;
}

int main() {
    ri(N);
    ri(R);
    G = new Graph(N);
    FOR(i, N) {
        RR[i] = 0;
        edgeTo[i] = -1;
        marked[i] = false;
    }
    FOR(i, N - 1) {
        ri(a); a--;
        ri(b); b--;
        G->addEdge(a, b);
    }
    FOR(i, R) {
        ri(rr); rr--;
        RR[rr] = 1;
    }
    ri(X); X--;
    ri(Y); Y--;
    dfs1(X, X);
    int ans = INT_INF;
    for (int v = Y; v != -1; v = edgeTo[v]) marked[v] = 1;
    for (int v = Y; v != -1; v = edgeTo[v]) MIN(ans, dfs2(v, 0));
    printf("%d\n", ans);
    return 0;
}
