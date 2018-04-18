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

#define MAXM 100005

int M;
ll A[2][MAXM], dp[2][MAXM][2];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> M;
    FOR(i, 2) FOR(j, M) cin >> A[i][j];
    dp[0][M - 1][0] = dp[0][M - 1][1] = A[0][M - 1] + A[1][M - 1];
    dp[1][M - 1][0] = dp[1][M - 1][1] = A[1][M - 1];
    REV(j, M - 2) {
        FOR(i, 2) {
            dp[i][j][0] = min(dp[i ^ 1][j + 1][0] + A[0][j] + A[1][j], dp[i][j + 1][1] + A[i][j]);
            dp[i][j][1] = max(dp[i ^ 1][j + 1][1] + A[0][j] + A[1][j], dp[i][j + 1][0] + A[i][j]);
        }
    }
    cout << dp[0][0][0] << nl;
    return 0;
}
