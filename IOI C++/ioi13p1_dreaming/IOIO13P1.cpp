/*
 * IOIO13P1.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
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
#define rc(x) scanf("%c", &x)
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
        return (v == e.v && w == e.w && weight == e.weight);
    }

    bool operator != (const WeightedEdge &e) {
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
} *G;

#define MAXN 100000

int ret, len, vD;
bool vis1[MAXN], vis2[MAXN];

pii getLongest(bool *vis, int src) {
    queue<pii> q;
    q.push({src, 0});
    int maxD = -1, maxV = -1;
    vis[src] = true;
    while(!q.empty()) {
        int v = q.front().f;
        int d = q.front().s;
        if (d > maxD) {
            maxD = d;
            maxV = v;
        }
        q.pop();
        for (WeightedEdge *e: G->adj(v)) {
            int w = e->other(v);
            if (vis[w]) continue;
            vis[w] = true;
            q.push({w, d + e->getWeight()});
        }
    }
    return mp(maxD, maxV);
}

bool dfs(int v, int prev, int l) {
    if (v == vD) return true;
    for (WeightedEdge *e: G->adj(v)) {
        int w = e->other(v);
        if (w == prev) continue;
        if (dfs(w, v, l + e->getWeight())) {
            ret = min(ret, max(len - l, l));
            return true;
        }
    }
    return false;
}

int getDiameter(int v) {
    return getLongest(vis1, getLongest(vis2, v).s).f;
}

int getRadius(int v) {
    int w = getLongest(vis2, v).s;
    pii d = getLongest(vis1, w);
    vD = d.s;
    ret = len = d.f;
    dfs(w, -1, 0);
    return ret;
}

int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
    G = new WeightedGraph(N);
    for (int i = 0; i < M; i++) {
        G->addEdge(new WeightedEdge(A[i], B[i], T[i]));
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (!vis1[i]) ans = max(ans, getDiameter(i));
    }
    Fill(vis1, false);
    Fill(vis2, false);
    vector<int> rad;
    for (int i = 0; i < N; i++) {
        if (!vis1[i]) rad.pb(getRadius(i));
    }
    sort(rad.begin(), rad.end(), greater<int>());
    if (rad.size() > 1) ans = max(ans, L + rad[0] + rad[1]);
    if (rad.size() > 2) ans = max(ans, 2 * L + rad[1] + rad[2]);
    return ans;
}

int main() {
    int N, M, L;
    ri(N);
    ri(M);
    ri(L);
    int A[M], B[M], T[M];
    for (int i = 0; i < M; i++) {
        ri(A[i]);
        ri(B[i]);
        ri(T[i]);
    }
    printf("%d\n", travelTime(N, M, L, A, B, T));
    return 0;
}
