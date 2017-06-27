/*
 * CCO17P2.cpp
 *
 *  Created on: May 27, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

int N, M;
unordered_map<long long, pair<int, int>> dp;

long long getHash(int n, int m) {
    return (long long) (n) * INF + (long long) (m);
}

pair<int, int> solve(int n, int m) {
    if (n == 0 || m == 0) return make_pair(0, 0);
    if (n < m) swap(n, m);
    long long id = getHash(n, m);
    if (dp.count(id)) return dp[id];
    pair<int, int> ret = make_pair(INF, 0);
    if (n == 2 * m) {
        pair<int, int> x = make_pair(0, 0);
        ret.first = min(ret.first, x.first + 1);
        ret.second = max(ret.second, x.second + 1);
        if (m % 2 == 0) {
            pair<int, int> y = solve(n - m / 2, m);
            ret.first = min(ret.first, y.first + 1);
            ret.second = max(ret.second, y.second + 1);
        }
    } else if (n < 2 * m) {
        if (m % 2 == 0) {
            pair<int, int> x = solve(n - m / 2, m);
            ret.first = min(ret.first, x.first + 1);
            ret.second = max(ret.second, x.second + 1);
        }
        if (n % 2 == 0) {
            pair<int, int> x = solve(m - n / 2, n);
            ret.first = min(ret.first, x.first + 1);
            ret.second = max(ret.second, x.second + 1);
        }
    } else if (n > 2 * m) {
        int q = n / (2 * m);
        int r = n % (2 * m);
        pair<int, int> x = solve(r, m);
        ret.first = min(ret.first, x.first + q);
        ret.second = max(ret.second, x.second + q);
        if (m % 2 == 0) {
            int a = (int) ceil(1.0 * r / (m / 2));
            int b = q - 1;
            int c = 2 * m + r - a * m / 2;
            pair<int, int> y = solve(c, m);
            ret.first = min(ret.first, y.first + a + b);
            ret.second = max(ret.second, y.second + a + 4 * b);
        }
    }
    return dp[id] = ret;
}

int main() {
    scanf("%d%d", &N, &M);
    pair<int, int> ans = solve(N, M);
    printf("%d %d\n", ans.first, ans.second);
    return 0;
}
