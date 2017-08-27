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
#define Min(a, b) (a = min(a, b))
#define Max(a, b) (a = max(a, b))
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

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return hash<T1> {}(p.first) << 31 | hash<T2> {}(p.second);}};

pair<int, int> floor(vector<int> &a, int start, int end, int key) {
    int lo = start, hi = end - 1, mid;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        if (key < a[mid]) hi = mid - 1;
        else lo = mid + 1;
    }
    return {hi, hi == -1 ? 0 : a[hi]};
}

pair<int, int> ceiling(vector<int> &a, int start, int end, int key) {
    int lo = start, hi = end, mid;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (key > a[mid]) lo = mid + 1;
        else hi = mid;
    }
    return {lo, lo == end ? 0 : a[lo]};
}

#define MAXNM 200005
#define RED 1
#define BLUE -1

int n, m, cInd, last[MAXNM], wiresRange[MAXNM];
pii all[MAXNM];
ll cut = 0LL, dp[MAXNM], preR[MAXNM], preB[MAXNM];

ll min_total_length(vector<int> r, vector<int> b) {
    n = r.size();
    m = b.size();
    FOR(i, n) {
        all[i] = {r[i], RED};
    }
    FOR(i, m) {
        all[i + n] = {b[i], BLUE};
    }
    sort(all, all + n + m);
    FOR(i, n + m) {
        dp[i] = preR[i] = preB[i] = 0LL;
        last[i] = wiresRange[i] = -1;
    }
    cInd = n;
    last[cInd] = MAXNM;
    FOR(i, n + m) {
        preR[i] = (i == 0 ? 0 : preR[i - 1]) + (all[i].s == RED ? all[i].f : 0);
        preB[i] = (i == 0 ? 0 : preB[i - 1]) + (all[i].s == BLUE ? all[i].f : 0);
        cInd -= all[i].s;
        if (last[cInd] != -1) wiresRange[i] = last[cInd];
        last[cInd] = i;
    }
    pii below, above;
    FOR(i, n + m) {
        if (all[i].s == RED) {
            below = floor(b, 0, m, all[i].f);
            above = ceiling(b, 0, m, all[i].f);
        } else {
            below = floor(r, 0, n, all[i].f);
            above = ceiling(r, 0, n, all[i].f);
        }
        dp[i] = (i == 0 ? 0 : dp[i - 1]) + min(below.f == -1 ? INT_INF : all[i].f - below.s, above.f == (all[i].s == RED ? m : n) ? INT_INF : above.s - all[i].f);
        if (wiresRange[i] != -1) Min(dp[i], dp[wiresRange[i]] + abs((preR[i] - preR[wiresRange[i]]) - (preB[i] - preB[wiresRange[i]])));
    }
    return dp[n + m - 1];
}

int main() {
    int N, M;
    ri(N);
    ri(M);
    vector<int> r, b;
    int a;
    FOR(i, N) {
        ri(a);
        r.pb(a);
    }
    FOR(i, M) {
        ri(a);
        b.pb(a);
    }
//    vector<int> r, b;
//    srand(time(0));
//    FOR(i, 15) {
//        int x = randi(0, 3);
//        if (x == 0) {
//            r.pb(i);
//        } else if (x == 1) {
//            b.pb(i);
//        }
//    }
//    for (int x : r) {
//        printf("%d ", x);
//    }
//    printf("\n");
//    for (int x : b) {
//        printf("%d ", x);
//    }
//    printf("\n---\n");
    printf("%lld\n", min_total_length(r, b));
    return 0;
}
