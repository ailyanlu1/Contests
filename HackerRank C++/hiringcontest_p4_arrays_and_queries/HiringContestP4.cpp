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

#define MAXN 300005
#define MOD ((ll) (1e9) + 7)

int N, Q, arr[MAXN];
ll ans = 0, tot = 0, final = 0;
map<int, pair<int, int>> A;

void update(int id, int val, int inc) {
    bool removed = false;
    if (inc == 1) {
        arr[id] = val;
        if (A.count(val)) {
            tot = (tot + MOD - A[val].s) % MOD;
            A[val] = {A[val].f + 1, 0};
        } else {
            A[val] = {1, 0};
        }
    } else {
        tot = (tot + MOD - A[val].s) % MOD;
        A[val] = {A[val].f - 1, 0};
        if (A[val].f == 0) {
            removed = true;
            A.erase(val);
        }
    }
    auto lb = A.lower_bound(val);
    auto cur = removed ? A.begin() : lb;
    if (!removed && cur != A.begin()) {
        auto pre = prev(cur);
        if (cur->f - pre->f > 1) cur->s.s = pre->s.f % MOD;
        else if (cur->s.f < pre->s.f) cur->s.s = (pre->s.f - cur->s.f) % MOD;
        else cur->s.s = 0;
        tot = (tot + cur->s.s) % MOD;
    }
    auto nxt = removed ? lb : next(cur);
    if (removed && lb != A.begin()) {
        cur = prev(lb);
    }
    if (removed && lb == A.begin()) {
        tot = (tot + MOD - lb->s.s) % MOD;
        lb->s.s = 0;
        return;
    }
    if (nxt == A.end()) {
        tot = (tot + MOD - final) % MOD;
        final = cur->s.f % MOD;
        tot = (tot + final) % MOD;
    } else {
        tot = (tot + MOD - nxt->s.s) % MOD;
        if (nxt->f - cur->f > 1) nxt->s.s = cur->s.f % MOD;
        else if (nxt->s.f < cur->s.f) nxt->s.s = (cur->s.f - nxt->s.f) % MOD;
        else nxt->s.s = 0;
        tot = (tot + nxt->s.s) % MOD;
    }
}

int main() {
    ri(N);
    int a;
    For(i, 1, N + 1) {
        ri(a);
        update(i, a, 1);
    }
    ri(Q);
    int id, val;
    For(i, 1, Q + 1) {
        ri(id);
        ri(val);
        update(id, arr[id], -1);
        update(id, val, 1);
        ans = (ans + (i * tot) % MOD) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}
