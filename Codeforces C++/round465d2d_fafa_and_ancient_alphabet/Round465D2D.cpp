// http://codeforces.com/contest/935/problem/D
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
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl "\n"

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

#define MAXN 100005
#define MOD ((ll) (1e9 + 7))

ll pow3(ll base, ll pow, ll mod) {
    if (pow == 0) return 1;
    if (pow == 1) return base;
    if (pow % 2 == 0) return pow3(base * base % mod, pow / 2, mod);
    return base * pow3(base * base % mod, pow / 2, mod) % mod;
}

ll divMod(ll i, ll j, ll p) {
    return i * pow3(j, p - 2, p) % p;
}

int N, S[MAXN], T[MAXN];
ll M, E = 1, P = 0, Q = 1;
int eq = 0;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    FOR(i, N) cin >> S[i];
    FOR(i, N) cin >> T[i];
    FOR(i, N) {
        if (S[i] == 0 && T[i] == 0) {
            Q = Q * M % MOD * M % MOD;
            if (eq == 0) {
                P = (E * ((M * (M - 1) / 2) % MOD) + P * (M * M % MOD) % MOD) % MOD;
                E = (E * M) % MOD;
            } else P = P * ((M * M) % MOD) % MOD;
        } else if (S[i] == 0) {
            Q = Q * M % MOD;
            if (eq == 0) P = (E * (M - T[i]) % MOD + P * M % MOD) % MOD;
            else P = P * M % MOD;
        } else if (T[i] == 0) {
            Q = Q * M % MOD;
            if (eq == 0) P = (E * (S[i] - 1) % MOD + P * M % MOD) % MOD;
            else P = P * M % MOD;
        } else if (eq == 0 && S[i] != T[i]) {
            if (S[i] > T[i]) {
                P = (P + E) % MOD;
                eq = 1;
            } else {
                eq = -1;
            }
        }
    }
    cout << divMod(P, Q, MOD) << nl;
    return 0;
}
