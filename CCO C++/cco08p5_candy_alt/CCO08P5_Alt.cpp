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

#define MAXNKC 5000005

int N, tot = 0, dp[MAXNKC];
bool bit[MAXNKC];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int k, c;
    FOR(j, MAXNKC) bit[j] = false;
    bit[0] = true;
    FOR(i, N) {
        cin >> k >> c;
        tot += k * c;
        memset(dp, 0, sizeof(dp));
        For(j, c, MAXNKC) {
            if (bit[j]) continue;
            bit[j] = bit[j] || (bit[j - c] && dp[j - c] + 1 <= k);
            if (bit[j - c]) dp[j] = dp[j - c] + 1;
        }
    }
    REV(i, tot / 2) {
        if (bit[i]) {
            cout << tot - i * 2 << nl;
            return 0;
        }
    }
    return 0;
}
