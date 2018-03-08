#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) ((x) << 1)
#define r(x) ((x) << 1 | 1)
#define m(x, y) ((x) + ((y) - (x)) / 2)
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rld(x) scanf("%Lf", &x)
#define rc(x) scanf(" %c", &x)
#define sc(x) do { scanf("%c", &x); } while (isspace(x))
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define set0(a) memset((a), 0, sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define Fill2(a, x, n, m) FOR(_, n) FOR(__, m) (a)[_][__] = (x)
#define Fill3(a, x, n, m, p) FOR(_, n) FOR(__, m) FOR(___, p) (a)[_][__][___] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))
#define sz(a) ((int) (a).size())
#define len(a) ((int) (a).length())

typedef long long ll;
typedef unsigned long long llu;
typedef long double ld;
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef map<ll, ll> mll;
typedef umap<int, int> umii;
typedef umap<int, ll> umill;
typedef umap<ll, int> umlli;
typedef umap<ll, ll> umll;
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

#define debug(fmt, x) fprintf(stderr, "%d::%s = " fmt, __LINE__, #x, (x)); fflush(stderr)
#define debug2(x) cerr << __LINE__ << "::" << #x << " = " << (x) << '\n' << flush
#define debugva(fmt, ...) fprintf(stderr, "%d::%s = " fmt, __LINE__, #__VA_ARGS__, __VA_ARGS__); fflush(stderr)
#define debugarr(fmt, x, a, b) fprintf(stderr, "%d::%s = {", __LINE__, #x); For(_, a, b) { if (_ != (a)) { fprintf(stderr, ", "); } fprintf(stderr, fmt, (x)[_]); } fprintf(stderr, "}\n"); fflush(stderr)
#define debugarr2(x, a, b) cerr << __LINE__ << "::" << #x << " = {"; For(_, a, b) { if (_ != (a)) { cerr << ", "; } cerr << (x)[_]; } cerr << "}\n" << flush

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

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
        if (a > b) return;
        update(array1, a, value);
        update(array1, b + 1, -value);
        update(array2, a, value * (a - 1));
        update(array2, b + 1, -value * b);
    }

    int getSize() {
        return size;
    }
};

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
        return (rsq(quad, ind) * ind * ind + rsq(lin, ind) * ind + rsq(con, ind)) / 2;
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
        if (a > b) return;
        int s = a - 1, len = b - a + 1;
        update(quad, a, value);
        update(quad, b + 1, -value);
        update(lin, a, value * (1 - 2 * s));
        update(lin, b + 1, -value * (1 - 2 * s));
        update(con, a, value * (s * s - s));
        update(con, b + 1, -value * (s * s - s));
        update(con, b + 1, value * len * (len + 1));
    }

    int getSize() {
        return size;
    }
};

#define MAXN 100010

int N, S, x, y, t, depth[MAXN], parent[MAXN], chain[MAXN], size[MAXN], head[MAXN], index[MAXN], vertex[MAXN], distTo[MAXN], chainNum, baseNum;
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
    index[v] = baseNum;
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

void updateUp(int a, int b, int t, bool includeB, int mult) {
    int curDist = mult == 1 ? dist(a, t) : 0;
    while (chain[a] != chain[b]) {
        curDist -= mult * (index[a] - index[head[chain[a]]]);
        printf("w %d %d %d\n", head[chain[a]], a, curDist);
        ft1->update(index[head[chain[a]]], index[a], curDist);
        ft2->update(index[head[chain[a]]] + 1, index[a], mult);
        a = parent[head[chain[a]]];
        curDist--;
    }
    if (includeB || a != b) {
        curDist -= mult * (index[a] - index[b]);
        printf("e %d %d %d\n", b, a, curDist);
        ft1->update(index[b] + !includeB, index[a], curDist);
        ft2->update(index[b] + 1, index[a], mult);
    }
}

void updatePath(int a, int b, int t) {
    int lcaAB = lca(a, b);
    int lcaAT = lca(a, t);
    int lcaBT = lca(b, t);
    updateUp(a, lcaAT, t, false, 1);
    FOR(j, N) printf("%lld ", ft1->rsq(index[j], index[j]) + ft2->rsq(index[j], index[j]));
    printf("\n");
    updateUp(t, lcaAT, t, true, -1);
    FOR(j, N) printf("%lld ", ft1->rsq(index[j], index[j]) + ft2->rsq(index[j], index[j]));
    printf("\n");
    updateUp(b, lcaBT, t, false, 1);
    FOR(j, N) printf("%lld ", ft1->rsq(index[j], index[j]) + ft2->rsq(index[j], index[j]));
    printf("\n");
    updateUp(t, lcaBT, t, true, -1);
    FOR(j, N) printf("%lld ", ft1->rsq(index[j], index[j]) + ft2->rsq(index[j], index[j]));
    printf("\n");
    if (dist(lcaAT, t) < dist(lcaBT, t)) {
        updateUp(t, lcaAT, t, false, 2);
        updateUp(lcaAT, lcaAT, t, true, 1);
    } else {
        updateUp(t, lcaBT, t, false, 2);
        updateUp(lcaBT, lcaBT, t, true, 1);
    }
    FOR(j, N) printf("%lld ", ft1->rsq(index[j], index[j]) + ft2->rsq(index[j], index[j]));
    printf("\n");
}

int main() {
    ri(N);
    ri(S);
    FOR(i, N - 1) {
        ri(x); x--;
        ri(y); y--;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    ft1 = new FenwickTreeRange<ll>(N);
    ft2 = new FenwickTreeQuadratic<ll>(N);
    lcaInit();
    bfs(0);
    int a, b, t;
    FOR(i, S) {
        ri(a); a--;
        ri(b); b--;
        ri(t); t--;
        updatePath(a, b, t);
        printf("---\n");
    }
    FOR(i, N) {
        printf("%lld ", ft1->rsq(index[i], index[i]) + ft2->rsq(index[i], index[i]));
    }
    printf("\n");
    return 0;
}
