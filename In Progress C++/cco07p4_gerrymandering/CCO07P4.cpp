/*
 * CCO07P4.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: Wesley Leung
 */


// 160/250 RTE
#include <bits/stdc++.h>

#define INT_INF 0x3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define m(x, y) x + (y - x) / 2
#define x first
#define y second
#define ri(x) scanf("%d", &x);
#define rll(x) scanf("%lld", &x);
#define rllu(x) scanf('%llu', &x)
#define rd(x) scanf("%lf", &x);
#define rc(x) scanf("%c", &x);
#define pri(x) printf("%d", x);
#define prll(x) printf("%lld", x);
#define prllu(x) printf("%llu", x);
#define prd(x) printf("%f", x);
#define prs(x) printf(x);
#define prsi(x, s) printf("%d" s, x);
#define prsll(x, s) printf("%lld" s, x);
#define prsllu(x, s) printf("%llu" s, x);
#define prsd(x, s) printf("%f" s, x);
#define For(i, a, n) for (int i = a; i < n; i++)
#define Fore(i, a, n) for (int i = a; i <= n; i++)
#define For0(i, n) For(i, 0, n)
#define For1(i, n) Fore(i, 1, n)
#define Forc(i, c) for (int i = c.begin(); i != c.end(); i++)
#define Rev(i, n, a) for (int i = n; i > a; i--)
#define Reve(i, n, a) for (int i = n; i >= a; i--)
#define Rev0(i, n) Reve(i, n - 1, 0)
#define Rev1(i, n) Reve(i, n, 1)
#define Revc(i, c) for (int i = c.end(); i-- != c.begin();)
#define Fill(a, x) memset(a, x, sizeof(a))
#define All(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
#define MAXN 40000
#define MAXP 10

int N, P;
int votes[MAXN + 1][MAXP + 1];
int dp[MAXN + 1][(MAXN + 1) / 32 + 1];

int calc(int cur, int m) {
    if (cur > N) {
        if (m != 0) return -INT_INF;
        else return 0;
    }
    if (N - cur + 1 <= m) return - INT_INF;
    if (dp[cur][m] != -1) return dp[cur][m];
    int ret = 0;
    for (int i = 0; i <= m && cur + i <= N; i++) {
        int won = 1;
        int val = votes[cur + i][1] - votes[cur - 1][1];
        For(j, 2, P + 1) {
            if (votes[cur + i][j] - votes[cur - 1][j] >= val) {
                won = 0;
                break;
            }
        }
        ret = max(ret, won + calc(cur + i + 1, m - i));
    }
    return dp[cur][m] = ret;
}

int main() {
    ri(N);
    ri(P);
    For1(i, N) {
        For1(j, P) {
            ri(votes[i][j]);
            votes[i][j] += votes[i - 1][j];
        }
    }
    Fill(dp, -1);
    For0(i, N) {
        if (calc(1, i) >= (N - i) / 2 + 1) {
            prsi(i, "\n");
            return 0;
        }
    }
    prs("-1\n");
    return 0;
}
