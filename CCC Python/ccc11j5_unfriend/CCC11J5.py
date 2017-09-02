import sys
input = sys.stdin.readline

N = int(input())
dp = [1] * N

for i in range(N - 1):
    dp[int(input()) - 1] *= 1 + dp[i]
print(dp[N - 1])
