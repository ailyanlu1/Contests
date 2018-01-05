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
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
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
typedef map<ll, ll> mll;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;
typedef unordered_map<ll, ll> umll;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXN 100010
#define MAXK 12
#define MOD ((ll) (1e9 + 7))

int N, Q;
ll POW[MAXN][MAXK], POWSUM[MAXN][MAXK];

struct LazySegmentTree {
    struct Node {
        ll val = 0LL;
        int l = 0, r = 0;
        int lazyL = -1, lazyR = -1, lazyK = -1;
        void push() {
            val = (((val + POWSUM[lazyR][lazyK]) % MOD) - POWSUM[lazyL - 1][lazyK] + MOD) % MOD;
        }
    };

private:
    vector<Node> tree;
    int N;

    void propogate(int cur) {
        if (tree[cur].lazyK != -1) {
            tree[cur * 2].lazyL = tree[cur].lazyL;
            tree[cur * 2].lazyR = tree[cur].lazyR - (tree[cur].r - tree[cur * 2].r);
            tree[cur * 2].lazyK = tree[cur].lazyK;
            tree[cur * 2].push();
            tree[cur * 2 + 1].lazyL = tree[cur].lazyL + (tree[cur * 2 + 1].l - tree[cur].l);
            tree[cur * 2 + 1].lazyR = tree[cur].lazyR;
            tree[cur * 2 + 1].lazyK = tree[cur].lazyK;
            tree[cur * 2 + 1].push();
            tree[cur].lazyL = tree[cur].lazyR = tree[cur].lazyK = -1;
        }
    }

    void build(int cur, int cL, int cR) {
        tree[cur].l = cL;
        tree[cur].r = cR;
        if (cL == cR) return;
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
    }

    void update(int cur, int cL, int cR, int l, int r, int k) {
        if (cL != cR) propogate(cur);
        if (cL > r || cR < l) return;
        if (cL >= l && cR <= r) {
            if (tree[cur].lazyK != -1) {
                tree[cur].push();
                propogate(cur);
            }
            tree[cur].lazyL = cL - l + 1;
            tree[cur].lazyR = cR - l + 1;
            tree[cur].lazyK = k;
            tree[cur].push();
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, l, r, k);
        update(cur * 2 + 1, m + 1, cR, l, r, k);
        tree[cur].val = (tree[cur * 2].val % MOD + tree[cur * 2 + 1].val % MOD) % MOD;
    }

    ll query(int cur, int cL, int cR, int l, int r) {
        if (cL != cR) propogate(cur);
        if (cL > r || cR < l) return 0LL;
        if (cL >= l && cR <= r) {
            if (tree[cur].lazyK != -1) {
                tree[cur].push();
                propogate(cur);
            }
            return tree[cur].val % MOD;
        }
        int m = cL + (cR - cL) / 2;
        ll left = query(cur * 2, cL, m, l, r) % MOD;
        ll right = query(cur * 2 + 1, m + 1, cR, l, r) % MOD;
        return (left + right) % MOD;
    }

public:
    LazySegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        build(1, 1, size);
        N = size;
    }

    void update(int l, int r, int k) {
        update(1, 1, N, l, r, k);
    }

    ll query(int l, int r) {
        return query(1, 1, N, l, r);
    }

    int size() {
        return N;
    }
} *st;

int main() {
    ri(N);
    ri(Q);
    st = new LazySegmentTree(N);
    For(i, 1, N + 1) {
        POW[i][0] = 1LL;
        For(j, 1, MAXK) {
            POW[i][j] = (POW[i][j - 1] * (ll) (i)) % MOD;
        }
    }
    FOR(j, MAXK) {
        POWSUM[0][j] = 0LL;
        For(i, 1, N + 1) {
            POWSUM[i][j] = (POWSUM[i - 1][j] + POW[i][j]) % MOD;
        }
    }
    char op;
    int l, r, k;
    FOR(i, Q) {
        rc(op);
        if (op == 'U') {
            ri(l);
            ri(r);
            ri(k);
            st->update(l, r, k);
        } else if (op == 'Q') {
            ri(l);
            ri(r);
            printf("%lld\n", st->query(l, r) % MOD);
        } else {
            i--;
        }
    }
    return 0;
}
