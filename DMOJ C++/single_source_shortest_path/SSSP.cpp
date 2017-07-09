/*
 * SSSP.cpp
 *
 *  Created on: Jul 8, 2017
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
        return (v == e.v && w == e.w && weight == e.weight);
    }

    bool operator != (const WeightedEdge &e) const {
        return !(v == e.v && w == e.w && weight == e.weight);
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
        return (weight > e.weight);
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

    vector<WeightedEdge*> adj(int v) {
        return adjList[v];
    }

    int degree(int v) {
        return adjList[v].size();
    }

    vector<WeightedEdge*> edges() {
        vector<WeightedEdge*> list;
        for (int v = 0; v < V; v++) {
            int selfLoops = 0;
            for (WeightedEdge *e : adj(v)) {
                if (e->other(v) > v) {
                    list.push_back(e);
                }
                // only add one copy of each self loop (self loops will be consecutive)
                else if (e->other(v) == v) {
                    if (selfLoops % 2 == 0) list.push_back(e);
                    selfLoops++;
                }
            }
        }
        return list;
    }
};

int N, M, u, v, w;
WeightedGraph *G;

double *distTo;
WeightedEdge **edgeTo;
priority_queue<pair<double, int>, vector<pair<double, int>> , greater<pair<double, int>>> pq;

void dijkstraSP(int s) {
    distTo = new double[G->getV()];
    edgeTo = new WeightedEdge *[G->getV()];
    for (int v = 0; v < G->getV(); v++) {
        distTo[v] = numeric_limits<double>::infinity();
    }
    distTo[s] = 0.0;
    pq.push({distTo[s], s});
    while (!pq.empty()) {
        int v = pq.top().second;
        pq.pop();
        for (WeightedEdge *e : G->adj(v)) {
            int w = e->other(v);
            if (distTo[w] > distTo[v] + e->getWeight()) {
                distTo[w] = distTo[v] + e->getWeight();
                edgeTo[w] = e;
                pq.push({distTo[w], w});
            }
        }
    }
}

int main() {
    ri(N);
    ri(M);
    G = new WeightedGraph(N);
    for (int i = 0; i < M; i++) {
        ri(u);
        ri(v);
        ri(w);
        u--;
        v--;
        G->addEdge(new WeightedEdge(u, v, w));
    }
    dijkstraSP(0);
    for (int i = 0; i < N; i++) {
        if (distTo[i] == D_INF) printf("-1\n");
        else printf("%d\n", (int) distTo[i]);
    }
    return 0;
}
