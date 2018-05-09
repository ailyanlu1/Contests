// http://codeforces.com/contest/52/problem/C
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

template<typename T1, typename T2, typename H1 = hash<T1>, typename H2 = hash<T2>>
struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * H1 {}(p.first) + H2 {}(p.second);}};

// range modifications, range query
// works when order of modifications does not affect result
struct SegmentTree_RM_RQ {
private:
    int N, H;
    int *T;
    int *L; // storing lazy values
    const int def = 0; // default value
    const int qdef = INT_MAX; // query default value
    const int ldef = 0; // lazy default value

    // applies the change to index i and updates the lazy value if the index is not a leaf
    void apply(int i, int v) {
        T[i] += v;
        if (i < N) L[i] += v;
    }

     // updates parents of index i
    void pushup(int i) {
        while (i > 1) {
            i >>= 1;
            T[i] = merge(T[i << 1], T[i << 1 | 1]) + L[i];
        }
    }

    // propagates changes down from index i
    void propagate(int i) {
        for (int h = H; h > 0; h--) {
            int ii = i >> h;
            if (L[ii] != ldef) {
                apply(ii << 1, L[ii]);
                apply(ii << 1 | 1, L[ii]);
                L[ii] = ldef;
            }
        }
    }

    // merges 2 values together in the correct order
    // operation must be associative (but not necessarily commutative)
    int merge(int l, int r) {
        return min(l, r);
    }

public:
    SegmentTree_RM_RQ(int size, int *A, bool oneIndexed) {
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

    SegmentTree_RM_RQ(int size) {
        N = size;
        T = new int[2 * N];
        L = new int[N];
        H = 0;
        for (int i = 1, H = 0; i <= N; H++) i <<= 1;
        for (int i = 1; i < 2 * N; i++) T[i] = def;
        for (int i = 1; i < N; i++) L[i] = ldef;
    }

    // adds v to the interval [l, r] (one-indexed)
    void update(int l, int r, int v) {
        l += (N - 1);
        r += (N - 1);
        int l0 = l, r0 = r;
        for (; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, v);
            if (!(r & 1)) apply(r--, v);
        }
        pushup(l0);
        pushup(r0);
    }

    // returns the maximum element on the interval [l, r] (one-indexed)
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

#define MAXN 200005

int N, M, A[MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    For(i, 1, N + 1) cin >> A[i];
    st = new SegmentTree_RM_RQ(N, A, true);
    cin >> M;
    int l, r, v;
    string s;
    getline(cin, s);
    FOR(i, M) {
        getline(cin, s);
        if (sscanf(s.data(), "%d %d %d", &l, &r, &v) == 2) {
            l++; r++;
            if (l <= r) cout << st->query(l, r) << nl;
            else cout << min(st->query(1, r), st->query(l, N)) << nl;
        } else {
            l++; r++;
            if (l <= r) st->update(l, r, v);
            else {
                st->update(1, r, v);
                st->update(l, N, v);
            }
        }
    }
    return 0;
}
