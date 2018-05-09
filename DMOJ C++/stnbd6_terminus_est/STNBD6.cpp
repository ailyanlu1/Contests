#include <bits/stdc++.h>
using namespace std;

#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define f first
#define s second
#define all(a) (a).begin(), (a).end()
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

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

template<typename T1, typename T2, typename H1 = hash<T1>, typename H2 = hash<T2>>
struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * H1 {}(p.first) + H2 {}(p.second);}};

#define MAXN 100005

int N, Q, maxCnt[MAXN];
bool A[MAXN], exclude[MAXN];
vector<int> adj[MAXN];
ll ans[MAXN];
vector<ll> small, large;

bool maxCntCmp(const int &a, const int &b) {
    return maxCnt[a] < maxCnt[b];
}

int getSize(int v, int prev) {
    int size = 1;
    for (int w : adj[v]) if (w != prev && !exclude[w]) size += getSize(w, v);
    return size;
}

int getCentroid(int v, int prev, int treeSize) {
    int n = treeSize;
    int size = 1;
    bool hasCentroid = true;
    for (int w : adj[v]) {
        if (w == prev || exclude[w]) continue;
        int ret = getCentroid(w, v, treeSize);
        if (ret >= 0) return ret;
        hasCentroid &= -ret <= n / 2;
        size += -ret;
    }
    hasCentroid &= n - size <= n / 2;
    return hasCentroid ? v : -size;
}

void dfs1(int v, int prev, int d) {
    maxCnt[v] = d + A[v];
    for (int w : adj[v]) {
        if (w == prev || exclude[w]) continue;
        dfs1(w, v, d + A[v]);
        MAX(maxCnt[v], maxCnt[w]);
    }
}

void dfs2(int v, int prev, int cnt) {
    small[cnt + A[v]]++;
    for (int w : adj[v]) {
        if (w == prev || exclude[w]) continue;
        dfs2(w, v, cnt + A[v]);
    }
}

const double PI = 3.14159265358979323846;

/**
 * Computes the Nth roots of unity.
 *
 * @param N the root
 * @param out the Nth roots of unity
 */
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

/**
 * Computes the Fast Fourier Transformation of the vector in.
 *
 * @param in the input vector (of any type)
 * @param out the output vector of type complex<double>
 * @param roots the complex roots of unity
 */
template<typename T> void fft(vector<T> &in, vector<complex<double>> &out, vector<complex<double>> &roots) {
    assert(in.size() == out.size());
    int N = (int) in.size();
    assert(!(N & (N - 1)));
    fft(in.data(), out.data(), roots, N);
}

/**
 * Computes the inverse Fast Fourier Transformation of the vector in.
 *
 * @param in the input vector (of any type)
 * @param out the output vector of type complex<double>
 * @param invRoots the conjugate of the complex roots of unity
 */
template<typename T> void invfft(vector<T> &in, vector<complex<double>> &out, vector<complex<double>> &invRoots) {
    assert(in.size() == out.size());
    int N = (int) in.size();
    assert(!(N & (N - 1)));
    fft(in, out, invRoots);
    for (int i = 0; i < N; i++) out[i] *= (1.0 / N);
}

/**
 * Computes the convolution of two vectors (of any type)
 *
 * @param a the first input vector (of any type)
 * @param b the second input vector (of any type)
 * @param out the output vector of type complex<double>
 */
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

/**
 * Multiplies two real polynomials together. vec[i] = coefficient of the ith exponent term.
 *
 * @param a the first polynomial
 * @param b the second polynomial
 * @param out the product of a and b
 */
void multiplyPolynomial(vector<ll> a, vector<ll> b, vector<ll> &out) {
    int N = (int) (a.size()) + (int) (b.size()) - 1;
    while (N & (N - 1)) N++;
    a.resize(N);
    b.resize(N);
    vector<complex<double>> c(N);
    convolve(a, b, c);
    out.resize(N);
    for (int i = 0; i < N; i++) out[i] = (ll) round(real(c[i]));
    while ((int) (out.size()) > 1 && out.back() == 0) out.pop_back();
}

void solve() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        int c = getCentroid(v, -1, getSize(v, -1));
        dfs1(c, -1, 0);
        large.clear();
        sort(all(adj[c]), maxCntCmp);
        for (int w : adj[c]) {
            if (exclude[w]) continue;
            small.clear();
            small.resize(maxCnt[w] + 1);
            fill(all(small), 0);
            while (sz(large) < sz(small)) large.pb(0);
            dfs2(w, c, 0);
            if (A[c]) small.insert(small.begin(), 0);
            FOR(i, sz(small)) ans[i] += small[i];
            vector<ll> res;
            multiplyPolynomial(large, small, res);
            FOR(i, sz(res)) ans[i] += res[i];
            if (A[c]) small.erase(small.begin());
            FOR(i, sz(small)) large[i] += small[i];
        }
        exclude[c] = true;
        for (int w : adj[c]) if (!exclude[w]) q.push(w);
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) {
        cin >> A[i];
        exclude[i] = false;
    }
    int a, b;
    FOR(i, N - 1) {
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    FOR(i, N + 1) ans[i] = 0;
    solve();
    For(i, 1, N + 1) ans[i] += ans[i - 1];
    cin >> Q;
    FOR(i, Q) {
        cin >> a >> b;
        cout << (ans[b] - (a == 0 ? 0 : ans[a - 1])) << nl;
    }
    return 0;
}
