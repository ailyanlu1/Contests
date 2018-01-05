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

struct Digraph {
private:
    int V;
    int E;
    vector<int> *adjList;
    int *indegreeArr;

public:
    Digraph(int V) {
        this->V = V;
        this->E = 0;
        adjList = new vector<int>[V];
        indegreeArr = new int[V];
    }

    int getV() {
        return this->V;
    }

    int getE() {
        return this->E;
    }

    void addEdge(int v, int w) {
        adjList[v].push_back(w);
        indegreeArr[w]++;
        E++;
    }

    vector<int> &adj(int v) {
        return adjList[v];
    }

    int outdegree(int v) {
        return adjList[v].size();
    }

    int indegree(int v) {
        return indegreeArr[v];
    }

    Digraph *reverse() {
        Digraph *reverse = new Digraph(V);
        for (int v = 0; v < V; v++) {
            for (int w : adj(v)) {
                reverse->addEdge(w, v);
            }
        }
        return reverse;
    }

    vector<pair<int, int>> &edges() {
        vector<pair<int, int>> *list = new vector<pair<int, int>>;
        for (int v = 0; v < V; v++) {
            for (int w : adj(v)) {
                list->push_back(make_pair(v, w));
            }
        }
        return *list;
    }
};

#define MAXN 300010

int N, M, Q[MAXN];
Digraph *G;

int dfs(int v, int prev) {
    if (G->outdegree(v) == 0) return Q[v];
    int minPath = INT_MAX;
    for (int w : G->adj(v)) {
        if (w == prev) continue;
        minPath = min(minPath, dfs(w, v));
    }
    return Q[v] + minPath;
}

int main() {
    ri(N);
    ri(M);
    G = new Digraph(N);
    int ti, mi, xi;
    FOR(i, M) {
        ri(ti); ti--;
        ri(mi);
        FOR(i, mi) {
            ri(xi); xi--;
            G->addEdge(ti, xi);
        }
    }
    FOR(i, N) {
        ri(Q[i]);
    }
    printf("%d\n", dfs(0, 0));
    return 0;
}
