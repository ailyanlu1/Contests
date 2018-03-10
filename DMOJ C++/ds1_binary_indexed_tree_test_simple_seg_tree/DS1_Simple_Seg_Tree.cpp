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
private:
    int N;
    T *A;

public:
    SegmentTree(int size, T *arr) {
        N = size;
        A = new T[2 * N];
        for (int i = 0; i < N; i++) A[N + i] = arr[i + 1];
        for (int i = N - 1; i > 0; i--) A[i] = A[i << 1] + A[i << 1 | 1];
    }

    void update(int i, T v) {
        for (A[i += (N - 1)] = v; i >>= 1;) A[i] = A[i << 1] + A[i << 1 | 1];
    }

    T query(int l, int r) {
        T q = 0;
        for (l += (N - 1), r += (N - 1); l <= r; l >>= 1, r >>= 1) {
            if (l & 1) q += A[l++];
            if (!(r & 1)) q += A[r--];
        }
        return q;
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
