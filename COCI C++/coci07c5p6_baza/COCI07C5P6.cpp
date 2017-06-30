/*
 * COCI07C5P6.cpp
 *
 *  Created on: Jun 29, 2017
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
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf("%c", &x)
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

#define MAXN 30000
#define MAXL 30

int N, Q, startInd[MAXL], endInd[MAXL], cnt[MAXN][MAXL], pre[MAXN][MAXL], id[MAXN];
string s, W[MAXN], sorted[MAXN];

int lowerBound(int c, char ch, int lo, int hi) {
    if (ch > sorted[hi - 1][c]) return hi;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (ch <= sorted[mid][c]) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int search(string s, int c, int lo, int hi) {
    startInd[c] = endInd[c] = -1;
    if (s[c] == 0) return sorted[lo][c] == 0 ? lo : -1;
    startInd[c] = lowerBound(c, s[c], lo, hi);
    endInd[c] = lowerBound(c, s[c] + 1, lo, hi);
    if (startInd[c] == endInd[c]) return -1;
    return search(s, c + 1, startInd[c], endInd[c]);
}

int main() {
    ri(N);
    for (int i = 0; i < N; i++) {
        cin >> W[i];
        sorted[i] = W[i];
    }
    sort(sorted, sorted + N);
    for (int i = 0; i < N; i++) {
        int r = search(W[i], 0, 0, N);
        id[r] = i + 1;
        for (int c = 0; startInd[c] < endInd[c]; c++) {
            pre[r][c] = ++cnt[startInd[c]][c];
        }
    }
    ri(Q);
    for (int q = 0; q < Q; q++) {
        cin >> s;
        int ans = 0;
        int r = search(s, 0, 0, N);
        if (r == -1) {
            ans += N;
            for (int c = 0; startInd[c] < endInd[c]; c++) {
                ans += cnt[startInd[c]][c];
            }
        } else {
            ans += id[r];
            for (int c = 0; s[c]; c++) {
                ans += pre[r][c];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
