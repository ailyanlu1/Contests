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

#define CUTOFF ((ll) 1e6 + 5)
#define MAXA ((ll) 1e12 + 5)

string S, T;
int Q;
vector<int> line;
vector<ll> A;
vector<vector<ll>> SIND, TIND;
vector<pll> SZ;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> S >> T >> Q;
    ll a, maxA = 0;
    FOR(q, Q) {
        cin >> a;
        a--;
        MAX(maxA, a);
        A.pb(a);
    }
    if (maxA < CUTOFF) {
        int curInd = 0;
        line.pb(0);
        while (sz(line) < CUTOFF) {
            if (line[curInd] == 0) FOR(i, len(S)) line.pb(S[i] - '0');
            else FOR(i, len(T)) line.pb(T[i] - '0');
            curInd++;
        }
        FOR(q, Q) {
            cout << line[A[q]] << '\n';
        }
    } else if (len(S) != len(T)) {
        SZ.pb({1, 1});
        SZ.pb({len(S), len(T)});
        while (SZ.back().f < MAXA) {
            ll s = 0, t = 0;
            FOR(i, len(S)) {
                if (S[i] == '0') s += SZ.back().f;
                else s += SZ.back().s;
            }
            FOR(i, len(T)) {
                if (T[i] == '0') t += SZ.back().f;
                else t += SZ.back().s;
            }
            SZ.pb({s, t});
        }
        ll start = 0;
        FOR(i, sz(SZ) - 1) start += SZ[i].f;
        FOR(q, Q) {
            bool type = 0;
            ll cur = start;
            Rev(i, sz(SZ) - 1, 0) {
                if (cur > A[q]) {
                    cur -= SZ[i - 1].f;
                    continue;
                }
                ll ind = (A[q] - cur) / SZ[i - 1].f;
                cur += ind * SZ[i - 1].f;
                type = (type ? T[ind] : S[ind]) - '0';
            }
            cout << type << '\n';
        }
    } else {
        SZ.pb({1, 1});
        SZ.pb({len(S), len(T)});
        while (SZ.back().f < MAXA) {
            ll s = 0, t = 0;
            FOR(i, len(S)) {
                if (S[i] == '0') s += SZ.back().f;
                else s += SZ.back().s;
            }
            FOR(i, len(T)) {
                if (T[i] == '0') t += SZ.back().f;
                else t += SZ.back().s;
            }
            SZ.pb({s, t});
        }
        ll start = 0;
        FOR(i, sz(SZ) - 1) start += SZ[i].f;
        SIND.pb(vector<ll>());
        TIND.pb(vector<ll>());
        For(i, 1, sz(SZ)) {
            ll curS = 0, curT = 0;
            SIND.pb(vector<ll>());
            for (int j = 0; j < len(S); j++) {
                SIND.back().pb(curS);
                curS += S[j] == '0' ? SZ[i - 1].f : SZ[i - 1].s;
            }
            TIND.pb(vector<ll>());
            for (int j = 0; j < len(T); j++) {
                TIND.back().pb(curT);
                curT += T[j] == '0' ? SZ[i - 1].f : SZ[i - 1].s;
            }
        }
        FOR(q, Q) {
            bool type = 0;
            ll cur = start;
            Rev(i, sz(SZ) - 1, 0) {
                if (cur > A[q]) {
                    cur -= SZ[i - 1].f;
                    continue;
                }
                ll ind;
                if (type == 0) {
                    auto ss = prev(upper_bound(SIND[i].begin(), SIND[i].end(), A[q] - cur));
                    ind = ss - SIND[i].begin();
                    cur += *ss;
                } else {
                    auto tt = prev(upper_bound(TIND[i].begin(), TIND[i].end(), A[q] - cur));
                    ind = tt - TIND[i].begin();
                    cur += *tt;
                }
                type = (type ? T[ind] : S[ind]) - '0';
            }
            cout << type << '\n';
        }
    }
    return 0;
}
