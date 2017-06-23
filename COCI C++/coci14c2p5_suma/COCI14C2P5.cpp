/*
 * COCI14C2P5.cpp
 *
 *  Created on: Jun 22, 2017
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

#define MAXN 700

struct WeightedUF {
private:
    int* parent;
    int count;

public:
    int* size;
    /**
     * Initializes an empty union–find data structure with {@code n} sites
     * {@code 0} through {@code n-1}. Each site is initially in its own
     * component.
     *
     * @param  n the number of sites
     */
    WeightedUF(int n) {
        count = n;
        parent = new int[n];
        size = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    /**
     * Returns the number of components.
     *
     * @return the number of components (between {@code 1} and {@code n})
     */
    int getCount() {
        return count;
    }


    /**
     * Returns the component identifier for the component containing site {@code p}.
     *
     * @param  p the integer representing one site
     * @return the component identifier for the component containing site {@code p}
     */
    int find(int p) {
        return p == parent[p] ? p : find(parent[p]);
    }

   /**
     * Returns true if the the two sites are in the same component.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     * @return {@code true} if the two sites {@code p} and {@code q} are in the same component;
     *         {@code false} otherwise
     */
    bool connected(int p, int q) {
        return find(p) == find(q);
    }

    /**
     * Returns the size of the component containing p
     *
     * @param p the integer representing one site
     * @return the size of the component containing p
     */
    int getSize(int p) {
        return size[find(p)];
    }

    /**
     * Merges the component containing site {@code p} with the
     * the component containing site {@code q}.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     */
    pair<int, bool> join(int rootP, int rootQ) {
        if (rootP == rootQ) return mp(size[rootP], false);
        count--;
        // make smaller root point to larger one
        if (size[rootP] < size[rootQ]) {
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
            return mp(size[rootQ], true);
        }
        else {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
            return mp(size[rootP], true);
        }
    }

    /**
     * Unmerges the component containing site {@code p} with the
     * the component containing site {@code q}.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     */
    void disjoin(int rootP, int rootQ) {
        if (size[rootP] < size[rootQ]) {
            parent[rootP] = rootP;
            size[rootQ] -= size[rootP];
        }
        else {
            parent[rootQ] = rootQ;
            size[rootP] -= size[rootQ];
        }
        count++;
    }
} uf(MAXN * MAXN);

struct Event {
    int p, q, h, v;
};

bool EventCmp(const Event &a, const Event &b) {
    return (ll) a.h * b.v < (ll) b.h * a.v;
}

int N, H[MAXN][MAXN], V[MAXN][MAXN];
vector<Event> events;
stack<pii> changes;
const int moves[2][2] = {{0, 1}, {1, 0}};

int toPoint(int i, int j) {
    return i * N + j;
}

int getI(int point) {
    return point / N;
}

int getJ(int point) {
    return point % N;
}

void processAdj(int i1, int j1, int i2, int j2) {
    if (i1 < 0 || i1 >= N || j1 < 0 || j1 >= N ||
            i2 < 0 || i2 >= N || j2 < 0 || j2 >= N) return;
    int dH = H[i1][j1] - H[i2][j2];
    int dV = V[i2][j2] - V[i1][j1];
    if (dV == 0 && dH == 0) {
        int p = toPoint(i1, j1);
        int q = toPoint(i2, j2);
        uf.join(uf.find(p), uf.find(q));
    } else if (dV != 0){
        if (dV < 0) {
            dH = -dH;
            dV = -dV;
        }
        if (dH >= 0) events.pb({toPoint(i1, j1), toPoint(i2, j2), dH, dV});
    }
}

int main() {
    ri(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ri(H[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ri(V[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 2; k++) {
                processAdj(i, j, i + moves[k][0], j + moves[k][1]);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < N * N; i++) {
        ans = max(ans, uf.size[i]);
    }
    sort(events.begin(), events.end(), EventCmp);
    for (int i = 0; i < events.size(); i++) {
        Event e = events[i];
        int rootP = uf.find(e.p);
        int rootQ = uf.find(e.q);
        pair<int, bool> res = uf.join(uf.find(e.p), uf.find(e.q));
        ans = max(ans, res.f);
        if (res.s) changes.push({rootP, rootQ});
        if (i == events.size() || EventCmp(e, events[i + 1])) {
            while (!changes.empty()) {
                uf.disjoin(changes.top().f, changes.top().s);
                changes.pop();
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
