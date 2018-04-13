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

struct LazySegmentTree {
private:
    static const int vdef = 0, ldef = 0, qdef = INT_MAX;

    static int merge(int l, int r) {
        return min(l, r);
    }

    static int apply(int x, int v) {
        return x + v;
    }

    static int getSegmentVal(int x, int len) {
        return x;
    }

    struct Node {
        int val = LazySegmentTree::vdef, lazy = LazySegmentTree::ldef;
    };

    vector<Node> tree;
    int N;

    void propogate(int cur, int cL, int cR) {
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
            tree[cur].val = vdef;
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
        tree[cur].val = merge(tree[cur * 2].val, tree[cur * 2 + 1].val);
    }

    void update(int cur, int cL, int cR, int l, int r, int val) {
        if (cL != cR) propogate(cur, cL, cR);
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
        if (cL != cR) propogate(cur, cL, cR);
        if (cL > r || cR < l) return qdef;
        if (cL >= l && cR <= r) return tree[cur].val;
        int m = cL + (cR - cL) / 2;
        int left = query(cur * 2, cL, m, l, r);
        int right = query(cur * 2 + 1, m + 1, cR, l, r);
        return merge(left, right);
    }

public:
    LazySegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
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

#define MAXN 100005

int N, A[MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) cin >> A[i];
    st = new LazySegmentTree(N);
    int ans = 0;
    FOR(i, N / 2) {
        st->update(1, A[i], 2);
        st->update(1, A[i * 2], -1);
        st->update(1, A[i * 2 + 1], -1);
        int q = st->query(1, N);
        if (q >= 0) ans = i + 1;
    }
    cout << ans << nl;
    return 0;
}
