/*
 * RTE16S3.cpp
 *
 *  Created on: Aug 4, 2017
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

struct WeightedEdge {
private:
    int v, w;
    double weight;

public:
    WeightedEdge(int v, int w, double weight) {
        this->v = v;
        this->w = w;
        this->weight = weight;
    }

    double getWeight() {
        return weight;
    }

    int either() {
        return v;
    }

    int other(int vertex) {
        if (vertex == v) return w;
        else if (vertex == w) return v;
        else throw new invalid_argument("Illegal endpoint");
    }

    bool operator == (const WeightedEdge &e) const {
        return (((v == e.v && w == e.w) || (v == e.w && w == e.v)) && weight == e.weight);
    }

    bool operator != (const WeightedEdge &e) const {
        return !(((v == e.v && w == e.w) || (v == e.w && w == e.v)) && weight == e.weight);
    }

    bool operator < (const WeightedEdge &e) const {
        return (weight < e.weight);
    }

    bool operator <= (const WeightedEdge &e) const {
        return (weight <= e.weight);
    }

    bool operator > (const WeightedEdge &e) const {
        return (weight > e.weight);
    }

    bool operator >= (const WeightedEdge &e) const {
        return (weight >= e.weight);
    }
};

struct WeightedEdge_less {
    const bool operator() (const WeightedEdge *a, const WeightedEdge *b) const {
        return *a < *b;
    }
};

struct WeightedEdge_greater {
    const bool operator() (const WeightedEdge *a, const WeightedEdge *b) const {
        return *a > *b;
    }
};

struct WeightedGraph {
private:
    int V;
    int E;
    vector<WeightedEdge*>* adjList;

public:
    WeightedGraph(int V) {
        this->V = V;
        this->E = 0;
        adjList = new vector<WeightedEdge*>[V];
    }

    int getV() {
        return this->V;
    }

    int getE() {
        return this->E;
    }

    void addEdge(WeightedEdge *e) {
        int v = e->either();
        int w = e->other(v);
        adjList[v].push_back(e);
        adjList[w].push_back(e);
        E++;
    }

    vector<WeightedEdge*> &adj(int v) {
        return adjList[v];
    }

    int degree(int v) {
        return adjList[v].size();
    }

    vector<WeightedEdge*> &edges() {
        vector<WeightedEdge*> *list = new vector<WeightedEdge*>;
        for (int v = 0; v < V; v++) {
            int selfLoops = 0;
            for (WeightedEdge *e : adj(v)) {
                if (e->other(v) > v) {
                    list->push_back(e);
                }
                // only add one copy of each self loop (self loops will be consecutive)
                else if (e->other(v) == v) {
                    if (selfLoops % 2 == 0) list->push_back(e);
                    selfLoops++;
                }
            }
        }
        return *list;
    }
};

class WeightedLCA {
private:
    int *depth, *parent, *chain, *size, *head;
    int chainNum;

    void dfs(WeightedGraph *G, int v, int d, int prev) {
        depth[v] = d;
        parent[v] = prev;
        size[v] = 1;
        for (WeightedEdge *e: G->adj(v)) {
            int w = e->other(v);
            if (w != prev) {
                dfs(G, w, d + 1, v);
                size[v] += size[w];
            }
        }
    }

    void hld(WeightedGraph *G, int v, int prev) {
        if (head[chainNum] == -1) head[chainNum] = v;
        chain[v] = chainNum;
        int maxIndex = -1;
        for (WeightedEdge *e: G->adj(v)) {
            int w = e->other(v);
            if (w != prev && (maxIndex == -1 || size[maxIndex] < size[w])) maxIndex = w;
        }
        if (maxIndex != -1) hld(G, maxIndex, v);
        for (WeightedEdge *e: G->adj(v)) {
            int w = e->other(v);
            if (w != prev && w != maxIndex) {
                chainNum++;
                hld(G, w, v);
            }
        }
    }

public:
    WeightedLCA(WeightedGraph *G) {
        depth = new int[G->getV()];
        parent = new int[G->getV()];
        chain = new int[G->getV()];
        size = new int[G->getV()];
        head = new int[G->getV()];
        chainNum = 0;
        for (int i = 0; i < G->getV(); i++) {
            head[i] = -1;
        }
        dfs(G, 0, 0, -1);
        hld(G, 0, -1);
    }

    /**
     * Returns the lowest common ancestor of vertex {@code v} and {@code w}.
     *
     * @param v the first vertex
     * @param w the first vertex
     * @return the lowest common ancestor of vertex {@code v} and {@code w}
     */
    int lca(int v, int w) {
        while (chain[v] != chain[w]) {
            if (depth[head[chain[v]]] < depth[head[chain[w]]]) w = parent[head[chain[w]]];
            else v = parent[head[chain[v]]];
        }
        if (depth[v] < depth[w]) return v;
        return w;
    }
};

class UndirectedAcyclicAPSP {
private:
    double *distTo; // stores the distance from an arbitrary root
    WeightedLCA *LCA;

    void bfs(WeightedGraph *G, int s) {
        queue<int> q;
        bool marked[G->getV()];
        for (int v = 0; v < G->getV(); v++) {
            marked[v] = false;
            distTo[v] = numeric_limits<double>::infinity();
        }
        distTo[s] = 0;
        marked[s] = true;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (WeightedEdge *e: G->adj(v)) {
                int w = e->other(v);
                if (!marked[w]) {
                    distTo[w] = distTo[v] + e->getWeight();
                    marked[w] = true;
                    q.push(w);
                }
            }
        }
    }

public:
    UndirectedAcyclicAPSP(WeightedGraph *G) {
        distTo = new double[G->getV()];
        LCA = new WeightedLCA(G);
        bfs(G, 0);
    }

    /**
     * Returns the length of a shortest path from vertex {@code s} to vertex {@code t}.
     * @param  s the source vertex
     * @param  t the destination vertex
     * @return the length of a shortest path from vertex {@code s} to vertex {@code t};
     * @throws IllegalArgumentException unless {@code 0 <= s < V}
     * @throws IllegalArgumentException unless {@code 0 <= t < V}
     */
    double dist(int s, int t) {
        return distTo[s] + distTo[t] - 2 * distTo[LCA->lca(s, t)];
    }
};

int N, Q, a, b, c;
WeightedGraph *G;
UndirectedAcyclicAPSP *sp;

int main() {
    ri(N);
    G = new WeightedGraph(N);
    for (int i = 0; i < N - 1; i++) {
        ri(a);
        ri(b);
        ri(c);
        G->addEdge(new WeightedEdge(a, b, c));
    }
    sp = new UndirectedAcyclicAPSP(G);
    ri(Q);
    for (int i = 0; i < Q; i++) {
        ri(a);
        ri(b);
        printf("%lld\n", (ll) sp->dist(a, b));
    }
    return 0;
}
