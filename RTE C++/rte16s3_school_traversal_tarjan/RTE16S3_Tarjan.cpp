/*
 * RTE16S3_Tarjan.cpp
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

struct UF {
private:
    int* parent;
    char* rank; // equivalent to byte
    int count;

public:
    /**
     * Initializes an empty union–find data structure with {@code n} sites
     * {@code 0} through {@code n-1}. Each site is initially in its own
     * component.
     *
     * @param  n the number of sites
     */
    UF(int n) {
        count = n;
        parent = new int[n];
        rank = new char[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    /**
     * Returns the component identifier for the component containing site {@code p}.
     *
     * @param  p the integer representing one site
     * @return the component identifier for the component containing site {@code p}
     */
    int find(int p) {
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];    // path compression by halving
            p = parent[p];
        }
        return p;
    }

    /**
     * Returns the number of components.
     *
     * @return the number of components (between {@code 1} and {@code n})
     */
    int getCount() {
        return count;
    }

    /**
     * Returns true if the the two sites are in the same component.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     * @return {@code true} if the two sites {@code p} and {@code q} are in the same component;
     *         {@code false} otherwise
     */
    bool connected(int p, int q) {
        return find(p) == find(q);
    }

    /**
     * Returns the rank by size of the component containing p
     *
     * @param p the integer representing one site
     * @return the rank by size of the component containing p
     */
    int getRank(int p) {
        return (int) rank[find(p)];
    }

    /**
     * Merges the component containing site {@code p} with the
     * the component containing site {@code q}.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     */
    void join(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return;

        // make root of smaller rank point to root of larger rank
        if      (rank[rootP] < rank[rootQ]) parent[rootP] = rootQ;
        else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootP;
        else {
            parent[rootQ] = rootP;
            rank[rootP]++;
        }
        count--;
    }

    /**
     * Unmerges the component containing site {@code p} with the
     * the component containing site {@code q}.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     */
    void disjoin(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if      (rank[rootP] < rank[rootQ]) parent[rootP] = rootP;
        else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootQ;
        else {
            parent[rootQ] = rootQ;
            rank[rootP]--;
        }
        count++;
    }
};

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

class TarjanWeightedLCA {
private:
    const bool WHITE = false;
    const bool BLACK = true;

    bool *color;
    int *ancestor;
    vector<pair<int, int>> *queriesList;
    vector<int> answers;
    UF *uf;

    void dfs(WeightedGraph *G, int v, int prev) {
        ancestor[v] = v;
        for (WeightedEdge *e : G->adj(v)) {
            int w = e->other(v);
            if (w == prev) continue;
            dfs(G, w, v);
            uf->join(v, w);
            ancestor[uf->find(v)] = v;
        }
        color[v] = BLACK;
        for (pair<int, int> q : queriesList[v]) {
            if (color[q.first] == BLACK) answers[q.second] = ancestor[uf->find(q.first)];
        }
    }

public:
    TarjanWeightedLCA(WeightedGraph *G, vector<pair<int, int>> &queries) : answers(queries.size()) {
        color = new bool[G->getV()];
        ancestor = new int[G->getV()];
        queriesList = new vector<pair<int, int>>[G->getV()];
        uf = new UF(G->getV());
        for (int v = 0; v < G->getV(); v++) {
            color[v] = WHITE;
        }
        for (int i = 0; i < queries.size(); i++) {
            queriesList[queries[i].first].push_back(make_pair(queries[i].second, i));
            queriesList[queries[i].second].push_back(make_pair(queries[i].first, i));
        }
        dfs(G, 0, -1);
    }

    vector<int> &getAnswers() {
        return answers;
    }
};

#define MAXN 6000

int N, Q, a, b, c;
WeightedGraph *G;
double distTo[MAXN];;
TarjanWeightedLCA *lca;
vector<pii> queries;

void bfs(int s) {
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

int main() {
    ri(N);
    G = new WeightedGraph(N);
    for (int i = 0; i < N - 1; i++) {
        ri(a);
        ri(b);
        ri(c);
        G->addEdge(new WeightedEdge(a, b, c));
    }
    bfs(0);
    ri(Q);
    for (int i = 0; i < Q; i++) {
        ri(a);
        ri(b);
        queries.pb(mp(a, b));
    }
    lca = new TarjanWeightedLCA(G, queries);
    for (int i = 0; i < Q; i++) {
        printf("%lld\n", (ll) (distTo[queries[i].f] + distTo[queries[i].s] - 2 * distTo[lca->getAnswers()[i]]));
    }
    return 0;
}
