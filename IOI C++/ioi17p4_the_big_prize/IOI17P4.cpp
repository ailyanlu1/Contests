// 97.68/100 Query Limit Exceeded

#include <bits/stdc++.h>
#include "prize.h"

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

#define MAXN 200005

unordered_map<int, vector<int>> queries;
int minInd[MAXN], maxInd[MAXN], T = 0;
// int cnt = 0;
vector<int> q;

vector<int> &ask1(int i) {
    if (queries.count(i) > 0) return queries[i];
//    cnt++;
//    assert(cnt <= 5000);
    return queries[i] = ask(i);
}

bool check(int i, int lo) {
    q = ask1(i);
    if (q[0] + q[1] != T) return true;
    MIN(minInd[q[0]], i);
    MAX(maxInd[q[0]], i);
    return lo < q[0];
}

int find_best(int n) {
    FOR(i, n) {
        minInd[i] = MAXN;
        maxInd[i] = -1;
    }
    FOR(i, min(n, 472)) {
        q = ask1(i);
        if (q[0] + q[1] == 0) return i;
        MAX(T, q[0] + q[1]);
    }
    int cur = -1, lo, mid, hi;
    FOR(i, T) {
        lo = cur + 1;
        hi = n - 1;
        FOR(j, i + 1) {
            MAX(lo, maxInd[j] + 1);
        }
        For(j, i + 1, n) {
            MIN(hi, minInd[j]);
        }
        while (lo < hi) {
            mid = m(lo, hi);
            if (check(mid, i)) hi = mid;
            else lo = mid + 1;
        }
        q = ask1(lo);
        if (q[0] + q[1] == 0) return lo;
        cur = lo;
    }
    // should never be here
    assert(false);
    return -1;
}
