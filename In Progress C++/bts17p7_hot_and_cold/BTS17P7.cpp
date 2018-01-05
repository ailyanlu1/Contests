#include <bits/stdc++.h>

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
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define FILL(a, x) memset((a), (x), sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x);
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<int, float> pif;
typedef pair<float, int> pfi;
typedef pair<double, double> pdd;
typedef pair<int, double> pid;
typedef pair<double, int> pdi;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef pair<llu, llu> pllu;
typedef pair<int, llu> pillu;
typedef pair<llu, int> pllui;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXN 100010

struct FenwickTreeRangePoint {
private:
    int size;
    ll *array;

public:
    FenwickTreeRangePoint(int size) {
        this->size = size;
        array = new ll[size + 1];
        for (int i = 0; i <= size; i++) {
            array[i] = 0LL;
        }
    }

    /**
     * Value at index {@code ind}.
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind index
     * @return sum
     */
    ll getValue(int ind) {
        int sum = 0LL;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
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
    void update(int ind, ll value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    /**
     * Update the array between a and b.
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  a left index
     * @param  b right index
     * @param  value value
     */
    void update(int a, int b, ll value) {
        update(a, value);
        update(b + 1, -value);
    }

    int getSize() {
        return size;
    }
};

struct Query {
    int a, b, t;
};

bool zero = true;
int N, S, x, y, t, depth[MAXN], parent[MAXN], chain[MAXN], size[MAXN], head[MAXN], base[MAXN], vertex[MAXN], distTo[MAXN], chainNum, baseNum;
ll sum[MAXN];
Query Q[MAXN];
vector<int> adj[MAXN];
FenwickTreeRangePoint *ft;

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
    base[v] = baseNum;
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

void updateUp(int v, int w, int t, bool includeW) {
    while (chain[v] != chain[w]) {
        if (zero) {
            ft->update(base[head[chain[v]]], base[v], 1);
        } else {
            For(i, base[head[chain[v]]], base[v] + 1) {
                sum[vertex[i]] += (ll) dist(t, vertex[i]);
            }
        }
        v = parent[head[chain[v]]];
    }
    if (includeW || v != w) {
        if (zero) {
            ft->update(base[w] + !includeW, base[v], 1);
        } else {
            For(i, base[w] + !includeW, base[v] + 1) {
               sum[vertex[i]] += (ll) dist(t, vertex[i]);
            }
        }
    }
}

void updatePath(int v, int w, int t) {
    int lcaVertex = lca(v, w);
    updateUp(v, lcaVertex, t, false);
    updateUp(w, lcaVertex, t, true);
}

int main() {
    ri(N);
    ri(S);
    FOR(i, N) {
        sum[i] = 0LL;
    }
    FOR(i, N - 1) {
        ri(x); x--;
        ri(y); y--;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    lcaInit();
    bfs(0);
    FOR(i, S) {
        ri(Q[i].a); Q[i].a--;
        ri(Q[i].b); Q[i].b--;
        ri(Q[i].t); Q[i].t--;
        if (Q[i].t != 0) zero = false;
    }
    if (zero) ft = new FenwickTreeRangePoint(N);
    FOR(i, S) {
        updatePath(Q[i].a, Q[i].b, Q[i].t);
    }
    FOR(i, N) {
        if (zero) printf("%lld ", ft->getValue(base[i]) * (ll) distTo[i]);
        else printf("%lld ", sum[i]);
    }
    printf("\n");
    return 0;
}
