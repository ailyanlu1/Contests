/*
 * GFSSOC1J5.cpp
 *
 *  Created on: Jul 3, 2017
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

struct Digraph {
private:
    int V;
    int E;
    vector<int>* adjList;
    int *indegreeArr;

public:
    Digraph(int V) {
        this->V = V;
        this->E = 0;
        adjList = new vector<int>[V];
        indegreeArr = new int[V];
    }

    int getV() {
        return this->V;
    }

    int getE() {
        return this->E;
    }

    void addEdge(int v, int w) {
        adjList[v].push_back(w);
        indegreeArr[w]++;
        E++;
    }

    vector<int> &adj(int v) {
        return adjList[v];
    }

    int outdegree(int v) {
        return adjList[v].size();
    }

    int indegree(int v) {
        return indegreeArr[v];
    }
};

#define MAXN 1000

Digraph *G;
bool marked[MAXN];
int N, M, T, Q, a, b, distTo[MAXN][MAXN];

void bfs(int s) {
    queue<int> q;
    for (int v = 0; v < G->getV(); v++) {
        marked[v] = false;
        distTo[s][v] = INT_MAX;
    }
    distTo[s][s] = 0;
    marked[s] = true;
    q.push(s);

    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for (int w : G->adj(v)) {
            if (marked[w]) continue;
            distTo[s][w] = distTo[s][v] + T;
            marked[w] = true;
            q.push(w);
        }
    }
}

int main() {
    ri(N);
    ri(M);
    ri(T);
    G = new Digraph(N);
    for (int i = 0; i < M; i++) {
        ri(a);
        ri(b);
        a--;
        b--;
        G->addEdge(a, b);
    }
    for (int i = 0; i < N; i++) {
        bfs(i);
    }
    ri(Q);
    for (int i = 0; i < Q; i++) {
        ri(a);
        ri(b);
        a--;
        b--;
        int ans = distTo[a][b];
        if (ans == INT_MAX) printf("Not enough hallways!\n");
        else printf("%d\n", distTo[a][b]);
    }
    return 0;
}
