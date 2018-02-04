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

#define MAXN 100010
#define MAXK 10
#define MOD ((ll) (1e9 + 7))

int N, Q;

long long pow3(long long base, long long pow, long long mod) {
    if (pow == 0) return 1;
    if (pow == 1) return base;
    if (pow % 2 == 0) return pow3(base * base % mod, pow / 2, mod);
    return base * pow3(base * base % mod, pow / 2, mod) % mod;
}

long long divMod(long long i, long long j, long long p) {
    return i * pow3(j, p - 2, p) % p;
}

struct FenwickTreePolynomial {
private:
    int size, maxK;
    long long mod;
    vector<vector<long long>> BIT;
    vector<vector<long long>> cof {{0, 1},
                                   {0, 1, 1},
                                   {0, 1, 3, 2},
                                   {0, 0, 6, 12, 6},
                                   {0, -4, 0, 40, 60, 24},
                                   {0, 0, -60, 0, 300, 360, 120},
                                   {0, 120, 0, -840, 0, 2520, 2520, 720},
                                   {0, 0, 3360, 0, -11760, 0, 23520, 20160, 5040},
                                   {0, -12096, 0, 80640, 0, -169344, 0, 241920, 181440, 40320},
                                   {0, 0, -544320, 0, 1814400, 0, -2540160, 0, 2721600, 1814400, 362880},
                                   {0, 3024000, 0, -19958400, 0, 39916800, 0, -39916800, 0, 33264000, 19958400, 3628800}};
    vector<vector<vector<long long>>> sumDiff;
    vector<long long> factorial;
    vector<vector<long long>> pascal;

    long long rsq(vector<long long> &array, int ind) {
        long long sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) sum = (sum + array[x]) % mod;
        return sum;
    }

    void update(vector<long long> &array, int ind, long long value) {
        value %= mod;
        for (int x = ind; x <= size; x += (x & -x)) array[x] = (array[x] + value) % mod;
    }

public:
    FenwickTreePolynomial(int size, int maxK, long long modbigPrime) : size(size), maxK(maxK), mod(modbigPrime), BIT(maxK + 2), sumDiff(maxK + 1), pascal(maxK + 2) {
        assert(maxK >= 0 && maxK <= 10);
        factorial.push_back(1);
        for (int i = 1; i < maxK + 2; i++) factorial.push_back(factorial.back() * i);
        for (int i = 0; i < maxK + 2; i++) for (int j = 0; j <= size; j++) BIT[i].push_back(0);
        for (int k = 0; k < maxK + 1; k++) {
            for (int i = 0; i < maxK + 2; i++) {
                sumDiff[k].push_back(vector<long long>());
                for (int j = 0; j < maxK + 2 - i; j++) sumDiff[k][i].push_back(0);
            }
        }
        for (int i = 0; i < maxK + 2; i++) {
            pascal[i].push_back(1);
            for (int j = 1; j <= i; j++) pascal[i].push_back(pascal[i].back() * (i - j + 1) / j);
        }
        for (int k = 0; k < maxK + 1; k++) {
            for (int i = 0; i < k + 2; i++) {
                int sign = 1;
                for (int j = 0; j <= i; j++) {
                    sumDiff[k][i - j][j] = (sumDiff[k][i - j][j] + (((cof[k][i] * pascal[i][j]) % mod * (factorial[maxK + 1] / factorial[k + 1])) % mod) * sign) % mod;
                    sign = -sign;
                }
            }
        }
    }

    long long rsq(int ind) {
        long long sum = rsq(BIT[maxK + 1], ind);
        for (int i = maxK; i >= 0; i--) sum = ((sum * ind) % mod + rsq(BIT[i], ind)) % mod;
        if (sum < 0) sum += mod;
        sum = divMod(sum, factorial[maxK + 1], mod);
        return sum;
    }

    long long rsq(int a, int b) {
        long long sum = (rsq(b) - rsq(a - 1)) % mod;
        if (sum < 0) sum += mod;
        return sum;
    }

    void update(int a, int b, long long value, int k) {
        value %= mod;
        long long s = a - 1, len = b - a + 1, mult;
        for (int i = 0; i < k + 2; i++) {
            mult = sumDiff[k][i][k + 1 - i];
            for (int j = k - i; j >= 0; j--) mult = ((mult * s) % mod + sumDiff[k][i][j]) % mod;
            update(BIT[i], a, value * mult % mod);
            update(BIT[i], b + 1, -value * mult % mod);
        }
        mult = cof[k][k + 1];
        for (int i = k; i >= 0; i--) mult = ((mult * len) % mod + cof[k][i]) % mod;
        if (mult < 0) mult += mod;
        mult = (mult * (factorial[maxK + 1] / factorial[k + 1])) % mod;
        update(BIT[0], b + 1, value * mult % mod);
    }

    int getSize() {
        return size;
    }
};

FenwickTreePolynomial *ft;

int main() {
    ri(N);
    ft = new FenwickTreePolynomial(N, MAXK, MOD);
    ri(Q);
    char op;
    int l, r, k;
    FOR(i, Q) {
        rc(op);
        if (op == 'U') {
            ri(l);
            ri(r);
            ri(k);
            ft->update(l, r, 1, k);
        } else if (op == 'Q') {
            ri(l);
            ri(r);
            printf("%lld\n", ft->rsq(l, r) % MOD);
        } else {
            i--;
        }
    }
    return 0;
}
