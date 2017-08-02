/*
 * VMSS7WC16C3P2_Bfs.cpp
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

struct Graph {
private:
    int V;
    int E;
    vector<int>* adjList;

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
};

#define MAXN 2000

Graph *G;
int N, M, A, B, x, y;
bool hasPath, marked[MAXN];

void bfs(int s) {
    if (s == B) {
        hasPath = true;
        return;
    }
    queue<int> q;
    for (int v = 0; v < G->getV(); v++) {
        marked[v] = false;
    }
    marked[s] = true;
    q.push(s);

    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for (int w : G->adj(v)) {
            if (w == B) {
                hasPath = true;
                return;
            }
            if (marked[w]) continue;
            marked[w] = true;
            q.push(w);
        }
    }
}

int main() {
    ri(N);
    ri(M);
    ri(A);
    ri(B);
    A--;
    B--;
    G = new Graph(N);
    hasPath = false;
    for (int i = 0; i < M; i++) {
        ri(x);
        ri(y);
        x--;
        y--;
        G->addEdge(x, y);
    }
    bfs(A);
    if (hasPath) printf("GO SHAHIR!");
    else printf("NO SHAHIR!");
    return 0;
}
