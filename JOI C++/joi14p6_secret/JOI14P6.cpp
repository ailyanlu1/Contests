#include <bits/stdc++.h>
#include "secret.h"

#define INT_INF 0x3f3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define x first
#define y second
#define ri(x) scanf("%d", &x);
#define rll(x) scanf("%lld", &x);
#define rllu(x) scanf('%llu', &x)
#define rd(x) scanf("%lf", &x);
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

#define MAXN 1000

int range[MAXN + 1][MAXN + 1];

int Secret(int X, int Y);

void solve(int l, int r) {
    if (l + 1 >= r) return;
    int mid = l + (r - l) / 2;
    Reve(i, mid - 1, l) {
        if (range[i][mid] == -1) range[i][mid] = Secret(range[i][i + 1], range[i + 1][mid]);
    }
    Fore(i, mid + 1, r) {
        if (range[mid][i] == -1) range[mid][i] = Secret(range[mid][i - 1], range[i - 1][i]);
    }
    solve(l, mid);
    solve(mid, r);
}

void Init(int N, int A[]) {
    Fill(range, -1);
    For0(i, N) {
        range[i][i + 1] = A[i];
    }
    solve(0, N);
}

int Query(int L, int R) {
    Fore(i, L + 1, R) {
        if (range[L][i] != -1 && range[i][R + 1] != -1) {
            return Secret(range[L][i], range[i][R + 1]);
        }
    }
    return range[L][R + 1];
}
