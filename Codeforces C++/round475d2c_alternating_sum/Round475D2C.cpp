// http://codeforces.com/contest/964/problem/C
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

const ll MOD = 1e9 + 9;

ll N, A, B, C, AN, S[100005];
int K;
string SS;

ll pow3(ll base, ll pow, ll mod) {
    if (pow == 0) return 1;
    if (pow == 1) return base;
    if (pow % 2 == 0) return pow3(base * base % mod, pow / 2, mod);
    return base * pow3(base * base % mod, pow / 2, mod) % mod;
}

ll divMod(ll i, ll j, ll p) {
    return i * pow3(j, p - 2, p) % p;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> A >> B >> K >> SS;
    C = (N + 1) / K;
    FOR(i, K) S[i] = SS[i] == '+' ? 1 : MOD - 1;
    AN = pow3(A, N, MOD) % MOD;
    ll d = divMod(B, A, MOD) % MOD;
    ll dk = pow3(d, K, MOD) % MOD;
    ll dkc = pow3(dk, C, MOD) % MOD;
    ll sumC = dk == 1 ? C : divMod((1 - dkc) % MOD + MOD, (1 - dk) % MOD + MOD, MOD);
    ll ans = 0;
    FOR(i, K) {
        ll cur = S[i] * AN % MOD;
        cur = cur * pow3(d, i, MOD) % MOD;
        cur = cur * sumC % MOD;
        ans = (ans + cur) % MOD;
    }
    cout << ans << nl;
    return 0;
}
