/*
 * COCI14C4P6.cpp
 *
 *  Created on: May 26, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAXN 300
#define INF 0x3f3f3f3f

using namespace std;

int N, M;
long long K;
long long dp[MAXN + 1][MAXN + 1][2][2][2][2];

int main() {
    scanf("%d%d%lld", &N, &M, &K);
    memset(dp, -1, sizeof dp);
    for (long long i = 1; i <= N; i++) {
        for (long long j = 1; j <= M; j++) {
            for (int w = 0; w < 2; w++) {
                for (int x = 0; x < 2; x++) {
                    for (int y = 0; y < 2; y++) {
                        for (int z = 0; z < 2; z++) {
                            if (w == 0 && x == 0 && y == 0 && z == 0) {
                                dp[i][j][0][0][0][0] = INF;
                                continue;
                            }
                            dp[i][j][w][x][y][z] = (i*j-K)*(i*j-K);
                            if (i > 1) {
                                for (int k = 1; k < i; k++) {
                                    dp[i][j][w][x][y][z] = min(dp[i][j][w][x][y][z], dp[k][j][0][x][y][z] + dp[i-k][j][w][0][y][z]);
                                }
                            }
                            if (j > 1) {
                                for (int k = 1; k < j; k++) {
                                    dp[i][j][w][x][y][z] = min(dp[i][j][w][x][y][z], dp[i][k][w][x][0][z] + dp[i][j-k][w][x][y][0]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%lld", dp[N][M][1][1][1][1]);
    return 0;
}
