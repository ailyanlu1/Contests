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

const double PI = 3.14159265358979323846;

void getRoots(int N, vector<complex<double>> &out) {
    for (int i = 0; i < N; i++) out.push_back(polar(1.0, 2.0 * PI * i / N));
}

template<typename T> void fft(T *in, complex<double> *out, vector<complex<double>> &roots, int len, int step = 1) {
    if (len == 1) *out = *in;
    else {
        fft(in, out, roots, len / 2, step * 2); // even
        fft(in + step, out + len / 2, roots, len / 2, step * 2); // odd
        for (int i = 0, j = 0; i < len / 2; i++, j += step) {
            auto temp = out[i + len / 2] * roots[j];
            out[i + len / 2] = out[i] - temp;
            out[i] += temp;
        }
    }
}

template<typename T> void fft(vector<T> &in, vector<complex<double>> &out, vector<complex<double>> &roots) {
    assert(in.size() == out.size());
    int N = (int) in.size();
    assert(!(N & (N - 1)));
    fft(in.data(), out.data(), roots, N);
}

template<typename T> void invfft(vector<T> &in, vector<complex<double>> &out, vector<complex<double>> &invRoots) {
    assert(in.size() == out.size());
    int N = (int) in.size();
    assert(!(N & (N - 1)));
    fft(in, out, invRoots);
    for (int i = 0; i < N; i++) out[i] *= (1.0 / N);
}

template<typename T> void convolve(vector<T> &a, vector<T> &b, vector<complex<double>> &out) {
    assert(a.size() == b.size() && a.size() == out.size());
    int N = (int) a.size();
    assert(!(N & (N - 1)));
    vector<complex<double>> x(N), y(N), roots;
    getRoots(N, roots);
    fft(a, x, roots);
    fft(b, y, roots);
    for (int i = 0; i < N; i++) {
        x[i] *= y[i];
        roots[i] = conj(roots[i]);
    }
    invfft(x, y, roots);
    for (int i = 0; i < N; i++) out[i] = y[i];
}

void multiplyInteger(vector<int> a, vector<int> b, vector<int> &out) {
    int N = (int) (a.size()) + (int) (b.size());
    while (N & (N - 1)) N++;
    a.resize(N);
    b.resize(N);
    vector<complex<double>> c(N);
    convolve(a, b, c);
    out.resize(N);
    for (int i = 0; i < N; i++) out[i] = (int) round(real(c[i]));
    for (int i = 0; i < (int) (out.size()); i++) {
        if (out[i] >= 10) {
            if (i == (int) (out.size()) - 1) out.push_back(out[i] / 10);
            else out[i + 1] += out[i] / 10;
            out[i] %= 10;
        }
    }
    while ((int) (out.size()) > 1 && out.back() == 0) out.pop_back();
}

int main() {
    vector<int> A, B, ans;
    char c;
    while (true) {
        scanf("%c", &c);
        if (isspace(c)) break;
        A.pb(c - '0');
    }
    while (true) {
        scanf("%c", &c);
        if (isspace(c)) break;
        B.pb(c - '0');
    }
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    multiplyInteger(A, B, ans);
    reverse(ans.begin(), ans.end());
    for (int x : ans) printf("%d", x);
    printf("\n");
    return 0;
}
