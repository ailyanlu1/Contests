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

struct DirectedWeightedEdge {
private:
    int v, w;
    double weight;

public:
    DirectedWeightedEdge(int v, int w, double weight) {
        this->v = v;
        this->w = w;
        this->weight = weight;
    }

    double getWeight() {
        return weight;
    }

    int from() {
        return v;
    }

    int to() {
        return w;
    }

    bool operator == (const DirectedWeightedEdge &e) const {
        return (v == e.v && w == e.w && weight == e.weight);
    }

    bool operator != (const DirectedWeightedEdge &e) const {
        return !(v == e.v && w == e.w && weight == e.weight);
    }

    bool operator < (const DirectedWeightedEdge &e) const {
        return (weight < e.weight);
    }

    bool operator <= (const DirectedWeightedEdge &e) const {
        return (weight <= e.weight);
    }

    bool operator > (const DirectedWeightedEdge &e) const {
        return (weight > e.weight);
    }

    bool operator >= (const DirectedWeightedEdge &e) const {
        return (weight >= e.weight);
    }
};

struct DirectedWeightedEdge_less {
    const bool operator() (const DirectedWeightedEdge *a, const DirectedWeightedEdge *b) const {
        return *a < *b;
    }
};

struct DirectedWeightedEdge_greater {
    const bool operator() (const DirectedWeightedEdge *a, const DirectedWeightedEdge *b) const {
        return *a > *b;
    }
};

struct WeightedDigraph {
private:
    int V;
    int E;
    vector<DirectedWeightedEdge*>* adjList;
    int *indegreeArr;

public:
    WeightedDigraph(int V) {
        this->V = V;
        this->E = 0;
        adjList = new vector<DirectedWeightedEdge*>[V];
        indegreeArr = new int[V];
    }

    int getV() {
        return this->V;
    }

    int getE() {
        return this->E;
    }

    void addEdge(DirectedWeightedEdge *e) {
        int v = e->from();
        int w = e->to();
        adjList[v].push_back(e);
        indegreeArr[w]++;
        E++;
    }

    vector<DirectedWeightedEdge*> &adj(int v) {
        return adjList[v];
    }

    int outdegree(int v) {
        return adjList[v].size();
    }

    int indegree(int v) {
        return indegreeArr[v];
    }

    vector<DirectedWeightedEdge*> &edges() {
        vector<DirectedWeightedEdge*> *list = new vector<DirectedWeightedEdge*>;
        for (int v = 0; v < V; v++) {
            for (DirectedWeightedEdge *e : adj(v)) {
                list->push_back(e);
            }
        }
        return *list;
    }

    WeightedDigraph *reverse() {
        WeightedDigraph *reverse = new WeightedDigraph(V);
        for (int v = 0; v < V; v++) {
            for (DirectedWeightedEdge *e : adj(v)) {
                reverse->addEdge(new DirectedWeightedEdge(e->to(), e->from(), e->getWeight()));
            }
        }
        return reverse;
    }
};

int N, M, u, v, w;
WeightedDigraph *G;

double *distTo;
bool *inQueue;
deque<int> q;

void spfa(int s) {
    distTo = new double[G->getV()];
    inQueue = new bool[G->getV()];
    for (int v = 0; v < G->getV(); v++) {
        distTo[v] = numeric_limits<double>::infinity();
        inQueue[v] = false;
    }
    distTo[s] = 0.0;
    inQueue[s] = true;
    q.push_back(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        inQueue[v] = false;
        for (DirectedWeightedEdge *e : G->adj(v)) {
            int w = e->to();
            if (distTo[w] > distTo[v] + e->getWeight()) {
                distTo[w] = distTo[v] + e->getWeight();
                if (!inQueue[w]) {
                    if (!q.empty() && distTo[w] < distTo[q.front()]) q.push_front(w);
                    else q.push_back(w);
                    inQueue[w] = true;
                }
            }
        }
    }
}

int main() {
    ri(N);
    ri(M);
    G = new WeightedDigraph(N);
    for (int i = 0; i < M; i++) {
        ri(u);
        ri(v);
        ri(w);
        u--;
        v--;
        G->addEdge(new DirectedWeightedEdge(u, v, w));
    }
    spfa(0);
    printf("%lld\n", (ll) distTo[N - 1]);
    return 0;
}
