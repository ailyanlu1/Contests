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

#define MAXN 300010
#define MAXX 15010
#define EPS 1e-3
#define EPS2 1e-9

int N;
double X[MAXN];

double d(double x, int n) {
    double ret = 0.0;
    FOR(i, n) ret += (abs(x - X[i]) < EPS2) ? 0.0 : (x - X[i]) * (x - X[i]) * (x - X[i]) / abs(x - X[i]);
    ret *= 3.0;
    return ret;
}

double d2(double x, int n) {
    double ret = 0.0;
    FOR(i, n) ret += (abs(x - X[i]) < EPS2) ? 0.0 : (x - X[i]) * (x - X[i]) / abs(x - X[i]);
    ret *= 6.0;
    return ret;
}

double newton(double x0, int i) {
    double cur = x0, next = x0, dv, d2v;
    do {
        cur = next;
        dv = d(cur, i);
        d2v = d2(cur, i);
        if (abs(d2v) < EPS2) {
            printf("%d\n", 1);
            return cur;
        }
        next = cur - dv / d2v;
    } while (abs(next - cur) > EPS);
    return next;
}

int main() {
    ri(N);
    if (N <= 1000) {
        FOR(i, N) {
            rd(X[i]);
            printf("%.3f\n", newton(0, i + 1));
        }
    } else {
        int cnt0 = 0, cnt1 = 0, xi;
        FOR(i, N) {
            ri(xi);
            if (xi == 1) cnt1++;
            else cnt0++;
            double s1 = sqrt(cnt1);
            double s0 = sqrt(cnt0);
            printf("%.3f\n", s1 / (s1 + s0));
        }
    }
    return 0;
}
