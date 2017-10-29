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
#define FILL(a, x) memset((a), (x), sizeof(a))
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

#define MAXN 10010
#define EPS 1e-9

int N;
double R;

struct Goose {
    double x, y, vx, vy;

    Goose(double x1, double y1, double x2, double y2, double v) {
        x = x1;
        y = y1;
        double dx = x2 - x1;
        double dy = y2 - y1;
        double angle = atan2(dy, dx);
        vx = v * cos(angle);
        vy = v * sin(angle);
    }

    double collisionTime(Goose &g) {
        double dx = g.x - x;
        double dy = g.y - y;
        double dvx = g.vx - vx;
        double dvy = g.vy - vy;
        double ddv = dx * dvx + dy * dvy;
        double dd = dx * dx + dy * dy;
        if (dd <= R * R + EPS) return 0.0;
        double dvdv = dvx * dvx + dvy * dvy;
        double d = (ddv * ddv) - dvdv * (dd - R * R);
        if (ddv > EPS) return D_INF;
        return d < -EPS ? D_INF : abs((ddv + sqrt(d)) / dvdv);
    }
} *geese[MAXN];

int main() {
    ri(N);
    rd(R);
    double x1, y1, x2, y2, v;
    FOR(i, N) {
        rd(x1);
        rd(y1);
        rd(x2);
        rd(y2);
        rd(v);
        geese[i] = new Goose(x1, y1, x2, y2, v);
    }
    double t;
    For(i, 1, N) {
        t = geese[0]->collisionTime(*geese[i]);
        if (t < D_INF) printf("%d\n", i + 1);
    }
    return 0;
}
