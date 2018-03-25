// https://naipc18.kattis.com/problems/zoninghouses
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

struct SegmentTree {
    struct Node {
        int max1 = -INT_INF, max2 = -INT_INF;
        int min1 = INT_INF, min2 = INT_INF;
    };

private:
    vector<Node> tree;
    int N;
    int *array;

    void build(int cur, int cL, int cR) {
        if (cL == cR) {
            tree[cur].max1 = tree[cur].min1 = array[cL];
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
        if (tree[cur * 2].max1 > tree[cur * 2 + 1].max1) {
            tree[cur].max1 = tree[cur * 2].max1;
            tree[cur].max2 = max(tree[cur * 2].max2, tree[cur * 2 + 1].max1);
        } else {
            tree[cur].max1 = tree[cur * 2 + 1].max1;
            tree[cur].max2 = max(tree[cur * 2 + 1].max2, tree[cur * 2].max1);
        }
        if (tree[cur * 2].min1 < tree[cur * 2 + 1].min1) {
            tree[cur].min1 = tree[cur * 2].min1;
            tree[cur].min2 = min(tree[cur * 2].min2, tree[cur * 2 + 1].min1);
        } else {
            tree[cur].min1 = tree[cur * 2 + 1].min1;
            tree[cur].min2 = min(tree[cur * 2 + 1].min2, tree[cur * 2].min1);
        }
    }

    pair<pii, pii> query(int cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) return mp(mp(-INT_INF, -INT_INF), mp(INT_INF, INT_INF));
        if (cL >= l && cR <= r) return mp(mp(tree[cur].max1, tree[cur].max2), mp(tree[cur].min1, tree[cur].min2));
        int m = cL + (cR - cL) / 2;
        pair<pii, pii> left = query(cur * 2, cL, m, l, r);
        pair<pii, pii> right = query(cur * 2 + 1, m + 1, cR, l, r);
        pair<pii, pii> ans;
        if (left.f.f > right.f.f) {
            ans.f.f = left.f.f;
            ans.f.s = max(left.f.s, right.f.f);
        } else {
            ans.f.f = right.f.f;
            ans.f.s = max(right.f.s, left.f.f);
        }
        if (left.s.f < right.s.f) {
            ans.s.f = left.s.f;
            ans.s.s = min(left.s.s, right.s.f);
        } else {
            ans.s.f = right.s.f;
            ans.s.s = min(right.s.s, left.s.f);
        }
        return ans;
    }

public:
    SegmentTree(int size, int *arr, bool oneIndexed): tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = arr[i - !oneIndexed];
        }
        build(1, 1, size);
        N = size;
    }

    SegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = 0;
        }
        build(1, 1, size);
        N = size;
    }

    pair<pii, pii> query(int l, int r) {
        return query(1, 1, N, l, r);
    }

    int size() {
        return N;
    }
};

#define MAXN 100005

int N, Q, X[MAXN], Y[MAXN];
SegmentTree *x, *y;
umap<pii, int, pair_hash<int, int>> p;

inline bool inRange(int l, int r, int a) {
    return l <= a && a <= r;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    For(i, 1, N + 1) {
        cin >> X[i] >> Y[i];
        p[{X[i], Y[i]}] = i;
    }
    x = new SegmentTree(N, X, true);
    y = new SegmentTree(N, Y, true);
    int a, b;
    FOR(i, Q) {
        cin >> a >> b;
        pair<pii, pii> xAns = x->query(a, b);
        pair<pii, pii> yAns = y->query(a, b);
        int ans = INT_MAX;
        if (p.count({xAns.f.f, yAns.f.f}) && inRange(a, b, p[{xAns.f.f, yAns.f.f}])) {
            MIN(ans, max(xAns.f.s - xAns.s.f, yAns.f.s - yAns.s.f));
        }
        if (p.count({xAns.f.f, yAns.s.f}) && inRange(a, b, p[{xAns.f.f, yAns.s.f}])) {
            MIN(ans, max(xAns.f.s - xAns.s.f, yAns.f.f - yAns.s.s));
        }
        if (p.count({xAns.s.f, yAns.f.f}) && inRange(a, b, p[{xAns.s.f, yAns.f.f}])) {
            MIN(ans, max(xAns.f.f - xAns.s.s, yAns.f.s - yAns.s.f));
        }
        if (p.count({xAns.s.f, yAns.s.f}) && inRange(a, b, p[{xAns.s.f, yAns.s.f}])) {
            MIN(ans, max(xAns.f.f - xAns.s.s, yAns.f.f - yAns.s.s));
        }
        MIN(ans, max(xAns.f.f - xAns.s.s, yAns.f.f - yAns.s.f));
        MIN(ans, max(xAns.f.s - xAns.s.f, yAns.f.f - yAns.s.f));
        MIN(ans, max(xAns.f.f - xAns.s.f, yAns.f.f - yAns.s.s));
        MIN(ans, max(xAns.f.f - xAns.s.f, yAns.f.s - yAns.s.f));
        cout << ans << nl;
    }
    return 0;
}
