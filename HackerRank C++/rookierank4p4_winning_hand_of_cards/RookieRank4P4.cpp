#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
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
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

int N;
ll M, T;
vector<ll> C;

ll gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1LL;
        y = 0LL;
        return abs(a);
    }
    ll x1, y1;
    ll g = gcd(b, a % b, x1, y1);
    y = x1 - (a / b) * y1;
    x = y1;
    return g;
}

void solveHalf(vector<ll> &half, umap<ll, ll> &prod) {
    For(i, 1, 1 << sz(half)) {
        ll curProd = 1LL;
        FOR(j, sz(half)) if (i & (1 << j)) curProd = (curProd * half[j]) % M;
        prod[curProd]++;
    }
}

ll solve() {
    vector<ll> even, odd;
    FOR(i, N) {
        if (i % 2) odd.pb(C[i]);
        else even.pb(C[i]);
    }
    umap<ll, ll> evenProd, oddProd;
    solveHalf(even, evenProd);
    solveHalf(odd, oddProd);
    ll cnt = evenProd[T] + oddProd[T];
    for (pair<ll, ll> p : evenProd) {
        ll x, y;
        ll g = gcd(p.f, M, x, y);
        if (T % g == 0) {
            x = (x % M + M) % M;
            for (x = (x * T / g) % (M / g); x < M; x += M / g) cnt += p.s * oddProd[x];
        }
    }
    return cnt;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> T;
    ll ci;
    FOR(i, N) {
        cin >> ci;
        C.pb(ci % M);
    }
    cout << solve() << nl;
    return 0;
}
