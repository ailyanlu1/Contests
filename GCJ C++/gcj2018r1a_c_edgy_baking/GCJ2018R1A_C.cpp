// https://codejam.withgoogle.com/2018/challenges/0000000000007883/dashboard/000000000002fff7
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

#define MAXN 105

int T, N, P, W[MAXN], H[MAXN];
umap<int, double> dp;

void solve(int t) {
    dp.clear();
    cin >> N >> P;
    int curP = 0;
    FOR(i, N) {
        cin >> W[i] >> H[i];
        curP += (W[i] + H[i]) * 2;
    }
    dp[curP] = curP;
    FOR(i, N) {
        vector<pair<int, double>> cur;
        for (pair<int, double> p : dp) cur.pb(p);
        for (pair<int, double> p : cur) {
            int a = p.f + min(W[i], H[i]) * 2;
            double b = p.s + sqrt(W[i] * W[i] + H[i] * H[i]) * 2;
            if (a > P) continue;
            if (!dp.count(a)) dp[a] = b;
            else MAX(dp[a], b);
        }
    }
    double ans = 0;
    for (pair<int, double> p : dp) MAX(ans, p.s);
    MIN(ans, (double) P);
    cout << fixed << setprecision(7) << "Case #" << t << ": " << ans << nl;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(i, T) solve(i + 1);
    return 0;
}
