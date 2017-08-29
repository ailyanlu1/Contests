#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
#define m(x, y) (x + (y - x) / 2)
#define MIN(a, b) (a = min(a, b))
#define MAX(a, b) (a = max(a, b))
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
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) (rand() % (b - a + 1) + a)

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<int, float> pif;
typedef pair<float, int> pfi;
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
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXN 1005

struct Line {
    int x, yt, yb;
    ll t;

    Line(){}

    Line(int x, int yt, int yb, ll t) {
        this->x = x;
        this->yt = yt;
        this->yb = yb;
        this->t = t;
    }

    bool operator < (Line &l) {
        return x < l.x;
    }
};

vector<Line> events;
int N, T;
vector<int> ys;
ll ans = 0LL, tint[2 * MAXN];

int main() {
    ri(N);
    ri(T);
    int xl, yt, xr, yb;
    ll t;
    ys.pb(0);
    events.pb(Line(0, 0, 0, 0LL));
    FOR(i, N) {
        ri(xl);
        ri(yt);
        ri(xr);
        ri(yb);
        rll(t);
        events.pb(Line(xl, yt, yb, t));
        events.pb(Line(xr, yt, yb, -t));
        ys.pb(yt);
        ys.pb(yb);
    }
    sort(events.begin() + 1, events.end());
    sort(ys.begin() + 1, ys.end());
    ys.erase(unique(ys.begin() + 1, ys.end()), ys.end());
    int l, r;
    For(i, 1, 2 * N + 1) {
        For(j, 1, (int) ys.size()) {
            if (tint[j] >= T) ans += (ll) (ys[j + 1] - ys[j]) * (events[i].x - events[i - 1].x);
        }
        l = upper_bound(ys.begin() + 1, ys.end(), events[i].yt) - (ys.begin() + 1);
        r = upper_bound(ys.begin() + 1, ys.end(), events[i].yb) - (ys.begin() + 1);
        For(j, l, r) {
            tint[j] += events[i].t;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
