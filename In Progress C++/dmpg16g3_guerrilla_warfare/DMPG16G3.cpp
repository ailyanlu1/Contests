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

#define MAXN 100005

int N, Q, DEP[MAXN], PAR[MAXN], CHAIN[MAXN], SZ[MAXN], HEAD[MAXN], IND[MAXN], VERT[MAXN], CNT[MAXN], chainNum, curInd;
vector<int> adj[MAXN];

// range assignments, range query
struct SegmentTree_RA_RQ {
private:
    int N, H;
    int *T;
    int *L; // storing lazy values
    const int def = 0; // default value
    const int qdef = 0; // query default value
    const int ldef = 0; // lazy default value

    // applies the change to index i and updates the lazy value if the index is not a leaf
    // k is the length of the interval of node i
    void apply(int i, int v, int k) {
        T[i] = v * k; // for maximum value queries: T[i] = v, for sum queries: T[i] = v * k
        if (i < N) L[i] = v;
    }

    // evaluates the value of index i
    // k is the length of the interval of node i
    int eval(int i, int k) {
        return L[i] == ldef ? merge(T[i << 1], T[i << 1 | 1]) : L[i] * k; // for maximum value queries: L[i], for sum queries: L[i] = v * k
    }

    // updates parents of index i
    void pushup(int i) {
        for (int k = 2; i > 1; k <<= 1) {
            i >>= 1;
            T[i] = eval(i, k);
        }
    }

    // propagates changes down from index i
    void propagate(int i) {
        for (int h = H, k = 1 << (H - 1); h > 0; h--, k >>= 1) {
            int ii = i >> h;
            if (L[ii] != ldef) {
                apply(ii << 1, L[ii], k);
                apply(ii << 1 | 1, L[ii], k);
                L[ii] = ldef;
            }
        }
    }

    // merges 2 values together in the correct order
    // operation must be associative (but not necessarily commutative)
    int merge(int l, int r) {
        return l + r;
    }

public:
    SegmentTree_RA_RQ(int size, int *A, bool oneIndexed) {
        N = size;
        T = new int[2 * N];
        L = new int[N];
        H = 0;
        for (int i = 1; i <= N; H++) i <<= 1;
        for (int i = 0; i < N; i++) {
            T[N + i] = A[i + oneIndexed];
            L[i] = ldef;
        }
        for (int i = N - 1; i > 0; i--) T[i] = merge(T[i << 1], T[i << 1 | 1]);
    }

    SegmentTree_RA_RQ(int size) {
        N = size;
        T = new int[2 * N];
        L = new int[N];
        H = 0;
        for (int i = 1, H = 0; i <= N; H++) i <<= 1;
        for (int i = 1; i < 2 * N; i++) T[i] = def;
        for (int i = 1; i < N; i++) L[i] = ldef;
    }

    // assigns v to all elements on the interval [l, r] (one-indexed)
    void update(int l, int r, int v) {
        l += (N - 1);
        r += (N - 1);
        propagate(l);
        propagate(r);
        int l0 = l, r0 = r, k = 1;
        for (; l <= r; l >>= 1, r >>= 1, k <<= 1) {
            if (l & 1) apply(l++, v, k);
            if (!(r & 1)) apply(r--, v, k);
        }
        pushup(l0);
        pushup(r0);
    }

    // returns the sum of all elements on the interval [l, r] (one-indexed)
    int query(int l, int r) {
        l += (N - 1);
        r += (N - 1);
        propagate(l);
        propagate(r);
        int ql = qdef, qr = qdef;
        for (; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) ql = merge(ql, T[l++]);
            if (!(r & 1)) qr = merge(T[r--], qr);
        }
        return merge(ql, qr);
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
    For(i, 1, N) CNT[i] = 1;
    CNT[0] = 0;
    st = new SegmentTree_RA_RQ(N, CNT, false);
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

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int t, a, b;
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
            updatePath(a, b, 0);
        } else if (t == 2) {

        } else {
            i--;
        }
    }
    return 0;
}
