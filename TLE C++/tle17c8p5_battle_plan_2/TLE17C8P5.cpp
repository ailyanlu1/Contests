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

#define MAXN 200005
#define LGN 20
#define MAXQ 100005
#define MAXK 55

int N, K, Q, A[MAXN], B[MAXK], ans[MAXQ], dp[MAXN][LGN];
ll preA[MAXN];
vector<pair<pii, int>> queries[MAXK];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K >> Q;
    FOR(i, N) {
        cin >> A[i];
        preA[i] = (i == 0 ? 0 : preA[i - 1]) + A[i];
    }
    FOR(i, K) cin >> B[i];
    FOR(i, Q) {
        int j, l, r;
        cin >> j >> l >> r;
        j--; l--; r--;
        queries[j].pb({{l, r}, i});
    }
    int lg;
    for (lg = 0; (1 << lg) < N; lg++);
    FOR(k, K) {
        FOR(i, N) dp[i][0] = upper_bound(preA + i, preA + N, (i == 0 ? 0 : preA[i - 1]) + B[k]) - preA;
        For(j, 1, lg) FOR(i, N) dp[i][j] = dp[i][j - 1] == N ? N : dp[dp[i][j - 1]][j - 1];
        FOR(i, sz(queries[k])) {
            int cur = queries[k][i].f.f;
            ll cost = 0;
            int en = queries[k][i].f.s + 1;
            REV(j, lg - 1) {
                if (dp[cur][j] == cur) break;
                if (dp[cur][j] < en) {
                    cur = dp[cur][j];
                    cost += 1 << j;
                }
            }
            if (dp[cur][0] >= en) ans[queries[k][i].s] = cost + 1;
            else ans[queries[k][i].s] = -1;
        }
    }
    FOR(i, Q) cout << ans[i] << nl;
    return 0;
}
