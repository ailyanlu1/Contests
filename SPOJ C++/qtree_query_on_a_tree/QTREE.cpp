// http://www.spoj.com/problems/QTREE/
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

#define MAXN 10005

int T, N, DEP[MAXN], PAR[MAXN], CHAIN[MAXN], SZ[MAXN], HEAD[MAXN], IND[MAXN], VERT[MAXN], WEIGHT[MAXN], chainNum, curInd;
vector<pii> adj[MAXN];
vector<pii> edges;

struct SegmentTree {
private:
    static const int vdef = 0, qdef = 0;

    static int merge(int l, int r) {
        return max(l, r);
    }

    static int apply(int x, int v) {
        return v;
    }

    struct Node {
        int val = SegmentTree::vdef;
    };

    vector<Node> tree;
    int N;
    int *array;

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

    void update(int cur, int cL, int cR, int ind, int val) {
        if (cL > ind || cR < ind) return;
        if (cL == cR) {
            tree[cur].val = apply(tree[cur].val, val);
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, ind, val);
        update(cur * 2 + 1, m + 1, cR, ind, val);
        tree[cur].val = merge(tree[cur * 2].val, tree[cur * 2 + 1].val);
    }

    int query(int cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) return qdef;
        if (cL >= l && cR <= r) return tree[cur].val;
        int m = cL + (cR - cL) / 2;
        int left = query(cur * 2, cL, m, l, r);
        int right = query(cur * 2 + 1, m + 1, cR, l, r);
        return merge(left, right);
    }

public:
    SegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        array = new int[size + 1];
        for (int i = 0; i < size; i++) {
            array[IND[i]] = WEIGHT[i];
        }
        build(1, 1, size);
        N = size;
    }

    void update(int ind, int val) {
        update(1, 1, N, ind, val);
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
    for (pii e : adj[v]) {
        if (e.f == prev) continue;
        WEIGHT[e.f] = e.s;
        dfs(e.f, d + 1, v);
        SZ[v] += SZ[e.f];
    }
}

void hld(int v, int prev) {
    if (HEAD[chainNum] == -1) HEAD[chainNum] = v;
    CHAIN[v] = chainNum;
    IND[v] = curInd;
    VERT[curInd++] = v;
    int maxInd = -1;
    for (pii e : adj[v]) {
        if (e.f != prev && (maxInd == -1 || SZ[maxInd] < SZ[e.f])) maxInd = e.f;
    }
    if (maxInd != -1) hld(maxInd, v);
    for (pii e : adj[v]) {
        if (e.f == prev || e.f == maxInd) continue;
        chainNum++;
        hld(e.f, v);
    }
}

void initHLD() {
    chainNum = 0;
    curInd = 1;
    FOR(i, N) HEAD[i] = -1;
    dfs(0, 0, -1);
    hld(0, -1);
    st = new SegmentTree(N);
}

int lca(int v, int w) {
    while (CHAIN[v] != CHAIN[w]) {
        if (DEP[HEAD[CHAIN[v]]] < DEP[HEAD[CHAIN[w]]]) w = PAR[HEAD[CHAIN[w]]];
        else v = PAR[HEAD[CHAIN[v]]];
    }
    return DEP[v] < DEP[w] ? v : w;
}

void update(int v, int w, int val) {
    if (PAR[v] == w) st->update(IND[v], val);
    else if (PAR[w] == v) st->update(IND[w], val);
    else assert(false);
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

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(t, T) {
        cin >> N;
        FOR(i, N) adj[i].clear();
        edges.clear();
        int a, b, c;
        FOR(i, N - 1) {
            cin >> a >> b >> c;
            a--; b--;
            adj[a].pb({b, c});
            adj[b].pb({a, c});
            edges.pb({a, b});
        }
        initHLD();
        string cmd;
        while (true) {
            cin >> cmd;
            if (cmd == "CHANGE") {
                cin >> a >> b;
                a--;
                update(edges[a].f, edges[a].s, b);
            } else if (cmd == "QUERY") {
                cin >> a >> b;
                a--; b--;
                cout << queryPath(a, b) << nl;
            } else if (cmd == "DONE") {
                break;
            } else {
                assert(false);
            }
        }
    }
    return 0;
}
