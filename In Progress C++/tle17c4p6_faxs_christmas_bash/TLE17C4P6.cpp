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

template <typename T>
struct FenwickTree {
private:
    int size;
    T *array;

public:
    FenwickTree(int size) {
        this->size = size;
        array = new T[size + 1];
        for (int i = 0; i <= size; i++) {
            array[i] = 0;
        }
    }

    /**
     * Range Sum query from 1 to ind
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind index
     * @return sum
     */
    T rsq(int ind) {
        T sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    /**
     * Range Sum Query from a to b.
     * Search for the sum from array index from a to b
     * a and b are 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  a left index
     * @param  b right index
     * @return sum
     */
    T rsq(int a, int b) {
        return rsq(b) - rsq(a - 1);
    }

    /**
     * Update the array at ind and all the affected regions above ind.
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind   index
     * @param  value value
     */
    void update(int ind, T value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    int getSize() {
        return size;
    }
};
const ld EPS = 1e-4;

/**
 * Performs ternary search to find the minimum of a function.
 *
 * @param f the function
 * @param lo the starting x value
 * @param hi the ending x value
 * @returns a pair containing the x value at the minimum of the function, and the minimum value of the function.
 */
pair<ld, ld> ternary_search(ld (*f)(ld), ld lo, ld hi) {
    ld m1, m2;
    do {
        m1 = lo + (hi - lo) / 3;
        m2 = lo + (hi - lo) * 2 / 3;
        if (f(m1) < f(m2)) hi = m2; // change to f(m1) < f(m2) for minimum, f(m1) > f(m2) for maximum
        else lo = m1;
    } while (abs(hi - lo) >= EPS);
    if (abs(lo) < EPS) lo = 0.0;
    return make_pair(lo, f(lo));
}

#define MAXX 15010

FenwickTree<ll> cube(MAXX * 2), quad(MAXX * 2), lin(MAXX * 2), con(MAXX * 2);

ld f(ld x) {
    int below = (int) floor(x);
    int above = (int) ceil(x);
    ld ret = 0.0;
    ret += ((((con.rsq(1, below + MAXX) - con.rsq(above + MAXX, MAXX * 2)) * x + 3.0 * (lin.rsq(above + MAXX, MAXX * 2) - lin.rsq(1, below + MAXX))))
            * x + 3.0 * (quad.rsq(1, below + MAXX) - quad.rsq(above + MAXX, MAXX * 2))) * x + (cube.rsq(above + MAXX, MAXX * 2) - cube.rsq(1, below + MAXX));
    return ret;
}

int N;

int main() {
    ri(N);
    int x;
    FOR(i, N) {
        ri(x);
        cube.update(x + MAXX, (ll) x * (ll) x * (ll) x);
        quad.update(x + MAXX, (ll) x * (ll) x);
        lin.update(x + MAXX, (ll) x);
        con.update(x + MAXX, 1);
        printf("%.4Lf\n", ternary_search(f, -15000.0, 15000.0).f);
    }
    return 0;
}
