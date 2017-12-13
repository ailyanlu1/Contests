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

#define MAXN 20

int N, si, LSet, RSet, minDiff = INT_MAX;
vector<int> S[2];
vector<pii> diff[2];
vector<int> ans[2];

void solveHalf(int side) {
    int perms = 1;
    FOR(i, (int) S[side].size()) perms *= 3;
    For(i, 1, perms) {
        int cur = i;
        int curDiff = 0;
        FOR(j, (int) S[side].size()) {
            curDiff += ((cur + 1) % 3 - 1) * S[side][j];
            cur /= 3;
        }
        diff[side].pb(mp(curDiff, i));
    }
    sort(diff[side].begin(), diff[side].end());
    diff[side].resize(unique(diff[side].begin(), diff[side].end()) - diff[side].begin());
}

int main() {
    ri(N);
    FOR(i, N) {
        ri(si);
        S[i % 2].pb(si);
    }
    solveHalf(0);
    solveHalf(1);
    int p = 0, q = 0, LS = diff[0].size(), RS = diff[1].size();
    if (LS > 0) {
        if (abs(diff[0][0].f) < minDiff) {
            LSet = diff[0][0].s;
            RSet = 0;
            minDiff = abs(diff[0][0].f);
        }
    }
    if (RS > 0) {
        if (abs(diff[1][0].f) < minDiff) {
            LSet = 0;
            RSet = diff[1][0].s;
            minDiff = abs(diff[1][0].f);
        }
    }
    while (p < LS && q < RS) {
        if (abs(diff[0][p].f - diff[1][q].f) < minDiff) {
            LSet = diff[0][p].s;
            RSet = diff[1][q].s;
            minDiff = abs(diff[0][p].f - diff[1][q].f);
        }
        if (diff[0][p].f < diff[1][q].first) p++;
        else if (diff[0][p].f > diff[1][q].first) q++;
        else break;
    }
    FOR(i, LS) {
        if (LSet % 3 == 1) ans[0].pb(l(i));
        else if (LSet % 3 == 2) ans[1].pb(l(i));
        LSet /= 3;
    }
    FOR(i, RS) {
        if (RSet % 3 == 1) ans[1].pb(r(i));
        else if (RSet % 3 == 2) ans[0].pb(r(i));
        RSet /= 3;
    }
    FOR(i, 2) {
        for (int x : ans[i]) {
            printf("%d ", x + 1);
        }
        printf("\n");
    }
    return 0;
}
