/*
 * COCI15C4P5.cpp
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

#define MAXN 100000

int N, P[MAXN - 1], path[MAXN];
map<int, vector<int>> M[MAXN];
ll cur, ans[MAXN];

struct WeightedEdge {
private:
    int v, w;
    double weight;

public:
    WeightedEdge(int v, int w, double weight) {
        this->v = v;
        this->w = w;
        this->weight = weight;
    }

    double getWeight() {
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

    bool operator == (const WeightedEdge &e) {
        return (v == e.v && w == e.w && weight == e.weight);
    }

    bool operator != (const WeightedEdge &e) {
        return !(v == e.v && w == e.w && weight == e.weight);
    }

    bool operator < (const WeightedEdge &e) {
        return (weight < e.weight);
    }

    bool operator <= (const WeightedEdge &e) {
        return (weight <= e.weight);
    }

    bool operator > (const WeightedEdge &e) {
        return (weight > e.weight);
    }

    bool operator >= (const WeightedEdge &e) {
        return (weight > e.weight);
    }
} *edges[MAXN - 1];

struct UF {
private:
    int* parent;
    int* size;

public:

    UF(int n) {
        parent = new int[n];
        size = new int[n];
        for (int i = 0; i < n; i++) {
            M[i][0].pb(i);
            parent[i] = i;
            size[i] = 1;
        }
    }

    void join(int a, int b, int c) {
        if (size[parent[a]] < size[parent[b]]) swap(a, b);
        int pA = parent[a];
        int pB = parent[b];
        for (auto it: M[pB]) {
            for (int i: it.second) {
                cur += M[pA][path[a] ^ c ^ path[b] ^ path[i]].size();
            }
        }
        int old = path[b];
        for (auto it: M[pB]) {
            for (int i: it.second) {
                path[i] = path[i] ^ old ^ c ^ path[a];
                parent[i] = pA;
                M[pA][path[i]].pb(i);
            }
        }
        size[pA] += size[pB];
        M[pB].clear();
        size[pB] = 0;
    }
};

int main() {
    ri(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b, z;
        ri(a);
        ri(b);
        ri(z);
        a--;
        b--;
        edges[i] = new WeightedEdge(a, b, z);
    }
    for (int i = 0; i < N - 1; i++) {
        ri(P[i]);
        P[i]--;
    }
    UF uf(N);
    for (int i = N - 2; i >= 0; i--) {
        WeightedEdge* e = edges[P[i]];
        uf.join(e->either(), e->other(e->either()), e->getWeight());
        ans[i] = cur;
    }
    ans[N - 1] = 0;
    for (int i = 0; i < N; i++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}
