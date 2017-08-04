/*
 * SSSP_BellmanFord.cpp
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

int N, M, u, v, w;
vector<DirectedWeightedEdge*> edges;

double *distTo;
bool *marked;

void bellmanFordSP(int s) {
    distTo = new double[N];
    for (int v = 0; v < N; v++) {
        distTo[v] = numeric_limits<double>::infinity();
    }
    distTo[s] = 0.0;
    for (int i = 0; i < N - 1; i++) {
        for (DirectedWeightedEdge *e : edges) {
            int v = e->from();
            int w = e->to();
            if (distTo[w] > distTo[v] + e->getWeight()) {
                distTo[w] = distTo[v] + e->getWeight();
            }
        }
    }

    for (DirectedWeightedEdge *e : edges) {
        if (distTo[e->to()] > distTo[e->from()] + e->getWeight()) throw runtime_error("Graph has a negative cycle.");
    }
}

int main() {
    ri(N);
    ri(M);
    for (int i = 0; i < M; i++) {
        ri(u);
        ri(v);
        ri(w);
        u--;
        v--;
        edges.pb(new DirectedWeightedEdge(u, v, w));
        edges.pb(new DirectedWeightedEdge(v, u, w));
    }
    bellmanFordSP(0);
    for (int i = 0; i < N; i++) {
        if (distTo[i] == D_INF) printf("-1\n");
        else printf("%d\n", (int) distTo[i]);
    }
    return 0;
}
