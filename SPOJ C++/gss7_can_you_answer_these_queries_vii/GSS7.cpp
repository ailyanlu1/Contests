// http://www.spoj.com/problems/GSS7/
#include <bits/stdc++.h>
using namespace std;

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

#define MAXN 100005

int N, Q, DEP[MAXN], PAR[MAXN], CHAIN[MAXN], SZ[MAXN], HEAD[MAXN], IND[MAXN], VERT[MAXN], VAL[MAXN], X[MAXN], chainNum, curInd;
vector<int> adj[MAXN];

struct Node {
    long long pre, suf, sum, maxSum, lazy;
    bool isNull;

    Node() {
        this->pre = this->suf = this->sum = this->maxSum = 0;
        this->lazy = LL_INF;
        this->isNull = true;
    }

    Node(long long val) {
        this->pre = this->suf = this->maxSum = val;
        this->sum = val;
        this->lazy = LL_INF;
        this->isNull = false;
    }

    Node(Node l, Node r) {
        if (l.isNull) {
            this->pre = r.pre;
            this->suf = r.suf;
            this->sum = r.sum;
            this->maxSum = r.maxSum;
            this->lazy = LL_INF;
            this->isNull = r.isNull;
        } else if (r.isNull) {
            this->pre = l.pre;
            this->suf = l.suf;
            this->sum = l.sum;
            this->maxSum = l.maxSum;
            this->lazy = LL_INF;
            this->isNull = l.isNull;
        } else {
            this->pre = max(l.pre, l.sum + r.pre);
            this->suf = max(l.suf + r.sum, r.suf);
            this->sum = l.sum + r.sum;
            this->maxSum = max(max(l.maxSum, r.maxSum), l.suf + r.pre);
            this->lazy = LL_INF;
            this->isNull = false;
        }
    }
};

struct MaxContiguousSumSegmentTree {
private:
    vector<Node> tree;
    int *array;
    int N;

    void propogate(int cur, int cL, int cR) {
        if (tree[cur].lazy != LL_INF) {
            int m = cL + (cR - cL) / 2;
            tree[cur * 2].sum = tree[cur].lazy * (m - cL + 1);
            tree[cur * 2].pre = tree[cur * 2].suf = tree[cur * 2].maxSum = tree[cur * 2].sum;
            tree[cur * 2].lazy = tree[cur].lazy;
            tree[cur * 2 + 1].sum = tree[cur].lazy * (cR - m);
            tree[cur * 2 + 1].pre = tree[cur * 2 + 1].suf = tree[cur * 2 + 1].maxSum = tree[cur * 2 + 1].sum;
            tree[cur * 2 + 1].lazy = tree[cur].lazy;
            tree[cur].lazy = LL_INF;
        }
    }

    void build(int cur, int cL, int cR) {
        if (cL == cR) {
            tree[cur] = Node(array[cL]);
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL, m);
        build(cur * 2 + 1, m + 1, cR);
        tree[cur] = Node(tree[cur * 2], tree[cur * 2 + 1]);
    }

    void update(int cur, int cL, int cR, int l, int r, long long val) {
        if (cL != cR) propogate(cur, cL, cR);
        if (cL > r || cR < l) return;
        if (cL >= l && cR <= r) {
            tree[cur].sum = val * (cR - cL + 1);
            tree[cur].pre = tree[cur].suf = tree[cur].maxSum = tree[cur].sum;
            tree[cur].lazy = val;
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, l, r, val);
        update(cur * 2 + 1, m + 1, cR, l, r, val);
        tree[cur] = Node(tree[cur * 2], tree[cur * 2 + 1]);
    }

    Node query(int cur, int cL, int cR, int l, int r) {
        if (cL != cR) propogate(cur, cL, cR);
        if (cL > r || cR < l) return Node();
        if (cL >= l && cR <= r) return tree[cur];
        int m = cL + (cR - cL) / 2;
        Node left = query(cur * 2, cL, m, l, r);
        Node right = query(cur * 2 + 1, m + 1, cR, l, r);
        return Node(left, right);
    }

public:
    MaxContiguousSumSegmentTree(int size, int *arr, bool oneIndexed) : tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = arr[i - !oneIndexed];
        }
        build(1, 1, size);
        N = size;
    }

    void update(int l, int r, long long val) {
        update(1, 1, N, l, r, val);
    }

    Node query(int l, int r) {
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
    FOR(i, N) HEAD[i] = -1;
    dfs(0, 0, -1);
    hld(0, -1);
    For(i, 1, N + 1) VAL[i] = X[VERT[i]];
    st = new MaxContiguousSumSegmentTree(N, VAL, true);
}

int lca(int v, int w) {
    while (CHAIN[v] != CHAIN[w]) {
        if (DEP[HEAD[CHAIN[v]]] < DEP[HEAD[CHAIN[w]]]) w = PAR[HEAD[CHAIN[w]]];
        else v = PAR[HEAD[CHAIN[v]]];
    }
    return DEP[v] < DEP[w] ? v : w;
}

void updateUp(int v, int w, ll val, bool includeW) {
    while (CHAIN[v] != CHAIN[w]) {
        st->update(IND[HEAD[CHAIN[v]]], IND[v], val);
        v = PAR[HEAD[CHAIN[v]]];
    }
    if (!includeW && v == w) return;
    st->update(IND[w] + !includeW, IND[v], val);
}

void updatePath(int v, int w, int val) {
    int LCA = lca(v, w);
    updateUp(v, LCA, val, false);
    updateUp(w, LCA, val, true);
}

Node queryUp(int v, int w, bool up, bool includeW) {
    Node ans;
    while (CHAIN[v] != CHAIN[w]) {
        Node x = st->query(IND[HEAD[CHAIN[v]]], IND[v]);
        if (up) {
            swap(x.pre, x.suf);
            ans = Node(ans, x);
        } else {
            ans = Node(x, ans);
        }
        v = PAR[HEAD[CHAIN[v]]];
    }
    if (!includeW && v == w) return ans;
    Node x = st->query(IND[w] + !includeW, IND[v]);
    if (up) {
        swap(x.pre, x.suf);
        ans = Node(ans, x);
    } else {
        ans = Node(x, ans);
    }
    return ans;
}

ll queryPath(int v, int w) {
    int LCA = lca(v, w);
    Node a = queryUp(v, LCA, true, false);
    Node b = queryUp(w, LCA, false, true);
    return Node(a, b).maxSum;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) cin >> X[i];
    int t, a, b, c;
    FOR(i, N - 1) {
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    initHLD();
    cin >> Q;
    FOR(i, Q) {
        cin >> t;
        if (t == 1) {
            cin >> a >> b;
            a--; b--;
            cout << max(0LL, queryPath(a, b)) << nl;
        } else {
            cin >> a >> b >> c;
            a--; b--;
            updatePath(a, b, c);
        }
    }
    return 0;
}
