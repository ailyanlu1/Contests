/*
 * IOI12P2.cpp
 *
 *  Created on: Jul 25, 2017
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

struct WeightedUF {
private:
    int* parent;
    int* size;
    int count;

public:
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
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];    // path compression by halving
            p = parent[p];
        }
        return p;
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
    void join(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return;

        // make smaller root point to larger one
        if (size[rootP] < size[rootQ]) {
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
        }
        else {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }
        count--;
    }

    /**
     * Unmerges the component containing site {@code p} with the
     * the component containing site {@code q}.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     */
    void disjoin(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
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
} *uf;

#define MAXN 1000000

int state = 0, ans1 = 0, ans2 = 0, n;
vector<int> adj[MAXN];

struct UF {
private:
    int* parent;
    int* degree;
    char* rank; // equivalent to byte
    int count;
    int n;
    int skip = -1;

public:
    bool isCritical = true;
    /**
     * Initializes an empty union–find data structure with {@code n} sites
     * {@code 0} through {@code n-1}. Each site is initially in its own
     * component.
     *
     * @param  n the number of sites
     */
    UF(int n) {
        count = n;
        this->n = n;
        parent = new int[n];
        degree = new int[n];
        rank = new char[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            degree[i] = 0;
            rank[i] = 0;
        }
    }

    void rebuild(int skip) {
        this->skip = skip;
        isCritical = true;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
        for (int v = 0; v < n; v++) {
            for (int w : adj[v]) {
                if (v < w) join(v, w);
            }
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
     * Returns the number of components.
     *
     * @return the number of components (between {@code 1} and {@code n})
     */
    int getCount() {
        return count;
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
     * Returns the rank by size of the component containing p
     *
     * @param p the integer representing one site
     * @return the rank by size of the component containing p
     */
    int getRank(int p) {
        return (int) rank[find(p)];
    }

    /**
     * Merges the component containing site {@code p} with the
     * the component containing site {@code q}.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     */
    void join(int p, int q) {
        if (!isCritical) return;
        if (p == skip || q == skip) return;
        degree[p]++;
        degree[q]++;
        if (degree[p] > 2 || degree[q] > 2) {
            isCritical = false;
            return;
        }
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) {
            isCritical = false;
            return;
        }

        // make root of smaller rank point to root of larger rank
        if      (rank[rootP] < rank[rootQ]) parent[rootP] = rootQ;
        else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootP;
        else {
            parent[rootQ] = rootP;
            rank[rootP]++;
        }
        count--;
    }
} *ufCycle[4];

void Init(int N) {
    n = N;
    uf = new WeightedUF(N);
    for (int i = 0; i < 4; i++) {
        ufCycle[i] = new UF(N);
    }
}

void Link(int A, int B) {
    if (state == 1) {
        for (int i = 0; i < 4; i++) {
            ufCycle[i]->join(A, B);
        }
        return;
    } else if (state == 3) {
        return;
    }
    adj[A].pb(B);
    adj[B].pb(A);
    if (adj[A].size() < adj[B].size()) swap(A, B);
    if (adj[A].size() > 2) {
        state = 1;
        for (int i = 0; i < 3; i++) {
            ufCycle[i]->rebuild(adj[A][i]);
        }
        ufCycle[3]->rebuild(A);
        return;
    }
    if (uf->connected(A, B)) {
        if (state == 0) {
            state = 2;
            ans2 = uf->getSize(A);
            return;
        } else if (state == 2) {
            state = 3;
            return;
        }
    }
    uf->join(A, B);
}

int CountCritical() {
    if (state == 0) {
        return n;
    } else if (state == 1) {
        ans1 = 0;
        for (int i = 0; i < 4; i++) {
            if (ufCycle[i]->isCritical) ans1++;
        }
        return ans1;
    } else if (state == 2) {
        return ans2;
    } else /*if (state == 3)*/ {
        return 0;
    }
}

int main() {
    int N, L, A, B;
    ri(N);
    ri(L);
    Init(N);
    for (int i = 0; i < L; i++) {
        ri(A);
        if (A == -1) {
            printf("%d\n", CountCritical());
        } else {
            ri(B);
            Link(A, B);
        }
    }
    return 0;
}
