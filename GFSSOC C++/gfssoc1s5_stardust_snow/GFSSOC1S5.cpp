/*
 * GFSSOC1S5.cpp
 *
 *  Created on: May 25, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAX 50
#define INF 0x3f3f3f3f

using namespace std;

int R, C, S, B, K, M;
int ans = 0;
int T[MAX + 1][MAX + 1], V[MAX + 1][MAX + 1];
int dp[2][MAX + 1][MAX][MAX + 1];

int main() {
	scanf("%d%d%d%d%d%d", &R, &C, &S, &B, &K, &M);
	for (int i = 0; i < S; i++) {
		int Ti, Vi, ci, ri;
		scanf("%d%d%d%d", &Ti, &Vi, &ci, &ri);
		T[ri][ci] = Ti;
		V[ri][ci] = Vi;
	}
	memset(dp[0], -INF, sizeof dp[0]);
	dp[0][0][0][1] = 0;
	for (int r = 1; r <= R; r++) {
		memset(dp[r%2], -INF, sizeof dp[r%2]);
		for (int k = 0; k <= K; k++) {
			for (int b = 0; b < B; b++) {
				for (int c = 1; c <= C; c++) {
					for (int m = max(1, c - M); m <= min(C, c + M); m++) {
						dp[r%2][k][b][c] = max(dp[r%2][k][b][c], dp[1-r%2][k][b][m]);
						if(k >= 1 && b >= T[r][c]) {
							dp[r%2][k][b][c] = max(dp[r%2][k][b][c], dp[1-r%2][k - 1][b - T[r][c]][m] + V[r][c]);
						}
					}
					ans = max(ans, dp[r%2][k][b][c]);
				}
			}
		}
	}
	printf("%d", ans);
	return 0;
}
