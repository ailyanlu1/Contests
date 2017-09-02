import sys
input = sys.stdin.readline


def solve(n, k):
    if k > n:
        return 0
    if k == 1 or k == n:
        return 1
    if dp[n][k] != -1:
        return dp[n][k]
    dp[n][k] = solve(n - 1, k - 1) + solve(n - k, k)
    return dp[n][k]


N = int(input())
K = int(input())
dp = [[-1 for j in range(N + 1)] for i in range(N + 1)]
print(solve(N, K))
