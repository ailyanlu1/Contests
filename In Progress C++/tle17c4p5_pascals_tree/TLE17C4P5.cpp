#include <bits/stdc++.h>

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
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define SET0(a) memset((a), 0, sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<int, double> pid;
typedef pair<double, int> pdi;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef pair<llu, llu> pllu;
typedef pair<int, llu> pillu;
typedef pair<llu, int> pllui;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef map<ll, ll> mll;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;
typedef unordered_map<ll, ll> umll;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXN 200010

long long pow3(long long base, long long pow, long long mod) {
    if (pow == 0) return 1;
    if (pow == 1) return base;
    if (pow % 2 == 0) return pow3(base * base % mod, pow / 2, mod);
    return base * pow3(base * base % mod, pow / 2, mod) % mod;
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

umll A;

ll ncrModPE(ll n, ll k, ll p, ll e, ll a) {
    ll pe = 1;
    for (ll i = 0LL; i < e; i++) pe *= p;
    ll r = n - k;
    ll num = 1, den = 1, neg = 0, dig = 0;
    while (n > 0) {
        if (a != 1 && dig >= e) neg = neg ^ (n & 1) ^ (k & 1) ^ (r & 1);
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

ll ncrPE(ll n, ll k, ll p, ll e, ll a) {
    ll pe = 1;
    for (ll i = 0LL; i < e; i++) pe *= p;
    ll pp = cntDig(n, p) - cntDig(k, p) - cntDig(n - k, p);
    if (pp >= e) return 0;
    ll ret = ncrModPE(n, k, p, e - pp, a);
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

void solve5(int n, ll m) {
    factor(m);
    ll prod = 1;
    FOR(i, (int) pfProd.size()) prod *= pfProd[i];
    FOR(i, (int) pfProd.size()) {
        FOR(j, n + 1) T[j] = j;
        ll pe = 1;
        for (ll j = 0LL; j < pf[i].s; j++) pe *= pf[i].f;
        ll tn = n;
        while (tn > 0) {
            A[tn % pe] = -1;
            tn /= pf[i].f;
            FOR(j, n + 1) {
                A[T[j] % pe] = -1;
                T[j] /= pf[i].f;
            }
        }
        ll a = 1LL;
        for (ll j = 0LL; j < pe; j++) {
            ll x = j % pf[i].f == 0 ? 1LL : j;
            a = a * x % pe;
            if (A.count(j)) A[j] = a;
        }
        FOR(r, n + 1) {
            ll c = ncrPE(n, r, pf[i].f, pf[i].s, a);
            ll y = prod / pfProd[i];
            ans[r] = (ans[r] + (((c * y) % prod) * (multInv(y, pfProd[i]) % prod)) % prod) % prod;
        }
    }
    FOR(r, n + 1) {
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
    SET0(row);
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

long long divMod(long long i, long long j, long long p) {
    return i * pow3(j, p - 2, p) % p;
}

ll fact[MAXN];

long long fastChoose(int n, int k, int p) {
    return divMod(divMod(fact[n], fact[k], p), fact[n - k], p);
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
    else if (N <= 2200) solve2(N, M);
    else if (M == 1e8 + 7) solve3(N, M);
    else solve5(N, M);
    return 0;
}
