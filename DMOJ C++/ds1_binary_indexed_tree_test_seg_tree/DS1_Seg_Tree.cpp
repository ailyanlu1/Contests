#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
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

template <typename T>
struct SegmentTree {
    struct Node {
        T val = 0;
    };

private:
    vector<Node> tree;
    int N;
    T *array;

    void build(int cur, int cL, int cR) {
        if (cL == cR) {
            tree[cur].val = array[cL];
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
        tree[cur].val = tree[cur * 2].val + tree[cur * 2 + 1].val;
    }

    void update(int cur, int cL, int cR, int ind, T val) {
        if (cL > ind || cR < ind) return;
        if (cL >= ind && cR <= ind) {
            tree[cur].val = val;
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, ind, val);
        update(cur * 2 + 1, m + 1, cR, ind, val);
        tree[cur].val = tree[cur * 2].val + tree[cur * 2 + 1].val;
    }

    T query(int cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) return 0;
        if (cL >= l && cR <= r) return tree[cur].val;
        int m = cL + (cR - cL) / 2;
        T left = query(cur * 2, cL, m, l, r);
        T right = query(cur * 2 + 1, m + 1, cR, l, r);
        return left + right;
    }

public:
    SegmentTree(int size, T *arr): tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        array = new T[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = arr[i];
        }
        build(1, 1, size);
        N = size;
    }

    void update(int ind, T val) {
        update(1, 1, N, ind, val);
    }

    T query(int l, int r) {
        return query(1, 1, N, l, r);
    }

    int size() {
        return N;
    }
};

#define MAXNV 100005

int N, M, x, y, *freq;
ll *A, v, oldV;
char op;
SegmentTree<ll> *sum;
SegmentTree<int> *cnt;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    A = new ll[N + 1];
    freq = new int[MAXNV + 1];
    FOR(i, MAXNV) freq[i] = 0;
    For(i, 1, N + 1) {
        cin >> A[i];
        freq[A[i]]++;
    }
    sum = new SegmentTree<ll>(N, A);
    cnt = new SegmentTree<int>(MAXNV, freq);
    FOR(i, M) {
        cin >> op;
        if (op == 'C') {
            cin >> x >> v;
            sum->update(x, v);
            freq[A[x]]--;
            cnt->update(A[x], freq[A[x]]);
            A[x] = v;
            freq[v]++;
            cnt->update(v, freq[v]);
        } else if (op == 'S') {
            cin >> x >> y;
            cout << sum->query(x, y) << nl;
        } else if (op == 'Q') {
            cin >> x;
            cout << cnt->query(1, x) << nl;
        } else {
            i--;
        }
    }
    return 0;
}
