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

#define MAXN 100005

struct triple {
    ll h;
    int i;
    ll dp;

    bool operator < (const triple &t) const { return h < t.h; }
    bool operator <= (const triple &t) const { return h <= t.h; }
    bool operator > (const triple &t) const { return h > t.h; }
    bool operator >= (const triple &t) const { return h >= t.h; }
    bool operator == (const triple &t) const { return h == t.h && i == t.i && dp == t.dp; }
    bool operator != (const triple &t) const { return h != t.h || i != t.i || dp != t.dp; }
};

int N, ind[MAXN];
ll H[MAXN], P[MAXN];
minpq<triple> good;

struct LazySegmentTree {
    struct Node {
        ll val = LL_INF, lazy = 0;
    };

private:
    vector<Node> tree;
    int N;

    void propogate(int cur) {
        if (tree[cur].lazy != 0) {
            tree[cur * 2].val += tree[cur].lazy;
            tree[cur * 2].lazy += tree[cur].lazy;
            tree[cur * 2 + 1].val += tree[cur].lazy;
            tree[cur * 2 + 1].lazy += tree[cur].lazy;
            tree[cur].lazy = 0;
        }
    }

    void update(int cur, int cL, int cR, int l, int r, ll val) {
        if (cL != cR) propogate(cur);
        if (cL > r || cR < l) return;
        if (cL >= l && cR <= r) {
            tree[cur].val += val;
            tree[cur].lazy += val;
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, l, r, val);
        update(cur * 2 + 1, m + 1, cR, l, r, val);
        tree[cur].val = min(tree[cur * 2].val, tree[cur * 2 + 1].val);
    }

    ll query(int cur, int cL, int cR, int l, int r) {
        if (cL != cR) propogate(cur);
        if (cL > r || cR < l) return LL_INF;
        if (cL >= l && cR <= r) return tree[cur].val;
        int m = cL + (cR - cL) / 2;
        ll left = query(cur * 2, cL, m, l, r);
        ll right = query(cur * 2 + 1, m + 1, cR, l, r);
        return min(left, right);
    }

public:
    LazySegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        N = size;
    }

    void update(int l, int r, ll val) {
        if (l <= r) update(1, 1, N, l, r, val);
    }

    ll query(int l, int r) {
        return l <= r ? query(1, 1, N, l, r) : LL_INF;
    }

    int size() {
        return N;
    }
} *st1, *st2;

int main() {
    ri(N);
    vector<plli> toSort;
    FOR(i, N) {
        rll(H[i]);
        toSort.pb({H[i], -i});
    }
    sort(toSort.begin(), toSort.end());
    FOR(i, N) ind[-toSort[i].s] = i + 1;
    For(i, 1, N) rll(P[i]);
    st1 = new LazySegmentTree(N);
    st2 = new LazySegmentTree(N);
    good.push({H[0], 0, 0});
    st1->update(ind[0], ind[0], -H[0] - LL_INF);
    st2->update(ind[0], ind[0], H[0] - LL_INF);
    For(i, 1, N) {
        st1->update(1, ind[i] - 1, H[i]);
        st2->update(ind[i] + 1, N, -H[i]);
        ll dp = min(st1->query(ind[i - 1], ind[i] - 1), st2->query(max(ind[i] + 1, ind[i - 1]), N)) + P[i];
        st1->update(1, ind[i] - 1, -H[i]);
        st2->update(ind[i] + 1, N, H[i]);
        st1->update(ind[i], ind[i], dp - H[i] - LL_INF);
        st2->update(ind[i], ind[i], dp + H[i] - LL_INF);
        while (!good.empty() && good.top().h < H[i]) {
            st1->update(ind[good.top().i], ind[good.top().i], LL_INF - (good.top().dp - good.top().h));
            st2->update(ind[good.top().i], ind[good.top().i], LL_INF - (good.top().dp + good.top().h));
            good.pop();
        }
        good.push({H[i], i, dp});
    }
    ll ans = LL_INF;
    while (!good.empty()) {
        MIN(ans, good.top().dp);
        good.pop();
    }
    printf("%lld\n", ans + N);
    return 0;
}
