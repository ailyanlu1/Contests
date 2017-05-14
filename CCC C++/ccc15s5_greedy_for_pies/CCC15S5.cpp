/*
 * CCC15S5.cpp
 *
 *  Created on: May 14, 2017
 *      Author: wleung
 */

#include <bits/stdc++.h>
#define MAXN 3000
#define MAXM 100

using namespace std;

int n, m;
int N[MAXN + 1], M[MAXM + 1];
int dp[MAXN + 2][MAXM + 2][MAXM + 2][2];

int solve(int i, int l, int r, int take) {
	if (dp[i][l][r][take] != -1) return dp[i][l][r][take];
	if (i == n + 1 && l > r) return dp[i][l][r][take] = 0;
	// take
	if (take == 0) {
		if (i != n + 1) dp[i][l][r][take] = max(dp[i][l][r][take], N[i] + solve(i + 1, l, r, 1));
		if (l <= r) dp[i][l][r][take] = max(dp[i][l][r][take], M[r] + solve(i, l, r - 1, 1));
	}
	// skip
	if (i != n + 1) dp[i][l][r][take] = max(dp[i][l][r][take], solve(i + 1, l, r, 0));
	if (l <= r) dp[i][l][r][take] = max(dp[i][l][r][take], solve(i, l + 1, r, 0));
	return dp[i][l][r][take];
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &N[i]);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &M[i]);
	}
	sort(M, M + m + 1);
	memset(dp, -1, sizeof dp);
	printf("%d\n", solve(1, 1, m, 0));
	return 0;
}
