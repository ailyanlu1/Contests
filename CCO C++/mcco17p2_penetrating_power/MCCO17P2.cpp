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
    static const ll vdef = 0, ldef = 0, qdef = 0;

    static ll merge(ll l, ll r) {
        return max(l, r);
    }

    static ll apply(ll x, ll v) {
        return x + v;
    }

    static ll getSegmentVal(ll x, int len) {
        return x;
    }

    struct Node {
        ll val = LazySegmentTree::vdef, lazy = LazySegmentTree::ldef;
    };

    vector<Node> tree;
    int N;

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
            tree[cur].val = vdef;
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
        tree[cur].val = merge(tree[cur * 2].val, tree[cur * 2 + 1].val);
    }

    void update(int cur, int cL, int cR, int l, int r, ll val) {
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

    ll query(int cur, int cL, int cR, int l, int r) {
        if (cL != cR) propagate(cur, cL, cR);
        if (cL > r || cR < l) return qdef;
        if (cL >= l && cR <= r) return tree[cur].val;
        int m = cL + (cR - cL) / 2;
        ll left = query(cur * 2, cL, m, l, r);
        ll right = query(cur * 2 + 1, m + 1, cR, l, r);
        return merge(left, right);
    }

public:
    LazySegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        build(1, 0, size - 1);
        N = size;
    }

    void update(int l, int r, ll val) {
        update(1, 0, N - 1, l, r, val);
    }

    ll query(int l, int r) {
        if (l > r || l >= N || r < 0) return 0;
        return query(1, 0, N - 1, l, r);
    }

    int size() {
        return N;
    }
} *st;

int N, K, Q;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K >> Q;
    st = new LazySegmentTree(N);
    int t, a, b;
    FOR(i, Q) {
        cin >> t >> a >> b;
        if (t == 0) {
            st->update(max(a - K + 1, 0), min(N - 1, a), b);
        } else {
            cout << st->query(max(0, a), min(N - 1, b)) << nl;
        }
    }
    return 0;
}
