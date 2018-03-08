#include <bits/stdc++.h>
using namespace std;

#define MAXN 5005

int N, A[MAXN], dp[2][MAXN];

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    while (cin >> N) {
        for (int i = 0; i < N; i++) cin >> A[i];
        for (int i = 0; i < N; i++) dp[0][i] = dp[1][i] = 0;
        for (int i = N - 1; i >= 0; i--) {
            dp[i % 2][i] = 0;
            for (int j = i + 1; j < N; j++) {
                if (A[i] == A[j]) dp[i % 2][j] = dp[1 - i % 2][j - 1] + 1;
                else dp[i % 2][j] = max(dp[i % 2][j - 1], dp[1 - i % 2][j]);
            }
        }
        cout << dp[0][N - 1] << "\n";
    }
    return 0;
}
