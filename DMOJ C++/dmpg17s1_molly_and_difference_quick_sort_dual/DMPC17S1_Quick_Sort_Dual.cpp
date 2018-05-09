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

template <typename It> void quick_sort_dual(It st, It en) {
    int n = en - st;
    if (n <= 1) return;
    if (n <= INSERTION_SORT_CUTOFF) { // insertion sort
        for (int i = 0; i < n; i++) {
            for (int j = i; j > 0 && st[j] < st[j - 1]; j--) {
                swap(st[j], st[j - 1]);
            }
        }
        return;
    }
    if (st[n - 1] < st[0]) swap(st[0], st[n - 1]);
    int lt = 1, gt = n - 2, i = 1;
    while (i <= gt) {
        if (st[i] < st[0]) swap(st[i++], st[lt++]);
        else if (st[n - 1] < st[i]) swap(st[i], st[gt--]);
        else i++;
    }
    swap(st[0], st[--lt]);
    swap(st[n - 1], st[++gt]);
    sort(st, st + lt);
    if (st[lt] < st[gt]) sort(st + lt + 1, st + gt);
    sort(st + gt + 1, en);
}

#define MAXN 1000005

int N, A[MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) cin >> A[i];
    quick_sort_dual(A, A + N);
    int ans = INT_INF;
    FOR(i, N - 1) MIN(ans, A[i + 1] - A[i]);
    cout << ans << nl;
    return 0;
}
