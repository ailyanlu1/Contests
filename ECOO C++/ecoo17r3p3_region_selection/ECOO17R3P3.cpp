/*
 * ECOO17R3P3.cpp
 *
 *  Created on: Jun 27, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define x first
#define y second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf("%c", &x)
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

#define MAXN 100

int N;
pii loc[MAXN];

double solve(vector<int> *v) {
    if (v->empty()) return 0;
    double a = 0, b = 0, c = 0;
    for (int i: *v) {
        a++;
        b -= 2 * loc[i].x;
        c += loc[i].x * loc[i].x;
    }
    double bestX = -b / (2 * a);
    double ansX = a * bestX * bestX + b * bestX + c;

    a = 0, b = 0, c = 0;
    for (int i: *v) {
        a++;
        b -= 2 * loc[i].y;
        c += loc[i].y * loc[i].y;
    }
    double bestY = -b / (2 * a);
    double ansY = a * bestY * bestY + b * bestY + c;
    return ansX + ansY;
}

void run() {
    ri(N);
    for (int i = 0; i < N; i++) {
        ri(loc[i].x);
        ri(loc[i].y);
    }
    if (N == 1) {
        printf("0\n");
        return;
    }
    double ans = INT_INF;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            double a = loc[i].y - loc[j].y;
            double b = loc[j].x - loc[i].x;
            double c = loc[i].x * loc[j].y - loc[i].y * loc[j].x;
            vector<int> ans1, ans2;
            for (int k = 0; k < N; k++) {
                if (a * loc[k].x + b * loc[k].y + c > 0) {
                    ans1.pb(k);
                } else if (a * loc[k].x + b * loc[k].y + c == 0) {
                    if (b == 0) {
                        if (loc[k].y >= loc[i].y) ans1.pb(k);
                        else ans2.pb(k);
                    } else {
                        if (loc[k].x >= loc[i].x) ans1.pb(k);
                        else ans2.pb(k);
                    }
                } else {
                    ans2.pb(k);
                }
            }
            ans = min(ans, solve(&ans1) + solve(&ans2));
        }
    }
    printf("%d\n", (int) round(ans));
}

int T = 10;

int main() {
    for (int i = 0; i < T; i++) {
        run();
    }
    return 0;
}
