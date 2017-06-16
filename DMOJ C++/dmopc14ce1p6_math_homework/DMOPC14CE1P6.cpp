/*
 * DMOPC14CE1P6.cpp
 *
 *  Created on: May 27, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAXC 3001
#define MOD 1000000007

int c[MAXC + 1][MAXC + 1];

using namespace std;

long long exp(long long a, long long b) {
    if (b == 0) return 1;
    if (b == 1) return a;
    if (b % 2 == 0) return exp((a * a) % MOD, b / 2) % MOD;
    return (a * exp((a * a) % MOD, b / 2)) % MOD;
}

void pre() {
    for (int i = 1; i <= MAXC; i++) {
        for (int j = 1; j <= MAXC; j++) {
            if (i == j || j == 1) c[i][j] = 1;
            else c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
        }
    }
}

int solve(int R, int C) {
    if (C > R) swap(C, R);
    long long ans = 0;
    long long sign = 1;
    for (int i = 0; i <= C; i++) {
        ans = (ans + sign * ((long long)(c[C + 1][i + 1]) * exp(exp(2, C - i) - 1, R)) % MOD) % MOD;
        sign = -sign;
    }
    return (ans + MOD) % MOD;
}

int main() {
    pre();
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        int R, C;
        scanf("%d%d", &R, &C);
        printf("%d\n", solve(R, C));
    }
    return 0;
}
