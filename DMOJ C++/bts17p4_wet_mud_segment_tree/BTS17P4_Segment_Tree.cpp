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

struct SegmentTree {
private:
    struct Node {
        int val = INT_MAX;
    };

    vector<Node> tree;
    int N;

    void build(int cur, int cL, int cR) {
        if (cL == cR) {
            tree[cur].val = INT_MAX;
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
        tree[cur].val = min(tree[cur * 2].val, tree[cur * 2 + 1].val);
    }

    void update(int cur, int cL, int cR, int ind, int val) {
        if (cL > ind || cR < ind) return;
        if (cL == cR) {
            tree[cur].val = val;
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, ind, val);
        update(cur * 2 + 1, m + 1, cR, ind, val);
        tree[cur].val = min(tree[cur * 2].val, tree[cur * 2 + 1].val);
    }

    pii query(int cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) return mp(INT_MAX, -1);
        if (cL >= l && cR <= r) return mp(tree[cur].val, l);
        int m = cL + (cR - cL) / 2;
        pii left = query(cur * 2, cL, m, l, r);
        pii right = query(cur * 2 + 1, m + 1, cR, l, r);
        return min(left, right);
    }

public:
    SegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        build(1, 1, size);
        N = size;
    }

    void update(int ind, int val) {
        update(1, 1, N, ind, val);
    }

    pii query(int l, int r) {
        return query(1, 1, N, l, r);
    }

    int size() {
        return N;
    }
} *st;

#define MAXN 100005
#define MAXT 1000005

int N, M, J, p, t, tToP[MAXT], pToT[MAXN];
set<int> times;

int main() {
    cin >> N >> M >> J;
    st = new SegmentTree(N);
    FOR(i, M) {
        cin >> p >> t;
        st->update(p, t);
        tToP[t] = p;
        pToT[p] = t;
        times.insert(t);
    }
    int curPos = 0, curTime = 0;
    pii q;
    auto iter = times.begin();
    while (curPos + J <= N) {
        q = st->query(curPos + 1, min(curPos + J, N));
        if (q.f == INT_MAX) {
            cout << -1 << nl;
            return 0;
        }
        MAX(curTime, q.f);
        curPos = q.s;
        while (*iter < curTime) {
            st->update(pToT[*(iter++)], 0);
        }
    }
    cout << curTime << nl;
    return 0;
}
