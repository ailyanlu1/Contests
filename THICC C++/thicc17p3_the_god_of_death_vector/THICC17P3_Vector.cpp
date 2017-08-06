/*
 * THICC17P3_Vector.cpp
 *
 *  Created on: Aug 5, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

#define MAXN (int) (1e6 + 5)

int N, x, y, Q, cur = 0;
char t;
vector<pii> dayLoc[MAXN];

int main() {
    ri(N);
    for (int i = 0; i < N; i++) {
        ri(y);
        dayLoc[i].pb({0, y});
    }
    ri(Q);
    for (int i = 0; i < Q; i++) {
        rc(t);
        if (t == 'C') {
            ri(x);
            ri(y);
            dayLoc[x - 1].pb({++cur, y});
        } else if (t == 'Q') {
            ri(x);
            ri(y);
            auto iter = upper_bound(dayLoc[x - 1].begin(), dayLoc[x - 1].end(), mp(y, INT_INF)) - 1;
            printf("%d\n", iter->second);
        } else {
            i--;
        }
    }
    return 0;
}
