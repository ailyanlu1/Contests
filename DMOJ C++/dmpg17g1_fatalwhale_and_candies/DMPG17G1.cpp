/*
 * DMPG17G1.cpp
 *
 *  Created on: May 24, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAXN 4096

using namespace std;

int N, P;
int s[MAXN + 1], mod[MAXN + 1];
int dp[2][MAXN + 1];
deque<int> candies;

int main() {
	// TODO Insert Code Here
	scanf("%d%d", &N, &P);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &s[i]);
		mod[i] = s[i] % P;
	}
	dp[0][0] = 0;
	for (int i = 1; i < P; i++) {
		dp[0][i] = INT_MIN;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < P; j++) {
			dp[1][j] = max(dp[0][j], dp[0][(j - mod[i] + P) % P] + s[i]);
		}
		if (i == N) continue;
		for (int j = 0; j < P; j++) {
			dp[0][j] = dp[1][j];
		}
	}
	printf("%d\n", dp[1][0]);
	for (int i = N, k = 0; i >= 1; i--) {
		for (int j = 0; j < P; j++) {
			if (dp[1][k] != dp[0][k] && dp[1][k] == dp[0][(j - mod[i] + P) % P] + s[i]) {
				k = (j - mod[i] + P) % P;
				candies.push_front(i);
				break;
			}
		}
		for (int j = 0; j < P; j++) {
			dp[1][j] = dp[0][j];
		}

		for (int j = 0; j < P; j++) {
			dp[0][(j - mod[i - 1] + P) % P] = dp[1][j] - s[i - 1];
		}
	}
	printf("%d\n", candies.size());
	for (int i = 0; i < candies.size(); i++) {
		printf("%d ", candies[i]);
	}
	printf("\n");
	return 0;
}
