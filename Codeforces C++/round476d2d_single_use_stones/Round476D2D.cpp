// http://codeforces.com/contest/965/problem/D
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

#define MAXW 100005

int W, L, cnt[MAXW], cur[MAXW];
bool inPQ[MAXW];

struct SegmentTree {
private:
    struct Node {
        pii val = {0, 0};
    };

    vector<Node> tree;
    int N;
    int *array;

    void build(int cur, int cL, int cR) {
        if (cL == cR) {
            tree[cur].val = {array[cL] ? cL : 0, array[cL]};
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
        tree[cur].val = max(tree[cur * 2].val, tree[cur * 2 + 1].val);
    }

    void update(int cur, int cL, int cR, int ind, int val) {
        if (cL > ind || cR < ind) return;
        if (cL == cR) {
            tree[cur].val.s += val;
            if (tree[cur].val.s == 0) tree[cur].val.f = 0;
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, ind, val);
        update(cur * 2 + 1, m + 1, cR, ind, val);
        tree[cur].val = max(tree[cur * 2].val, tree[cur * 2 + 1].val);
    }

    pii query(int cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) return {0, 0};
        if (cL >= l && cR <= r) return tree[cur].val;
        int m = cL + (cR - cL) / 2;
        pii left = query(cur * 2, cL, m, l, r);
        pii right = query(cur * 2 + 1, m + 1, cR, l, r);
        return max(left, right);
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

    void update(int ind, int val) {
        update(1, 1, N, ind, val);
    }

    pii query(int l, int r) {
        return query(1, 1, N, l, r);
    }

    int size() {
        return N;
    }
};

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> W >> L;
    For(i, 1, W) cin >> cnt[i];
    cnt[W] = INT_INF;
    FOR(i, W + 1) cur[i] = 0;
    FOR(i, W + 1) inPQ[i] = 0;
    SegmentTree st(W, cnt, true);
    minpq<int> PQ;
    PQ.push(0);
    inPQ[0] = 1;
    cur[0] = INT_INF;
    while (!PQ.empty()) {
        int x = PQ.top();
        PQ.pop();
        inPQ[x] = 0;
        while (true) {
            pii y = st.query(x + 1, x + L);
            if (y.s == 0) break;
            cur[y.f] += min(cur[x], y.s);
            if (y.f != W) st.update(y.f, -min(cur[x], y.s));
            if (x > 0) cur[x] -= min(cur[x], y.s);
            if (!inPQ[y.f] && y.f != W) {
                inPQ[y.f] = 1;
                PQ.push(y.f);
            }
            if (cur[x] == 0) break;
        }
    }
    cout << cur[W] << nl;
    return 0;
}
