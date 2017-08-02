/*
 * COCI14C1P6.cpp
 *
 *  Created on: Jun 23, 2017
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

#define MAXN 1000000

struct WeightedEdge {
private:
    int v, w;
    ll weight;
public:
    WeightedEdge(int v, int w, ll weight) {
        this->v = v;
        this->w = w;
        this->weight = weight;
    }

    ll getWeight() {
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
};

struct WeightedGraph {
private:
    int V;
    int E;
    vector<WeightedEdge*>* adj;

public:
    WeightedGraph(int V) {
        if (V < 0) throw new invalid_argument("Number of vertices must be nonnegative");
        this->V = V;
        this->E = 0;
        adj = new vector<WeightedEdge*>[V];
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
        adj[v].pb(e);
        adj[w].pb(e);
        E++;
    }

    vector<WeightedEdge*> &adjTo(int v) {
        return adj[v];
    }

    int degree(int v) {
        return adj[v].size();
    }

    vector<WeightedEdge*> &edges() {
        vector<WeightedEdge*> list;
        for (int v = 0; v < V; v++) {
            int selfLoops = 0;
            for (WeightedEdge *e : adjTo(v)) {
                if (e->other(v) > v) {
                    list.pb(e);
                }
                // only add one copy of each self loop (self loops will be consecutive)
                else if (e->other(v) == v) {
                    if (selfLoops % 2 == 0) list.pb(e);
                    selfLoops++;
                }
            }
        }
        return list;
    }
} G(MAXN);

bool dest[MAXN];
int closest[MAXN], branch1[MAXN], branch2[MAXN], N, K;
ll furthest[MAXN], maxTime1[MAXN], maxTime2[MAXN], distTo[MAXN], totalTime;

bool dfsFind(int v, int prev) {
    bool connected = false;
    for (WeightedEdge *e: G.adjTo(v)) {
        int w = e->other(v);
        ll weight = e->getWeight();
        if (w == prev) continue;
        if (dfsFind(w, v)) {
            dest[v] = connected = true;
            totalTime += weight;
        }
    }
    if (dest[v]) connected = true;
    return connected;
}

ll dfsMaxBranches(int v, int prev, ll dist) {
    for (WeightedEdge *e: G.adjTo(v)) {
        int w = e->other(v);
        ll weight = e->getWeight();
        if (w == prev || !dest[w]) continue;
        ll curTime = dfsMaxBranches(w, v, weight + dist) + weight;
        if (curTime > maxTime1[v]) {
            maxTime2[v] = maxTime1[v];
            branch2[v] = branch1[v];
            maxTime1[v] = curTime;
            branch1[v] = w;
        } else if (curTime > maxTime2[v]) {
            maxTime2[v] = curTime;
            branch2[v] = w;
        }
    }
    return maxTime1[v];
}

void dfsFurthest(int v, int prev, ll dist) {
    furthest[v] = max(dist, maxTime1[v]);
    for (WeightedEdge *e: G.adjTo(v)) {
        int w = e->other(v);
        ll weight = e->getWeight();
        if (w == prev || !dest[w]) continue;
        if (w != branch1[v]) dfsFurthest(w, v, max(dist, maxTime1[v]) + weight);
        else dfsFurthest(w, v, max(dist, maxTime2[v]) + weight);
    }
}

void dfsDist(int v, int prev, ll dist, int closestDest) {
    distTo[v] = dist;
    closest[v] = closestDest;
    for (WeightedEdge *e: G.adjTo(v)) {
        int w = e->other(v);
        ll weight = e->getWeight();
        if (w == prev) continue;
        if (dest[w]) dfsDist(w, v, 0, w);
        else dfsDist(w, v, dist + weight, closestDest);
    }
}

int main() {
    ri(N);
    ri(K);
    for (int i = 0; i < N - 1; i++) {
        int a, b, c;
        ri(a);
        ri(b);
        ri(c);
        a--;
        b--;
        G.addEdge(new WeightedEdge(a, b, c));
    }
    int k = 0;
    for (int i = 0; i < K; i++) {
        ri(k);
        k--;
        dest[k] = true;
    }
    dfsFind(k, -1);
    int start = 0;
    for (int i = 0; i < N; i++) {
        if (dest[i]) {
            start = i;
            break;
        }
    }
    dfsMaxBranches(start, -1, 0);
    dfsFurthest(start, -1, 0);
    dfsDist(start, -1, 0, start);
    for (int i = 0; i < N; i++) {
        printf("%lld\n", distTo[i] + 2 * totalTime - furthest[closest[i]]);
    }
    return 0;
}
