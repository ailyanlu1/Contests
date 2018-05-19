// http://www.spoj.com/problems/MKTHNUM/
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

#define MAXN 100005

int N, M, A[MAXN];
pii B[MAXN];
vector<int> T[2 * MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    For(i, 1, N + 1) {
        cin >> A[i];
        B[i - 1] = {A[i], i};
    }
    sort(B, B + N);
    FOR(i, N) T[N + i].pb(A[i + 1]);
    Rev(i, N - 1, 0) merge(all(T[i << 1]), all(T[i << 1 | 1]), back_inserter(T[i]));
    int a, b, k, ans;
    FOR(i, M) {
        cin >> a >> b >> k;
        k--;
        int lo = 0, hi = N - 1, mid, ans;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            ans = 0;
            for (int l = a + N - 1, r = b + N - 1; l <= r; l >>= 1, r >>= 1) {
                if (l & 1) {
                    ans += lower_bound(all(T[l]), B[mid].f) - T[l].begin();
                    l++;
                }
                if (!(r & 1)) {
                    ans += lower_bound(all(T[r]), B[mid].f) - T[r].begin();
                    r--;
                }
            }
            if (ans == k) {
                if (B[mid].s >= a && B[mid].s <= b) break;
                lo = mid + 1;
            } else if (ans < k) lo = mid + 1;
            else hi = mid - 1;
        }
        cout << B[mid].f << nl;
    }
    return 0;
}
