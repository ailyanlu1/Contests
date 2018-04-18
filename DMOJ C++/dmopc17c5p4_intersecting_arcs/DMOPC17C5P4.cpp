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

#define MAXN 505
const ll MOD = 1e9 + 7;

int N, K;
ll dp[2][MAXN][MAXN];

inline ll query(int i, int j, int kl, int kr) {
    if (j < 0 || j > N) return 0;
    if (kl <= 0) return dp[i][j][kr];
    return (dp[i][j][kr] - dp[i][j][kl - 1] + MOD) % MOD;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    FOR(k, K + 1) dp[0][0][k] = 1;
    For(i, 1, N + 1) {
        FOR(j, i + 1) {
            FOR(k, K + 1) {
                dp[i % 2][j][k] = (query(1 - i % 2, j, k, k) + query(1 - i % 2, j - 1, k, k) + query(1 - i % 2, j + 1, k - j, k)) % MOD;
                if (k > 0) dp[i % 2][j][k] = (dp[i % 2][j][k] + dp[i % 2][j][k - 1]) % MOD;
            }
        }
    }
    cout << query(N % 2, 0, K, K) << nl;
    return 0;
}
