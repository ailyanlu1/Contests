// http://www.spoj.com/problems/VFMUL/
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

void fft(vector<complex<double>> &a, bool invert) {
    int N = (int) a.size();
    for (int i = 1, j = 0; i < N; i++) {
        int bit = N >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= N; len <<= 1) {
        double ang = 2 * 3.14159265358979323846 / len * (invert ? -1 : 1);
        complex<double> wlen(cos(ang), sin(ang));
        for (int i = 0; i < N; i += len) {
            complex<double> w(1, 0);
            for (int j = 0; j < len / 2; j++) {
                complex<double> u = a[i + j];
                complex<double> v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) for (int i = 0; i < N; i++) a[i] /= N;
}

void multiplyInteger(vector<int> &a, vector<int> &b, vector<int> &res) {
    vector<complex<double>> fa(a.begin(), a.end());
    vector<complex<double>> fb(b.begin(), b.end());
    int N = (int) (a.size()) + (int) (b.size());
    while (N & (N - 1)) N++;
    fa.resize(N);
    fb.resize(N);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < N; i++) fa[i] *= fb[i];
    fft(fa, true);
    res.resize(N);
    int carry = 0;
    for (int i = 0; i < N; i++) {
        res[i] = (int) (fa[i].real() + 0.5) + carry;
        carry = res[i] / 10;
        res[i] %= 10;
    }
    while (((int) res.size()) > 1 && res.back() == 0) res.pop_back();
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N;
    cin >> N;
    string A, B;
    FOR(i, N) {
        cin >> A >> B;
        vector<int> a(sz(A)), b(sz(B)), res;
        REV(j, sz(A) - 1) a[j] = A[sz(A) - j - 1] - '0';
        REV(j, sz(B) - 1) b[j] = B[sz(B) - j - 1] - '0';
        multiplyInteger(a, b, res);
        REV(j, sz(res) - 1) cout << res[j];
        cout << nl;
    }
    return 0;
}
