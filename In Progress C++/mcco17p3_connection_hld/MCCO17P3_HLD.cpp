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

#define MAXN 150005

int N, D, Q, UF[MAXN], DEP[MAXN], PAR[MAXN], CHAIN[MAXN], SZ[MAXN], HEAD[MAXN], IND[MAXN], VERT[MAXN], chainNum, curInd;
char RNK[MAXN];
vector<int> adj[MAXN];
vector<pair<int, pii>> updates;

struct LazySegmentTree {
private:
    static const int vdef = INT_INF, ldef = INT_INF, qdef = 0;

    static int merge(int l, int r) {
        return max(l, r);
    }

    static int apply(int x, int v) {
        return min(x, v);
    }

    static int getSegmentVal(int x, int len) {
        return x;
    }

    struct Node {
        int val = LazySegmentTree::vdef, lazy = LazySegmentTree::ldef;
    };

    vector<Node> tree;
    int N;
    int *array;

    void propagate(int cur, int cL, int cR) {
        if (tree[cur].lazy != ldef) {
            int m = cL + (cR - cL) / 2;
            tree[cur * 2].val = apply(tree[cur * 2].val, getSegmentVal(tree[cur].lazy, m - cL + 1));
            tree[cur * 2].lazy = apply(tree[cur * 2].lazy, tree[cur].lazy);
            tree[cur * 2 + 1].val = apply(tree[cur * 2 + 1].val, getSegmentVal(tree[cur].lazy, cR - m));
            tree[cur * 2 + 1].lazy = apply(tree[cur * 2 + 1].lazy, tree[cur].lazy);
            tree[cur].lazy = ldef;
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
        tree[cur].val = merge(tree[cur * 2].val, tree[cur * 2 + 1].val);
    }

    void update(int cur, int cL, int cR, int l, int r, int val) {
        if (cL != cR) propagate(cur, cL, cR);
        if (cL > r || cR < l) return;
        if (cL >= l && cR <= r) {
            tree[cur].val = apply(tree[cur].val, getSegmentVal(val, cR - cL + 1));
            tree[cur].lazy = apply(tree[cur].lazy, val);
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, l, r, val);
        update(cur * 2 + 1, m + 1, cR, l, r, val);
        tree[cur].val = merge(tree[cur * 2].val, tree[cur * 2 + 1].val);
    }

    int query(int cur, int cL, int cR, int l, int r) {
        if (cL != cR) propagate(cur, cL, cR);
        if (cL > r || cR < l) return qdef;
        if (cL >= l && cR <= r) return tree[cur].val;
        int m = cL + (cR - cL) / 2;
        int left = query(cur * 2, cL, m, l, r);
        int right = query(cur * 2 + 1, m + 1, cR, l, r);
        return merge(left, right);
    }

public:
    LazySegmentTree(int size, int *arr, bool oneIndexed): tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = arr[i - !oneIndexed];
        }
        build(1, 1, size);
        N = size;
    }

    LazySegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = vdef;
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
} *st;

void dfs(int v, int d, int prev) {
    DEP[v] = d;
    PAR[v] = prev;
    SZ[v] = 1;
    for (int w : adj[v]) {
        if (w == prev) continue;
        dfs(w, d + 1, v);
        SZ[v] += SZ[w];
    }
}

void hld(int v, int prev) {
    if (HEAD[chainNum] == -1) HEAD[chainNum] = v;
    CHAIN[v] = chainNum;
    IND[v] = curInd;
    VERT[curInd++] = v;
    int maxInd = -1;
    for (int w : adj[v]) {
        if (w != prev && (maxInd == -1 || SZ[maxInd] < SZ[w])) maxInd = w;
    }
    if (maxInd != -1) hld(maxInd, v);
    for (int w : adj[v]) {
        if (w == prev || w == maxInd) continue;
        chainNum++;
        hld(w, v);
    }
}

void initHLD() {
    chainNum = 0;
    curInd = 1;
    FOR(i, N) PAR[i] = HEAD[i] = -1;
    FOR(i, N) {
        if (PAR[i] != -1) continue;
        dfs(i, 0, -1);
        hld(i, -1);
    }
    st = new LazySegmentTree(N);
}

int lca(int v, int w) {
    while (CHAIN[v] != CHAIN[w]) {
        if (DEP[HEAD[CHAIN[v]]] < DEP[HEAD[CHAIN[w]]]) w = PAR[HEAD[CHAIN[w]]];
        else v = PAR[HEAD[CHAIN[v]]];
    }
    return DEP[v] < DEP[w] ? v : w;
}

void updateUp(int v, int w, int val) {
    while (CHAIN[v] != CHAIN[w]) {
        st->update(IND[HEAD[CHAIN[v]]], IND[v], val);
        v = PAR[HEAD[CHAIN[v]]];
    }
    if (v == w) return;
    st->update(IND[w] + 1, IND[v], val);
}

void updatePath(int v, int w, int val) {
    int LCA = lca(v, w);
    updateUp(v, LCA, val);
    updateUp(w, LCA, val);
}

int queryUp(int v, int w) {
    int ret = 0;
    while (CHAIN[v] != CHAIN[w]) {
        MAX(ret, st->query(IND[HEAD[CHAIN[v]]], IND[v]));
        v = PAR[HEAD[CHAIN[v]]];
    }
    if (v == w) return ret;
    MAX(ret, st->query(IND[w] + 1, IND[v]));
    return ret;
}

int queryPath(int v, int w) {
    int LCA = lca(v, w);
    return max(queryUp(v, LCA), queryUp(w, LCA));
}

void initUF() {
    FOR(i, N) {
        UF[i] = i;
        RNK[i] = 0;
    }
}

int find(int p) {
    while (p != UF[p]) p = UF[p] = UF[UF[p]];
    return p;
}

void join(int p, int q) {
    p = find(p);
    q = find(q);
    if (p == q) return;
    if (RNK[p] < RNK[q]) UF[p] = q;
    else if (RNK[p] > RNK[q]) UF[q] = p;
    else {
        UF[q] = p;
        RNK[p]++;
    }
}

bool connected(int p, int q) {
    return find(p) == find(q);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> D >> Q;
    int a, b;
    initUF();
    FOR(i, D) {
        cin >> a >> b;
        if (a == b) {
            continue;
        } else if (connected(a, b)) {
            updates.pb({i, {a, b}});
        } else {
            adj[a].pb(b);
            adj[b].pb(a);
            join(a, b);
        }
    }
    initHLD();
    for (pair<int, pii> u : updates) {
        updatePath(u.s.f, u.s.s, u.f);
    }
    FOR(i, Q) {
        cin >> a >> b;
        if (a == b) {
            cout << 0 << nl;
        } else if (connected(a, b)) {
            int ans = queryPath(a, b);
            if (ans == INT_INF) cout << -1 << nl;
            else cout << ans << nl;
        } else {
            cout << -1 << nl;
        }
    }
    return 0;
}
