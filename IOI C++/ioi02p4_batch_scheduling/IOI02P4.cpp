/*
 * IOI02P4.cpp
 *
 *  Created on: Jul 23, 2017
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

#define MAXN 10000

int N, S, t, f, T[MAXN + 1], F[MAXN + 1], dp[MAXN + 2];
deque<int> q;

inline double div2(int a, int b) {
    return (double) (dp[b + 1] - dp[a + 1]) / (T[a] - T[b]);
}

int main() {
    ri(N);
    ri(S);
    T[0] = F[0] = 0;
    for (int i = 1; i <= N; i++) {
        ri(t);
        ri(f);
        T[i] = T[i - 1] + t;
        F[i] = F[i - 1] + f;
    }
    q.push_back(N);
    for (int i = N; i >= 1; i--) {
        while (q.size() >= 2 && div2(q[0], q[1]) < (double) (F[N] - F[i - 1])) {
            q.pop_front();
        }
        int ind = q.front();
        dp[i] = (S + T[ind] - T[i - 1]) * (F[N] - F[i - 1]) + dp[ind + 1];
        while (q.size() >= 2 && div2(q[q.size() - 2] , q[q.size() - 1]) > div2(q[q.size() - 1], i - 1)) {
            q.pop_back();
        }
        q.push_back(i - 1);
    }
    printf("%d\n", dp[1]);
    return 0;
}
