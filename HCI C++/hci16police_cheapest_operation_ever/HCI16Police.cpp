/*
 * HCI16Police.cpp
 *
 *  Created on: May 22, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAXN 100000

long long c[MAXN + 1], dp[MAXN + 1];
int N, H;

using namespace std;

long long getCost(int a, int b) {
    return (c[a] - c[b]) * (c[a] - c[b]);
}

long long solve(int a) {
    if (a > N) return 0;
    if (dp[a] != -1) return dp[a];
    long long ret = INT_MAX;
    for (int b = a; b <= N; b++) {
        long long cost = getCost(a, b);
        if (cost > 2 * H) break;
        ret = min(ret, solve(b + 1) + cost + H);
    }
    return dp[a] = ret;
}

int main() {
    // TODO Insert Code Here
    scanf("%d%d", &N, &H);
    dp[0] = -1;
    for (int i = 1; i <= N; i++) {
        dp[i] = -1;
        scanf("%lld", &c[i]);
    }
    printf("%lld\n", solve(1));
    return 0;
}
