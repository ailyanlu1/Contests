/*
 * Det.cpp
 *
 *  Created on: Jun 4, 2017
 *      Author: Wesley Leung
 */

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

#define MAXN 500
#define MOD (ll) (1e9 + 7)

ll pow(ll base, ll x) {
    if (x == 0)
        return 1;
    if (x == 1)
        return base;
    if (x % 2 == 0)
        return pow(base * base % MOD, x / 2);
    return base * pow(base * base % MOD, x / 2) % MOD;
}

int N;
ll mat[MAXN][MAXN], det = 1;

int main() {
    ri(N);
    For0(i, N) {
        For0(j, N) {
            rll(mat[i][j]);
            if (mat[i][j] < 0) mat[i][j] += MOD;
        }
    }
    For0(i, N) {
        int max = i;
        For(j, i + 1, N) {
            if (mat[j][i] > mat[max][i]) max = j;
        }
        if (i != max) {
            det = -det;
            swap(mat[i], mat[max]);
        }
        For(j, i + 1, N) {
            ll d = mat[j][i] * pow(mat[i][i], MOD - 2) % MOD;
            For(k, i, N) {
                mat[j][k] = (mat[j][k] - d * mat[i][k] % MOD + MOD) % MOD;
            }
        }
    }
    det = (det + MOD) % MOD;
    For0(i, N) {
        det = det * mat[i][i] % MOD;
    }
    prll(det);
    return 0;
}
