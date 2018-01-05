#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) ((x) << 1)
#define r(x) ((x) << 1 | 1)
#define m(x, y) ((x) + ((y) - (x)) / 2)
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rld(x) scanf("%Lf", &x)
#define rc(x) scanf(" %c", &x)
#define sc(x) do { scanf("%c", &x); } while (isspace(x))
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define set0(a) memset((a), 0, sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define Fill2(a, x, n, m) FOR(_, n) FOR(__, m) (a)[_][__] = (x)
#define Fill3(a, x, n, m, p) FOR(_, n) FOR(__, m) FOR(___, p) (a)[_][__][___] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))
#define sz(a) ((int) (a).size())
#define len(a) ((int) (a).length())

typedef long long ll;
typedef unsigned long long llu;
typedef long double ld;
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef map<ll, ll> mll;
typedef umap<int, int> umii;
typedef umap<int, ll> umill;
typedef umap<ll, int> umlli;
typedef umap<ll, ll> umll;
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

#define debug(fmt, x) fprintf(stderr, "%d::%s = " fmt, __LINE__, #x, (x)); fflush(stderr)
#define debug2(x) cerr << __LINE__ << "::" << #x << " = " << (x) << '\n' << flush
#define debugva(fmt, ...) fprintf(stderr, "%d::%s = " fmt, __LINE__, #__VA_ARGS__, __VA_ARGS__); fflush(stderr)
#define debugarr(fmt, x, a, b) fprintf(stderr, "%d::%s = {", __LINE__, #x); For(_, a, b) { if (_ != (a)) { fprintf(stderr, ", "); } fprintf(stderr, fmt, (x)[_]); } fprintf(stderr, "}\n"); fflush(stderr)
#define debugarr2(x, a, b) cerr << __LINE__ << "::" << #x << " = {"; For(_, a, b) { if (_ != (a)) { cerr << ", "; } cerr << (x)[_]; } cerr << "}\n" << flush

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXN 200010

long long pow3(long long base, long long pow, long long mod) {
    if (pow == 0) return 1;
    if (pow == 1) return base;
    if (pow % 2 == 0) return pow3(base * base % mod, pow / 2, mod);
    return base * pow3(base * base % mod, pow / 2, mod) % mod;
}

long long divMod(long long i, long long j, long long p) {
    return i * pow3(j, p - 2, p) % p;
}

ll fact[MAXN];

long long fastChoose(int n, int k, int p) {
    return divMod(divMod(fact[n], fact[k], p), fact[n - k], p);
}

ll gcd(ll a, ll b, ll *x, ll *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    ll x1, y1;
    ll g = gcd(b, a % b, &x1, &y1);
    *y = x1 - (a / b) * y1;
    *x = y1;
    return g;
}

ll multInv(ll a, ll p) {
    ll x, y;
    assert(gcd(a, p, &x, &y) == 1);
    return (x % p + p) % p;
}

ll cntDig(ll x, ll y) {
    ll ret = 0;
    while (x > 0) {
        x /= y;
        ret += x;
    }
    return ret;
}

ll A[MAXN];

ll ncrModPE(ll n, ll k, ll p, ll e) {
    ll pe = 1;
    for (ll i = 0LL; i < e; i++) pe *= p;
    ll r = n - k;
    ll num = 1, den = 1, neg = 0, dig = 0;
    while (n > 0) {
        if (dig >= e) neg = neg ^ (n & 1) ^ (k & 1) ^ (r & 1);
        num = (num * A[n % pe]) % pe;
        den = (((den * A[k % pe]) % pe) * A[r % pe]) % pe;
        n /= p;
        k /= p;
        r /= p;
        dig++;
    }
    ll ret = (num % pe) * (multInv(den, pe) % pe) % pe;
    ret = (ret % pe + pe) % pe;
    if ((p != 2 || e < 3) && neg) ret = pe - ret;
    ret = (ret % pe + pe) % pe;
    return ret;
}

ll ncrPE(ll n, ll k, ll p, ll e) {
    ll pe = 1;
    for (ll i = 0LL; i < e; i++) pe *= p;
    ll pp = cntDig(n, p) - cntDig(k, p) - cntDig(n - k, p);
    if (pp >= e) return 0;
    ll ret = ncrModPE(n, k, p, e);
    ret = ret * pow3(p, pp, pe) % pe;
    return ret;
}

vector<pll> pf;
vector<ll> pfProd;

void factor(ll m) {
    for (ll i = 2; i * i <= m; i++) {
        ll e = 0;
        ll prod = 1;
        while (m % i == 0) {
            e++;
            m /= i;
            prod *= i;
        }
        if (e > 0) {
            pf.pb(mp(i, e));
            pfProd.pb(prod);
        }
    }
    if (m > 1) {
        pf.pb(mp(m, 1));
        pfProd.pb(m);
    }
}

ll T[MAXN], ans[MAXN];

void solve5(int N, ll M) {
    fact[0] = 1;
    For(i, 1, N + 1) fact[i] = fact[i - 1] * i % M;
    factor(M);
    ll prod = 1;
    FOR(i, sz(pfProd)) prod *= pfProd[i];
    assert(prod == M);
    FOR(i, sz(pfProd)) {
        FOR(j, N + 1) T[j] = j;
        ll pe = 1;
        for (ll j = 0LL; j < pf[i].s; j++) pe *= pf[i].f;
        ll a = 1LL;
        for (ll j = 0LL; j < min((ll) (N + 1), pe); j++) {
            ll x = j % pf[i].f == 0 ? 1LL : j;
            a = a * x % pe;
            A[j] = a;
        }
        FOR(r, N + 1) {
            ll c = ncrPE(N, r, pf[i].f, pf[i].s);
            ll y = prod / pfProd[i];
            ans[r] = (ans[r] + (((c * y) % prod) * (multInv(y, pfProd[i]) % prod)) % prod) % prod;
        }
    }
    FOR(r, N + 1) {
        printf("%lld\n", ans[r]);
    }
}

void solve1(int N, ll M) {
    ll x = 1;
    FOR(r, N + 1) {
        printf("%lld\n", x % M);
        x = x * (N - r) / (r + 1);
    }
}

void solve2(int N, ll M) {
    ll row[2][N + 1];
    set0(row);
    row[0][0] = 1;
    For(i, 1, N + 1) {
        row[i % 2][0] = 1;
        For(j, 1, i + 1) {
            row[i % 2][j] = (row[1 - i % 2][j] + row[1 - i % 2][j - 1]) % M;
        }
    }
    FOR(j, N + 1) {
        printf("%lld\n", row[N % 2][j]);
    }
}

void solve3(int N, ll M) {
    fact[0] = 1;
    For(i, 1, N + 1) fact[i] = fact[i - 1] * i % M;
    FOR(r, N + 1) {
        printf("%lld\n", fastChoose(N, r, M));
    }
}

int main() {
    int N;
    ll M;
    ri(N);
    rll(M);
    if (N <= 12) solve1(N, M);
    else if (N <= 2010) solve2(N, M);
    else if (M == 1e8 + 7) solve3(N, M);
    else solve5(N, M);
    return 0;
}
