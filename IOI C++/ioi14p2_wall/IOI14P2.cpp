/*
 * IOI14P2.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define INT_INF 0x3f3f3f3f
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

#define MAXN 2000000
int N;

struct Node {
    int up, down;
} seg[MAXN * 3];

void propogate(int parent, int child) {
    seg[child].down = max(min(seg[child].down, seg[parent].down), seg[parent].up);
    seg[child].up = min(max(seg[child].up, seg[parent].up), seg[parent].down);
}

void update(int cur, int cL, int cR, int l, int r, int op, int h) {
    if (cL > r || cR < l) return;
    if (cL >= l && cR <= r)  {
        if (op == 1) {
            seg[cur].down = max(seg[cur].down, h);
            seg[cur].up = max(seg[cur].up, h);
        } else {
            seg[cur].down = min(seg[cur].down, h);
            seg[cur].up = min(seg[cur].up, h);
        }
        return;
    }
    propogate(cur, l(cur));
    propogate(cur, r(cur));
    seg[cur].down = INT_INF;
    seg[cur].up = 0;
    int m = m(cL, cR);
    update(l(cur), cL, m, l, r, op, h);
    update(r(cur), m + 1, cR, l, r, op, h);
}

void update(int l, int r, int op, int h) {
    update(1, 1, N, l, r, op, h);
}

int query(int cur, int cL, int cR, int l, int r) {
    if (cL > r || cR < l) return INT_INF;
    if (cL >= l && cR <= r) return min(seg[cur].down, seg[cur].up);
    propogate(cur, l(cur));
    propogate(cur, r(cur));
    int m = m(cL, cR);
    return min(query(l(cur), cL, m, l, r), query(r(cur), m + 1, cR, l, r));
}

int query(int l, int r) {
    return query(1, 1, N, l, r);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]) {
    N = n;
    For0(i, k) {
        update(left[i] + 1, right[i] + 1, op[i], height[i]);
    }

    For1(i, n) {
        finalHeight[i - 1] = query(i, i);
    }
}

int main() {
    int n, k;
    ri(n);
    ri(k);
    int op[k], left[k], right[k], height[k];
    For0(i, k) {
        ri(op[i]);
        ri(left[i]);
        ri(right[i]);
        ri(height[i]);
    }
    int finalHeight[n];
    buildWall(n, k, op, left, right, height, finalHeight);
    For0(i, n) {
        prsi(finalHeight[i], "\n")
    }
    return 0;
}
