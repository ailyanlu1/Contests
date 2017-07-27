/*
 * DMPG16G3.cpp
 *
 *  Created on: Jul 26, 2017
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

struct LazySegmentTree {
    struct Node {
        int val = 0, lazy = 0;
    };

private:
    vector<Node> tree;
    int N;
    int *array;

    void propogate(int cur) {
        if (tree[cur].lazy != 0) {
            tree[cur * 2].val += tree[cur].lazy;
            tree[cur * 2].lazy += tree[cur].lazy;
            tree[cur * 2 + 1].val += tree[cur].lazy;
            tree[cur * 2 + 1].lazy += tree[cur].lazy;
            tree[cur].lazy = 0;
        }
    }

    void build(int cur, int cL, int cR) {
        if (cL == cR) {
            tree[cur].val = array[cL];
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
        tree[cur].val = tree[cur * 2].val + tree[cur * 2 + 1].val;
    }

    void update(int cur, int cL, int cR, int l, int r, int val) {
        if (cL != cR) propogate(cur);
        if (cL > r || cR < l) return;
        if (cL >= l && cR <= r) {
            tree[cur].val = val;
            tree[cur].lazy += val;
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, l, r, val);
        update(cur * 2 + 1, m + 1, cR, l, r, val);
        tree[cur].val = tree[cur * 2].val + tree[cur * 2 + 1].val;
    }

    int query(int cur, int cL, int cR, int l, int r) {
        if (cL != cR) propogate(cur);
        if (cL > r || cR < l) return 0;
        if (cL >= l && cR <= r) return tree[cur].val;
        int m = cL + (cR - cL) / 2;
        int left = query(cur * 2, cL, m, l, r);
        int right = query(cur * 2 + 1, m + 1, cR, l, r);
        return left + right;
    }

public:
    LazySegmentTree(int size, int *arr, bool oneIndexed): tree((int) (2 * pow(2.0, ceil(log((double) size) / log(2.0))))) {
        array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = arr[i - !oneIndexed];
        }
        build(1, 1, size);
        N = size;
    }

    LazySegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log((double) size) / log(2.0))))) {
        array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = 0;
        }
        build(1, 1, size);
        N = size;
    }

    void update(int l, int r, int val) {
        update(1, 1, N, l, r, val);
    }

    int query(int l, int r) {
        return query(1, 1, N, l, r);
    }

    int size() {
        return N;
    }
};

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

    vector<int> adj(int v) {
        return adjList[v];
    }

    int degree(int v) {
        return adjList[v].size();
    }
};

class LCA {
private:
    int *depth, *parent, *chain, *size, *head, *base, *val;
    int chainNum, baseNum;
    LazySegmentTree *st;
    Graph *G;
    int n;

    void dfs(Graph *G, int v, int d, int prev) {
        depth[v] = d;
        parent[v] = prev;
        size[v] = 1;
        for (int w: G->adj(v)) {
            if (w != prev) {
                dfs(G, w, d + 1, v);
                size[v] += size[w];
            }
        }
    }

    void hld(Graph *G, int v, int prev) {
        if (head[chainNum] == -1) head[chainNum] = v;
        chain[v] = chainNum;
        base[v] = baseNum;
        val[baseNum] = size[v] - 1;
        baseNum++;
        int maxIndex = -1;
        for (int w: G->adj(v)) {
            if (w != prev && (maxIndex == -1 || size[maxIndex] < size[w])) maxIndex = w;
        }
        if (maxIndex != -1) hld(G, maxIndex, v);
        for (int w: G->adj(v)) {
            if (w != prev && w != maxIndex) {
                chainNum++;
                hld(G, w, v);
            }
        }
    }

    void updateUp(int v, int w) {
        while (chain[v] != chain[w]) {
            st->update(base[head[chain[v]]], base[v], 0);
            v = parent[head[chain[v]]];
        }
        if (v != w) st->update(base[w], base[v], 0);
    }

public:
    LCA(Graph *G) {
        depth = new int[G->getV()];
        parent = new int[G->getV()];
        chain = new int[G->getV()];
        size = new int[G->getV()];
        head = new int[G->getV()];
        base = new int[G->getV()];
        val = new int[G->getV() + 1];
        chainNum = 0;
        baseNum = 1;
        for (int i = 0; i < G->getV(); i++) {
            head[i] = -1;
        }
        dfs(G, 0, 0, -1);
        hld(G, 0, -1);
        st = new LazySegmentTree(G->getV(), val, true);
        n = G->getV();
        this->G = G;
    }

    /**
     * Returns the lowest common ancestor of vertex {@code v} and {@code w}.
     *
     * @param v the first vertex
     * @param w the first vertex
     * @return the lowest common ancestor of vertex {@code v} and {@code w}
     */
    int lca(int v, int w) {
        while (chain[v] != chain[w]) {
            if (depth[head[chain[v]]] < depth[head[chain[w]]]) w = parent[head[chain[w]]];
            else v = parent[head[chain[v]]];
        }
        if (depth[v] < depth[w]) return v;
        return w;
    }

    void update(int v, int w) {
        int u = lca(v, w);
        updateUp(v, u);
        updateUp(w, u);
    }

    int query(int v) {
        int below = st->query(base[v], base[v] + size[v] - 1);
        // TODO
        return 0;
    }
};

int N, Q, t, u, v;
Graph *G;
LCA * lca;

int main() {
    ri(N);
    G = new Graph(N);
    for (int i = 0; i < N - 1; i++) {
        ri(u);
        ri(v);
        G->addEdge(u - 1, v - 1);
    }
    lca = new LCA(G);
    ri(Q);
    for (int i = 0; i < Q; i++) {
        ri(t);
        if (t == 1) {
            ri(u);
            ri(v);
            lca->update(u - 1, v - 1);
        } else /*if (t == 2)*/ {
            ri(u);
            printf("%d\n", lca->query(u - 1));
        }
    }
    return 0;
}
