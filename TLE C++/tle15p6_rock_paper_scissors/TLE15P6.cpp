/*
 * TLE15P6.cpp
 *
 *  Created on: Aug 2, 2017
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
    int *size;
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
            size[count]++;
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
        size = new int[G->getV()];
        low = new int[G->getV()];
        for (int v = 0; v < G->getV(); v++) {
            marked[v] = false;
            size[v] = 0;
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
     */
    bool stronglyConnected(int v, int w) {
        return id[v] == id[w];
    }

    /**
     * Returns the component id of the strong component containing vertex {@code v}.
     * @param  v the vertex
     * @return the component id of the strong component containing vertex {@code v}
     */
    int getId(int v) {
        return id[v];
    }

    /**
     * Returns the size of the strong component containing vertex {@code v}.
     * @param  v the vertex
     * @return the size of the strong component containing vertex {@code v}
     */
    int getSize(int v) {
        return size[id[v]];
    }

    /**
     * Returns the size of the specified id.
     * @param  x the id number
     * @return the size of the specified id
          */
    int getIdSize(int x) {
        return size[x];
    }
};

#define MAXN 5000

int N, M, Q, a, b, dp[MAXN][MAXN], cnt;
Digraph *G, *GG;
TarjanSCC *scc;

void rebuild() {
    GG = new Digraph(cnt);
    int idV, idW;
    for (int v = 0; v < N; v++) {
        idV = scc->getId(v);
        for (int w : G->adj(v)) {
            idW = scc->getId(w);
            if (idV != idW) GG->addEdge(idV, idW);
        }
    }
}

int dfs(int v, int x) {
    if (dp[v][x] != -1) return dp[v][x];
    if (v == x) return dp[v][x] = 0;
    int ret = -INT_INF;
    for (int w : GG->adj(v)) {
        ret = max(ret, dfs(w, x) + scc->getIdSize(v));
    }
    return dp[v][x] = ret;
}

int main() {
    ri(N);
    ri(M);
    ri(Q);
    G = new Digraph(N);
    for (int i = 0; i < M; i++) {
        ri(a);
        ri(b);
        G->addEdge(a - 1, b - 1);
    }
    scc = new TarjanSCC(G);
    cnt = scc->getCount();
    rebuild();
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < cnt; j++) {
            dp[i][j] = -1;
        }
    }
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < cnt; j++) {
            dfs(i, j);
        }
    }
    for (int i = 0, idA, idB; i < Q; i++) {
        ri(a);
        ri(b);
        idA = scc->getId(a - 1);
        idB = scc->getId(b - 1);
        if (dp[idA][idB] > 0) printf("%d %d\n", a, dp[idA][idB] - scc->getIdSize(idA));
        else if (dp[idB][idA] > 0) printf("%d %d\n", b, dp[idB][idA] - scc->getIdSize(idB));
        else printf("Indeterminate\n");
    }
    return 0;
}
