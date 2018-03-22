#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define f first
#define s second
#define all(a) (a).begin(), (a).end()
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pill pair<int, ll>
#define plli pair<ll, int>
#define pdd pair<double, double>
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

/**
 * FenwickTree supporting range updates and range queries.
 * Memory usage:  O(2n)
 */
template <typename T>
struct FenwickTreeRange {
private:
    int size;
    vector<T> array1, array2;

    T rsq(vector<T> &array, int ind) {
        T sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    void update(vector<T> &array, int ind, T value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

public:
    FenwickTreeRange(int size) : array1(size + 1), array2(size + 1) {
        this->size = size;
    }

    /**
     * Range Sum query at index ind
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind index
     * @return sum
     */
    T rsq(int ind) {
        return rsq(array1, ind) * ind - rsq(array2, ind);
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
    T rsq(int a, int b) {
        return rsq(b) - rsq(a - 1);
    }

    /**
     * Update the array between index a and b
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  a left index
     * @param  b right index
     * @param  value value
     */
    void update(int a, int b, T value) {
        update(array1, a, value);
        update(array1, b + 1, -value);
        update(array2, a, value * ((T) a - 1));
        update(array2, b + 1, -value * (T) b);
    }

    int getSize() {
        return size;
    }
};

/**
 * FenwickTree supporting range updates with updates in the form of
 * adding v, 2v, 3v, ... to the interval [l, r], and range queries.
 * Memory usage:  O(3n)
 */
template <typename T>
struct FenwickTreeQuadratic {
private:
    int size;
    // constant, linear, quadratic
    vector<T> con, lin, quad;

    T rsq(vector<T> &array, int ind) {
        T sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    void update(vector<T> &array, int ind, T value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

public:
    FenwickTreeQuadratic(int size) : con(size + 1), lin(size + 1), quad(size + 1) {
        this->size = size;
    }

    /**
     * Range Sum query at index ind
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind index
     * @return sum
     */
    T rsq(int ind) {
        return (rsq(quad, ind) * (T) ind * (T) ind + rsq(lin, ind) * (T) ind + rsq(con, ind)) / (T) 2;
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
    T rsq(int a, int b) {
        return rsq(b) - rsq(a - 1);
    }

    /**
     * Update the array between index a and b with values v, 2v, 3v, ...
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  a left index
     * @param  b right index
     * @param  value value
     */
    void update(int a, int b, T value) {
        int s = a - 1, len = b - a + 1;
        update(quad, a, value);
        update(quad, b + 1, -value);
        update(lin, a, value * ((T) 1 - (T) 2 * (T) s));
        update(lin, b + 1, -value * ((T) 1 - (T) 2 * (T) s));
        update(con, a, value * ((T) s * (T) s - (T) s));
        update(con, b + 1, -value * (((T) s * (T) s - (T) s)));
        update(con, b + 1, value * ((T) len * (T) (len + 1)));
    }

    int getSize() {
        return size;
    }
};

#define MAXN 100010

int N, S, x, y, t, depth[MAXN], parent[MAXN], chain[MAXN], size[MAXN], head[MAXN], ind[MAXN], vertex[MAXN], distTo[MAXN], chainNum, baseNum;
vector<int> adj[MAXN];
FenwickTreeRange<ll> *ft1;
FenwickTreeQuadratic<ll> *ft2;

void bfs(int s) {
    queue<int> q;
    bool marked[N];
    for (int v = 0; v < N; v++) {
        marked[v] = false;
        distTo[v] = INT_MAX;
    }
    distTo[s] = 0;
    marked[s] = true;
    q.push(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int w : adj[v]) {
            if (!marked[w]) {
                distTo[w] = distTo[v] + 1;
                marked[w] = true;
                q.push(w);
            }
        }
    }
}

void dfs(int v, int d, int prev) {
    depth[v] = d;
    parent[v] = prev;
    size[v] = 1;
    for (int w: adj[v]) {
        if (w != prev) {
            dfs(w, d + 1, v);
            size[v] += size[w];
        }
    }
}

void hld(int v, int prev) {
    if (head[chainNum] == -1) head[chainNum] = v;
    chain[v] = chainNum;
    ind[v] = baseNum;
    vertex[baseNum++] = v;
    int maxIndex = -1;
    for (int w: adj[v]) {
        if (w != prev && (maxIndex == -1 || size[maxIndex] < size[w])) maxIndex = w;
    }
    if (maxIndex != -1) hld(maxIndex, v);
    for (int w: adj[v]) {
        if (w != prev && w != maxIndex) {
            chainNum++;
            hld(w, v);
        }
    }
}

void lcaInit() {
    chainNum = 0;
    baseNum = 1;
    for (int i = 0; i < N; i++) {
        head[i] = -1;
    }
    dfs(0, 0, -1);
    hld(0, -1);
}

int lca(int v, int w) {
    while (chain[v] != chain[w]) {
        if (depth[head[chain[v]]] < depth[head[chain[w]]]) w = parent[head[chain[w]]];
        else v = parent[head[chain[v]]];
    }
    if (depth[v] < depth[w]) return v;
    return w;
}

int dist(int s, int t) {
    return distTo[s] + distTo[t] - 2 * distTo[lca(s, t)];
}

void updateUp(int a, int b, bool includeB, int con, int lin) {
    while (chain[a] != chain[b]) {
        con += lin * (ind[a] - ind[head[chain[a]]] + 1);
        ft1->update(ind[head[chain[a]]], ind[a], con);
        ft2->update(ind[head[chain[a]]], ind[a], -lin);
        a = parent[head[chain[a]]];
    }
    if (includeB || a != b) {
        con += lin * (ind[a] - (ind[b] + !includeB) + 1);
        ft1->update(ind[b] + !includeB, ind[a], con);
        ft2->update(ind[b] + !includeB, ind[a], -lin);
    }
}

void updatePath(int a, int b, int t) {
    int lcaAB = lca(a, b);
    if (a == b) {
        updateUp(a, a, true, dist(a, t), 1);
    } else if (lcaAB == a || lcaAB == b) {
        if (lcaAB == b) swap(a, b);
        if (lca(a, t) != a) {
            updateUp(b, a, true, dist(b, t), -1);
        } else {
            int lcaBT = lca(b, t);
            updateUp(b, lcaBT, false, dist(b, t), -1);
            updateUp(lcaBT, a, true, dist(lcaBT, t), 1);
        }
    } else if (lca(lcaAB, t) != lcaAB) {
        updateUp(a, lcaAB, true, dist(a, t), -1);
        updateUp(b, lcaAB, false, dist(b, t), -1);
    } else if (lca(a, t) == lcaAB) {
        updateUp(a, lcaAB, true, dist(a, t), -1);
        int lcaBT = lca(b, t);
        updateUp(b, lcaBT, false, dist(b, t), -1);
        updateUp(lcaBT, lcaAB, false, dist(lcaBT, t), 1);
    } else {
        updateUp(b, lcaAB, true, dist(b, t), -1);
        int lcaAT = lca(a, t);
        updateUp(a, lcaAT, false, dist(a, t), -1);
        updateUp(lcaAT, lcaAB, false, dist(lcaAT, t), 1);
    }
}

int main() {
    cin >> N >> S;
    FOR(i, N - 1) {
        cin >> x >> y;
        x--; y--;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    ft1 = new FenwickTreeRange<ll>(N);
    ft2 = new FenwickTreeQuadratic<ll>(N);
    lcaInit();
    bfs(0);
    int a, b, t;
    FOR(i, S) {
        cin >> a >> b >> t;
        a--; b--; t--;
        updatePath(a, b, t);
    }
    FOR(i, N) {
        cout << ft1->rsq(ind[i], ind[i]) + ft2->rsq(ind[i], ind[i]) << sp;
    }
    cout << nl;
    return 0;
}
