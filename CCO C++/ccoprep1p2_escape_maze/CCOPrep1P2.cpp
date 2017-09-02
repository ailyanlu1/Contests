#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
#define m(x, y) (x + (y - x) / 2)
#define MIN(a, b) (a = min(a, b))
#define MAX(a, b) (a = max(a, b))
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
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) (rand() % (b - a + 1) + a)

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<int, float> pif;
typedef pair<float, int> pfi;
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
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

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
};

class Biconnected {
private:
    int *low;
    int *pre;
    vector<unordered_set<int>> components;
    int cnt;
    bool *articulation;
    stack<pair<int, int>> s;

    void dfs(Graph *G, int v, int prev) {
        int children = 0;
        pre[v] = low[v] = cnt++;
        for (int w : G->adj(v)) {
            if (pre[w] == -1) {
                children++;
                s.push(make_pair(v, w));
                dfs(G, w, v);
                // update low number
                low[v] = min(low[v], low[w]);
                // non-root of DFS is an articulation point if low[w] >= pre[v]
                if ((prev == v && children > 1) || (prev != v && low[w] >= pre[v])) {
                    articulation[v] = true;
                    components.push_back(unordered_set<int>());
                    while (s.top().first != v && s.top().second != w) {
                        components.back().insert(s.top().first);
                        components.back().insert(s.top().second);
                        s.pop();
                    }
                    components.back().insert(s.top().first);
                    components.back().insert(s.top().second);
                    s.pop();
                }
            }
            // update low number - ignore reverse of edge leading to v
            else if (w != prev && pre[w] < low[v]) {
                low[v] = pre[w];
                s.push(make_pair(v, w));
            }
        }
    }

public:
    Biconnected(Graph *G) {
        cnt = 0;
        low = new int[G->getV()];
        pre = new int[G->getV()];
        articulation = new bool[G->getV()];
        for (int v = 0; v < G->getV(); v++) {
            low[v] = -1;
            pre[v] = -1;
            articulation[v] = false;
        }
        for (int v = 0; v < G->getV(); v++) {
            if (pre[v] == -1) dfs(G, v, v);
            if (!s.empty()) {
                components.push_back(unordered_set<int>());
                while (!s.empty()) {
                    components.back().insert(s.top().first);
                    components.back().insert(s.top().second);
                    s.pop();
                }
            }
        }
    }

    // is vertex v an articulation point?
    bool isArticulation(int v) {
        return articulation[v];
    }

    vector<unordered_set<int>> &getComponents() {
        return components;
    }

    unordered_set<int> &getComponent(int id) {
        return components[id];
    }

    int getSize(int id) {
        return components[id].size();
    }

    int countComponents() {
        return components.size();
    }
};

#define MAXST 405

int N, s, t;
Graph *G;
Biconnected *bc;

int main() {
    ri(N);
    while (N != 0) {
        int exits = 0;
        llu ways = 1LLU;
        G = new Graph(MAXST); // bad for memory, but this question isn't that demanding
        FOR(i, N) {
            ri(s);
            ri(t);
            G->addEdge(s - 1, t - 1);
        }
        bc = new Biconnected(G);
        for(unordered_set<int> comp : bc->getComponents()) {
            int cnt = 0;
            for (int v : comp) {
                if (bc->isArticulation(v)) {
                    cnt++;
                }
            }
            if (cnt <= 1) {
                exits++;
                ways *= comp.size() - cnt;
            }
        }
        if (exits == 1) {
            exits = 2;
            ways = ways * (ways - 1) / 2;
        }
        printf("%d %llu\n", exits, ways);
        ri(N);
    }
    return 0;
}
