/*
 * UTSO15P4.cpp
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

struct DirectedWeightedEdge {
public:
    int from, to;
    int x, y;

    DirectedWeightedEdge(int v, int w, int x, int y) {
        this->from = v;
        this->to = w;
        this->x = x;
        this->y = y;
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
        int v = e->from;
        int w = e->to;
        adjList[v].push_back(e);
        indegreeArr[w]++;
        E++;
    }

    vector<DirectedWeightedEdge*> adj(int v) {
        return adjList[v];
    }

    int outdegree(int v) {
        return adjList[v].size();
    }

    int indegree(int v) {
        return indegreeArr[v];
    }

    vector<DirectedWeightedEdge*> edges() {
        vector<DirectedWeightedEdge*> list;
        for (int v = 0; v < V; v++) {
            for (DirectedWeightedEdge *e : adj(v)) {
                list.push_back(e);
            }
        }
        return list;
    }
} *G;

#define MAX 2000

int N, M, T;
// prob[t][n] = probability of reaching station n at time t
double prob[MAX + 1][MAX];

int main() {
    ri(N);
    ri(M);
    ri(T);
    G = new WeightedDigraph(N);
    for (int i = 0; i < M; i++) {
        int a, b, x, y;
        ri(a);
        ri(b);
        ri(x);
        ri(y);
        if (a == N) continue;
        a--;
        b--;
        G->addEdge(new DirectedWeightedEdge(a, b, x, y));
    }
    prob[0][0] = 1.0;
    prob[1][0] = -1.0;
    for (int i = 0; i < T; i++) {
        for (int j = 0; j < N; j++) {
            for (DirectedWeightedEdge *e: G->adj(j)) {
                double buf = prob[i][j] / G->outdegree(j) / (e->y - e->x + 1);
                if (e->x + i <= T) {
                    prob[e->x + i][e->to] += buf;
                    if (e->y + i < T) {
                        prob[e->y + i + 1][e->to] -= buf;
                    }
                }
            }
            prob[i + 1][j] += prob[i][j];
        }
    }
    double num = 0, den = 0;
    for (int i = 0; i <= T; i++) {
        num += prob[i][N - 1] * i;
        den += prob[i][N - 1];
    }
    printf("%.6f", num / den);
    return 0;
}
