/*
 * IOI15P1.cpp
 *
 *  Created on: May 12, 2017
 *      Author: wleung
 */

#include <bits/stdc++.h>
#define MAXN 10000001
#define INF LLONG_MAX;

using namespace std;

long long dp[2][MAXN];

long long delivery(int N, int K, int L, int positions[]) {
	for (int i = 1; i <= N; i++) {
		if (i >= K) {
			dp[0][i] = dp[0][i - K] + min(2 * positions[i - 1], L);
		} else {
			dp[0][i] = min(2 * positions[i - 1], L);
		}
	}
	for (int i = N; i >= 1; i--) {
		if (N - i >= K) {
			dp[1][i] = dp[1][i + K] + min(2 * (L - positions[i - 1]), L);
		} else {
			dp[1][i] = min(2 * (L - positions[i - 1]), L);
		}
	}
	long long ans = INF;
	for (int i = 0; i <= N; i++) {
		ans = min(ans, dp[0][i] + dp[1][i + 1]);
	}
	return ans;
}

int main() {
	int N, K, L;
	scanf("%d%d%d", &N, &K, &L);
	int positions[N];
	for (int i = 0; i < N; i++) {
		scanf("%d", &positions[i]);
	}
	printf("%I64d\n", delivery(N, K, L, positions));
	return 0;
}
