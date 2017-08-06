/*
 * THICC17P6.cpp
 *
 *  Created on: Aug 5, 2017
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
    int weight;

public:
    WeightedEdge(int v, int w, int weight) {
        this->v = v;
        this->w = w;
        this->weight = weight;
    }

    int getWeight() {
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

#define MAXN 200005

int N, T, a, b, c, total = 0, dist[3][MAXN], maxDist;
vector<int> leaves;
WeightedGraph *G;

void dfs(int v, int prev, int d, int i) {
    dist[i][v] = d;
    for (WeightedEdge *e: G->adj(v)) {
        int w = e->other(v);
        if (w == prev) continue;
        dfs(w, v, d + e->getWeight(), i);
    }
}

int main() {
    ri(N);
    ri(T);
    G = new WeightedGraph(N);
    for (int i = 0; i < N - 1; i++) {
        ri(a);
        ri(b);
        ri(c);
        G->addEdge(new WeightedEdge(a - 1, b - 1, c));
        total += c;
    }
    total *= 2;
    dfs(0, -1, 0, 0);
    maxDist = 0;
    int d1, d2;
    for (int v = 0; v < N; v++) {
        if (dist[0][v] > maxDist) {
            maxDist = dist[0][v];
            d1 = v;
        }
    }
    dfs(d1, -1, 0, 1);
    maxDist = 0;
    for (int v = 0; v < N; v++) {
        if (dist[1][v] > maxDist) {
            maxDist = dist[1][v];
            d2 = v;
        }
    }
    dfs(d2, -1, 0, 2);
    for (int v = 0; v < N; v++) {
        if (G->degree(v) == T) {
            printf("%d %d\n", v + 1, total - max(dist[1][v], dist[2][v]));
        }
    }
    return 0;
}
