// http://codeforces.com/contest/915/problem/E
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

#define MAXQ 300010

int N, Q, num[MAXQ * 2];
umii ind;

struct SegmentTree {
    struct Node {
        int val = 0, lazy = -1, l, r;
    };

private:
    vector<Node> tree;
    int N;
    int *array;

    void propagate(int cur, int cL, int cR) {
        if (tree[cur].lazy != -1) {
            int m = cL + (cR - cL) / 2;
            tree[cur * 2].l = tree[cur].l;
            tree[cur * 2].r = num[m];
            tree[cur * 2].val = tree[cur].lazy * (tree[cur * 2].r - tree[cur * 2].l);
            tree[cur * 2].lazy = tree[cur].lazy;
            tree[cur * 2 + 1].l = num[m];
            tree[cur * 2 + 1].r = tree[cur].r;
            tree[cur * 2 + 1].val = tree[cur].lazy * (tree[cur * 2 + 1].r - tree[cur * 2 + 1].l);
            tree[cur * 2 + 1].lazy = tree[cur].lazy;
            tree[cur].lazy = -1;
        }
    }

    void update(int cur, int cL, int cR, int l, int r, int val) {
        if (cL != cR) propagate(cur, cL, cR);
        if (cL > r || cR < l) return;
        if (cL >= l && cR <= r) {
            bool ext = cL == l;
            tree[cur].l = num[cL - !ext] - ext;
            tree[cur].r = num[cR];
            tree[cur].val = val * (tree[cur].r - tree[cur].l);
            tree[cur].lazy = val;
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, l, r, val);
        update(cur * 2 + 1, m + 1, cR, l, r, val);
        tree[cur].val = tree[cur * 2].val + tree[cur * 2 + 1].val;
    }

    int query(int cur, int cL, int cR, int l, int r) {
        if (cL != cR) propagate(cur, cL, cR);
        if (cL > r || cR < l) return 0;
        if (cL >= l && cR <= r) return tree[cur].val;
        int m = cL + (cR - cL) / 2;
        int left = query(cur * 2, cL, m, l, r);
        int right = query(cur * 2 + 1, m + 1, cR, l, r);
        return left + right;
    }

public:
    SegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = 0;
        }
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

struct query {
    int l, r, k;
} q[MAXQ];

int main() {
    ri(N);
    ri(Q);
    set<int> sorted;
    sorted.insert(1);
    sorted.insert(N);
    FOR(i, Q) {
        ri(q[i].l);
        ri(q[i].r);
        ri(q[i].k);
        sorted.insert(q[i].l);
        sorted.insert(q[i].r);
    }
    int cur = 1;
    num[0] = 0;
    for (int i : sorted) {
        num[cur] = i;
        ind[i] = cur++;
    }
    st = new SegmentTree((int) sorted.size());
    FOR(i, Q) {
        st->update(ind[q[i].l], ind[q[i].r], q[i].k % 2);
        printf("%d\n", st->query(ind[1], ind[N]));
    }
    return 0;
}
