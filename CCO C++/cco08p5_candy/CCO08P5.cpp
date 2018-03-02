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

#define MAXN 105
#define MAXK 505
#define MAXC 205

int N, K[MAXN], C[MAXN], ans = INT_MAX;
bool dp[2][MAXC * 2];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) cin >> K[i] >> C[i];
    FOR(j, MAXC * 2) dp[0][j] = dp[1][j] = false;
    dp[1][MAXC] = true;
    int m = 0;
    FOR(i, N) {
        FOR(j, K[i]) {
            FOR(k, MAXC * 2) dp[m % 2][k] = false;
            FOR(k, MAXC * 2 - C[i]) dp[m % 2][k] |= dp[1 - m % 2][k + C[i]];
            For(k, C[i], MAXC * 2) dp[m % 2][k] |= dp[1 - m % 2][k - C[i]];
            m++;
        }
    }
    FOR(k, MAXC * 2) if (dp[(m - 1) % 2][k]) MIN(ans, abs(MAXC - k));
    cout << ans << nl;
    return 0;
}
