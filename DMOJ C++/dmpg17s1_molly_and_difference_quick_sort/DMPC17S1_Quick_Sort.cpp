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

const int INSERTION_SORT_CUTOFF = 8;
const int MEDIAN_OF_3_CUTOFF = 40;

template <typename T> inline T *median3(T *a, T *b, T *c) {
    return (*a < *b ? (*b < *c ? b : (*a < *c ? c : a)) : (*c < *b ? b : (*c < *a ? c : a)));
}

template <typename It> void quick_sort(It st, It en) {
    int n = en - st;
    if (n <= INSERTION_SORT_CUTOFF) { // insertion sort
        for (int i = 0; i < n; i++) {
            for (int j = i; j > 0 && st[j] < st[j - 1]; j--) {
                swap(st[j], st[j - 1]);
            }
        }
        return;
    } else if (n <= MEDIAN_OF_3_CUTOFF) { // median-of-3 pivot
        It m = median3(st, st + n / 2, en - 1);
        swap(*st, *m);
    } else { // Tukey ninther pivot
        int eps = n / 8;
        It mid = st + n / 2;
        It ninther = median3(median3(st, st + eps, st + eps + eps),
                median3(mid - eps, mid, mid + eps),
                median3(en - 1 - eps - eps, en - 1 - eps, en - 1));
        swap(*st, *ninther);
    }
    // Bentley-McIlroy 3-way partitioning
    int i = 0, j = n, p = 0, q = n;
    auto v = st[0];
    while (true) {
        while (st[++i] < v) if (i == n - 1) break;
        while (v < st[--j]) if (j == 0) break;
        if (i == j && st[i] == v) swap(st[++p], st[i]);
        if (i >= j) break;
        swap(st[i], st[j]);
        if (st[i] == v) swap(st[++p], st[i]);
        if (st[j] == v) swap(st[--q], st[j]);
    }
    i = j + 1;
    for (int k = 0; k <= p; k++, j--) swap(st[k], st[j]);
    for (int k = n - 1; k >= q; k--, i++) swap(st[k], st[i]);
    sort(st, st + j + 1);
    sort(st + i, en);
}

#define MAXN 1000005

int N, A[MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) cin >> A[i];
    quick_sort(A, A + N);
    int ans = INT_INF;
    FOR(i, N - 1) MIN(ans, A[i + 1] - A[i]);
    cout << ans << nl;
    return 0;
}
