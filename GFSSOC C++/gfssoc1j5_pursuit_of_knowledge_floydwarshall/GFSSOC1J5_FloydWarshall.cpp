/*
 * GFSSOC1J5_FloydWarshall.cpp
 *
 *  Created on: Jul 3, 2017
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

#define MAXN 1000

int V, M, T, Q, a, b;
int adj[MAXN][MAXN];
int distTo[MAXN][MAXN];

void floydWarshallAPSP() {
    // initialize distances to infinity
    for (int v = 0; v < V; v++) {
        for (int w = 0; w < V; w++) {
            distTo[v][w] = INT_INF;
        }
    }

    // initialize distances using edge-weighted digraph's
    for (int v = 0; v < V; v++) {
        for (int w = 0; w < V; w++) {
            if (adj[v][w] == 0) continue;
            distTo[v][w] = adj[v][w];
        }
        // in case of self-loops
        if (distTo[v][v] >= 0) {
            distTo[v][v] = 0;
        }
    }

    // Floyd-Warshall updates
    for (int i = 0; i < V; i++) {
        // compute shortest paths using only 0, 1, ..., i as intermediate vertices
        for (int v = 0; v < V; v++) {
            if (distTo[v][i] == 0) continue;  // optimization
            for (int w = 0; w < V; w++) {
                if (distTo[v][w] > distTo[v][i] + distTo[i][w]) {
                    distTo[v][w] = distTo[v][i] + distTo[i][w];
                }
            }
            // check for negative cycle
            if (distTo[v][v] < 0) throw runtime_error("Graph has a negative cycle.");
        }
    }
}

int main() {
    ri(V);
    ri(M);
    ri(T);
    for (int i = 0; i < M; i++) {
        ri(a);
        ri(b);
        a--;
        b--;
        adj[a][b] = T;
    }
    floydWarshallAPSP();
    ri(Q);
    for (int i = 0; i < Q; i++) {
        ri(a);
        ri(b);
        a--;
        b--;
        int ans = distTo[a][b];
        if (ans == INT_INF) printf("Not enough hallways!\n");
        else printf("%d\n", distTo[a][b]);
    }
    return 0;
}
