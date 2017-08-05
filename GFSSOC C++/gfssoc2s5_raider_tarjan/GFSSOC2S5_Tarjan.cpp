/*
 * GFSSOC2S5_Tarjan.cpp
 *
 *  Created on: Aug 1, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
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
#define randi(a, b) rand() % (b - a + 1) + a

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

struct Digraph {
private:
    int V;
    int E;
    vector<int>* adjList;
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
};

class TarjanSCC {
private:
    bool *marked;            // marked[v] = has v been visited?
    int *id;                 // id[v] = id of strong component containing v
    int *low;                // low[v] = low number of v
    int pre;                 // preorder number counter
    int count;               // number of strongly-connected components
    stack<int> s;

    void dfs(Digraph *G, int v) {
        marked[v] = true;
        low[v] = pre++;
        int min = low[v];
        s.push(v);
        for (int w : G->adj(v)) {
            if (!marked[w]) dfs(G, w);
            if (low[w] < min) min = low[w];
        }
        if (min < low[v]) {
            low[v] = min;
            return;
        }
        int w;
        do {
            w = s.top();
            s.pop();
            id[w] = count;
            low[w] = G->getV();
        } while (w != v);
        count++;
    }

public:
    /**
     * Computes the strong components of the digraph {@code G}.
     * @param G the digraph
     */
    TarjanSCC(Digraph *G) {
        marked = new bool[G->getV()];
        id = new int[G->getV()];
        low = new int[G->getV()];
        for (int v = 0; v < G->getV(); v++) {
            marked[v] = false;
        }
        pre = 0;
        count = 0;
        for (int v = 0; v < G->getV(); v++) {
            if (!marked[v]) dfs(G, v);
        }
    }

    /**
     * Returns the number of strong components.
     * @return the number of strong components
     */
    int getCount() {
        return count;
    }


    /**
     * Are vertices {@code v} and {@code w} in the same strong component?
     * @param  v one vertex
     * @param  w the other vertex
     * @return {@code true} if vertices {@code v} and {@code w} are in the same
     *         strong component, and {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     * @throws IllegalArgumentException unless {@code 0 <= w < V}
     */
    bool stronglyConnected(int v, int w) {
        return id[v] == id[w];
    }

    /**
     * Returns the component id of the strong component containing vertex {@code v}.
     * @param  v the vertex
     * @return the component id of the strong component containing vertex {@code v}
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    int getId(int v) {
        return id[v];
    }
};

#define MAXN 500000
#define MOD (int) (1e9 + 7)

int N, M, V[MAXN], a, b, sumV[MAXN];
pii dp[MAXN][2];
Digraph *G, *prov;
TarjanSCC *scc;

void rebuild() {
    prov = new Digraph(scc->getCount());
    int idV, idW;
    for (int v = 0; v < N; v++) {
        idV = scc->getId(v);
        for (int w : G->adj(v)) {
            idW = scc->getId(w);
            if (idV != idW) prov->addEdge(idV, idW);
        }
    }
}

pii solve(int v, bool take) {
    if (v == scc->getId(N - 1)) {
        if (take) return mp(sumV[v], 1);
        else return mp(0, 1);
    }
    if (dp[v][take] != mp(-1, -1)) return dp[v][take];
    pii ret = mp(INT_MIN, 0);
    pii hold;
    for (int w : prov->adj(v)) {
        if (take) {
            hold = solve(w, false);
            hold.f += sumV[v];
            if (hold.f > ret.f) ret = hold;
            else if (hold.f == ret.f) ret.s = (ret.s + hold.s) % MOD;
        }
        hold = solve(w, true);
        if (hold.f > ret.f) ret = hold;
        else if (hold.f == ret.f) ret.s = (ret.s + hold.s) % MOD;
    }
    return dp[v][take] = ret;
}

int main() {
    ri(N);
    ri(M);
    G = new Digraph(N);
    for (int i = 0; i < N; i++) {
        ri(V[i]);
    }
    for (int i = 0; i < M; i++) {
        ri(a);
        ri(b);
        G->addEdge(a - 1, b - 1);
    }
    scc = new TarjanSCC(G);
    for (int v = 0; v < N; v++) {
        sumV[scc->getId(v)] += V[v];
    }
    for (int i = 0; i < scc->getCount(); i++) {
        dp[i][0] = dp[i][1] = mp(-1, -1);
    }
    rebuild();
    pii ans = solve(scc->getId(0), true);
    printf("%d %d\n", ans.f, ans.s);
    return 0;
}
