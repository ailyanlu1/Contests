/*
 * IOI16P2.cpp
 *
 *  Created on: Jun 19, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

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

struct UF {
private:
    int* parent;
    int* rank;

public:
    /**
     * Initializes an empty union–find data structure with {@code n} sites
     * {@code 0} through {@code n-1}. Each site is initially in its own
     * component.
     *
     * @param  n the number of sites
     */
    UF(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    /**
     * Returns the component identifier for the component containing site {@code p}.
     *
     * @param  p the integer representing one site
     * @return the component identifier for the component containing site {@code p}
     */
    int find(int p) {
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];    // path compression by halving
            p = parent[p];
        }
        return p;
    }

    /**
     * Merges the component containing site {@code p} with the
     * the component containing site {@code q}.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     */
    bool join(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return false;

        // make root of smaller rank point to root of larger rank
        if      (rank[rootP] < rank[rootQ]) parent[rootP] = rootQ;
        else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootP;
        else {
            parent[rootQ] = rootP;
            rank[rootP]++;
        }
        return true;
    }
};

struct Edge {
    int from, to, weight;
    Edge(int f, int t, int w) {
        from = f;
        to = t;
        weight = w;
    }

    bool operator < (const Edge &e) {
        return weight < e.weight;
    }
};

#define MAXN 200000

vector<int> all;
int dist[2 * MAXN];

ll plan_roller_coaster(int n, int s[], int t[]) {
    for (int i = 0; i < n; i++) {
        all.pb(s[i]);
        all.pb(t[i]);
    }
    sort(all.begin(), all.end());
    all.resize(unique(all.begin(), all.end()) - all.begin());
    UF uf(all.size());
    for (int i = 0; i < n; i++) {
        s[i] = lower_bound(all.begin(), all.end(), s[i]) - all.begin();
        t[i] = lower_bound(all.begin(), all.end(), t[i]) - all.begin();
        dist[s[i]]++;
        dist[t[i]]--;
        uf.join(s[i], t[i]);
    }
    int cur = 1;
    ll ans = 0;
    vector<Edge> edges;
    for (int i = all.size() - 1; i >= 1; i--) {
        cur += dist[i];
        if (cur < 0) {
            ans -= (ll) cur * (all[i] - all[i - 1]);
            dist[i - 1] += cur;
            uf.join(i - 1, i);
            cur = 0;
        }
        if (cur > 0) {
            uf.join(i, i - 1);
        } else if (cur == 0) {
            edges.pb(Edge(i, i - 1, all[i] - all[i - 1]));
        }
    }
    sort(edges.begin(), edges.end());
    for (Edge e: edges) {
        if (uf.join(e.from, e.to)) ans += e.weight;
    }
    return ans;
}

int main() {
    int n = 4;
    int s[] = {1, 4, 5, 6};
    int t[] = {7, 3, 8, 6};
    printf("%lld", plan_roller_coaster(n, s, t));
    return 0;
}
