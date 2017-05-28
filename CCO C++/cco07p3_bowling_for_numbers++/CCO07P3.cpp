/*
 * CCO07P3.cpp
 *
 *  Created on: May 28, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAXN 10000
#define MAXK 500
#define MAXW 100

using namespace std;

int T, N, K, W;
int dp[MAXK + 1][MAXN + MAXW + 1];
int pins[MAXN + MAXW + 1];
int psa[MAXN + MAXW + 1];

int solve(int k, int x) {
	if (k <= 0 || x < 0) return 0;
	if (dp[k][x] != -1) return dp[k][x];
	int pos = max(0, x - W);
	int score = psa[x] - psa[pos];
	dp[k][x] = max(solve(k, x - 1), solve(k - 1, pos) + score);
	if (k >= 2) {
		int sum = 0;
		for (int i = pos; i > pos - W + 1 && i > 0; i--) {
			sum += pins[i];
			dp[k][x] = max(dp[k][x], solve(k - 2, i - 1) + score + sum);
		}
	}
	return dp[k][x];
}

void run() {
	scanf("%d%d%d", &N, &K, &W);
	memset(dp, -1, sizeof dp);
	memset(pins, 0, sizeof pins);
	memset(psa, 0, sizeof psa);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &pins[i]);
	}
	for (int i = 1; i <= N + W; i++) {
		psa[i] = psa[i - 1] + pins[i];
	}
	printf("%d\n", solve(K, N + W));
}

int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		run();
	}
	return 0;
}
