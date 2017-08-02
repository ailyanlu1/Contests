/*
 * DMPG15G3.cpp
 *
 *  Created on: Jul 29, 2017
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

struct FenwickTree {
private:
    int size;
    int *array;

public:
    FenwickTree(int size) {
        this->size = size;
        array = new int[size + 1];
        for (int i = 0; i <= size; i++) {
            array[i] = 0;
        }
    }

    /**
     * Range Sum query from 1 to ind
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind index
     * @return sum
     */
    int rsq(int ind) {
        int sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    /**
     * Range Sum Query from a to b.
     * Search for the sum from array index from a to b
     * a and b are 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  a left index
     * @param  b right index
     * @return sum
     */
    int rsq(int a, int b) {
        return rsq(b) - rsq(a - 1);
    }

    /**
     * Update the array at ind and all the affected regions above ind.
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind   index
     * @param  value value
     */
    void update(int ind, int value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    int getSize() {
        return size;
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

    vector<int> &adj(int v) {
        return adjList[v];
    }

    int degree(int v) {
        return adjList[v].size();
    }
};

#define MAXN 200005

Graph *G;
FenwickTree *ft;
bool exclude[MAXN];
int N, Lk, Rk, Lc, Rc;
char bread[MAXN];
queue<int> q;
vector<pii> allStates;
vector<pii> curStates;
ll ans = 0;

int getSize(int v, int prev) {
    int size = 1;
    for (int w : G->adj(v)) {
        if (w != prev && !exclude[w]) size += getSize(w, v);
    }
    return size;
}

int getCentroid(int v, int prev, int treeSize) {
    int n = treeSize;
    int size = 1;
    bool hasCentroid = true;
    for (int w : G->adj(v)) {
        if (w == prev || exclude[w]) continue;
        int ret = getCentroid(w, v, treeSize);
        if (ret >= 0) return ret;
        hasCentroid &= -ret <= n / 2;
        size += -ret;
    }
    hasCentroid &= n - size <= n / 2;
    return hasCentroid ? v : -size;
}

void countPaths(int v, int prev, int C, int K) {
    bread[v] == 'C' ? C++ : K++;
    allStates.pb({C, K});
    curStates.pb({C, K});
    for (int w : G->adj(v)) {
        if (w != prev && !exclude[w]) countPaths(w, v, C, K);
    }
}

ll updateAll(vector<pii> &states, int adj) {
    int l = 0, r = 0;
    ll ret = 0;
    for (int i = 0; i < states.size(); i++) {
        while (l < i && states[i].f + states[l].f + adj < Lc) {
            ft->update(states[l++].s + 1, -1);
        }
        while (l > 0 && states[i].f + states[l - 1].f + adj >= Lc) {
            ft->update(states[--l].s + 1, 1);
        }
        while (r < i && states[i].f + states[r].f + adj <= Rc) {
            ft->update(states[r++].s + 1, 1);
        }
        while (r > 0 && states[i].f + states[r - 1].f + adj > Rc) {
            ft->update(states[--r].s + 1, -1);
        }
        ret += max(0, ft->rsq(Lk - states[i].s - (adj ^ 1) + 1, Rk - states[i].s - (adj ^ 1) + 1));
    }
    while (l > 0) {
        ft->update(states[--l].s + 1, 1);
    }
    while (r > 0) {
        ft->update(states[--r].s + 1, -1);
    }
    return ret;
}

int main() {
    ri(N);
    ri(Lk);
    ri(Rk);
    ri(Lc);
    ri(Rc);
    rs(bread);
    G = new Graph(N);
    ft = new FenwickTree(N);
    for (int i = 0, u, v; i < N - 1; i++) {
        ri(u);
        ri(v);
        G->addEdge(u - 1, v - 1);
    }
    q.push(0);
    while (!q.empty()) {
        allStates.clear();
        int v = q.front();
        q.pop();
        int c = getCentroid(v, -1, getSize(v, -1));
        exclude[c] = true;
        allStates.pb({0, 0});
        for (int w : G->adj(c)) {
            if (!exclude[w]) {
                curStates.clear();
                countPaths(w, c, 0, 0);
                sort(curStates.begin(), curStates.end());
                ans -= updateAll(curStates, bread[c] == 'C');
                q.push(w);
            }
        }
        sort(allStates.begin(), allStates.end());
        ans += updateAll(allStates, bread[c] == 'C');
        if (Lc <= (bread[c] == 'C') && (bread[c] == 'C') <= Rc && Lk <= (bread[c] == 'K') && (bread[c] == 'K') <= Rk) ans++;
    }
    printf("%lld\n", ans);
    return 0;
}
