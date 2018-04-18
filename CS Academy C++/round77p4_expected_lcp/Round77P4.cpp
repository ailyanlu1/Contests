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

int N;
const ll BASE1 = 10007;
const ll BASE2 = 137;
const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1e9 + 9;
umap<ll, ll> cnt1, cnt2;
ll ans = 0;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    string s;
    FOR(i, N) {
        cin >> s;
        ll h1 = 0, h2 = 0;
        FOR(j, sz(s)) {
            h1 = (h1 * BASE1 + (s[j] - 'a' + 1)) % MOD1;
            h2 = (h2 * BASE2 + (s[j] - 'a' + 1)) % MOD2;
            ans += min(cnt1[h1], cnt2[h2]);
            cnt1[h1]++;
            cnt2[h2]++;
        }
    }
    cout << fixed << setprecision(9) << (double) ans / ((ll) N * (N - 1) / 2) << nl;
    return 0;
}
