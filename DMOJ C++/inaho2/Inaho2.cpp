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

#define MAXN 10
#define MAXPROD 10000000

int N, Q, BIT[MAXPROD], L[MAXN], sufProd[MAXN], A[MAXN], B[MAXN];
unsigned char ARR[MAXPROD];

void init() {
    int prod = 1;
    for (int i = N - 1; i >= 0; i--) {
        sufProd[i] = prod;
        prod *= L[i];
    }
}

int rsq(int curDim, int pos) {
    int sum = 0;
    if (curDim == N) {
        sum += BIT[pos];
    } else {
        for (int i = B[curDim]; i > 0; i -= (i & -i)) {
            sum += rsq(curDim + 1, pos + (i - 1) * sufProd[curDim]);
        }
        for (int i = A[curDim] - 1; i > 0; i -= (i & -i)) {
            sum -= rsq(curDim + 1, pos + (i - 1) * sufProd[curDim]);
        }
    }
    return sum;
}

void update(int curDim, int pos, int value) {
    if (curDim == N) {
        BIT[pos] += value;
    } else {
        for (int i = A[curDim]; i <= L[curDim]; i += (i & -i)) {
            update(curDim + 1, pos + (i - 1) * sufProd[curDim], value);
        }
    }
}

//void generate();

int main() {
//    generate();
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
//    const auto start_time = chrono::system_clock::now();
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    FOR(i, N) cin >> L[i];
    init();
    int op, pos, x;
    FOR(q, Q) {
        cin >> op;
        if (op == 1) {
            pos = 0;
            FOR(i, N) {
                cin >> A[i];
                pos += (A[i] - 1) * sufProd[i];
            }
            cin >> x;
            update(0, 0, x - ARR[pos]);
            ARR[pos] = x;
        } else if (op == 2) {
            FOR(i, N) cin >> A[i];
            FOR(i, N) cin >> B[i];
            cout << rsq(0, 0) << '\n';
        } else {
            q--;
        }
    }
//    double time_elapsed = ((chrono::system_clock::now() - start_time).count() / static_cast<double>(chrono::system_clock::period::den));
//    fprintf(stderr, "Completed in %.3f seconds.\n", time_elapsed);
    return 0;
}
