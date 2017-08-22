import sys
input = sys.stdin.readline

t = int(input())
for tt in range(t):
    n, k, w = map(int, input().strip().split())
    pins = [0] * n
    sumP = [0] * n
    dp = [[0] * n for i in range(k + 1)]
    for i in range(n):
        pins[i] = int(input())
        for j in range(0, w):
            if j > i:
                break
            sumP[i] += pins[i - j]
    for i in range(1, k + 1):
        dp[i][0] = pins[0]
        for j in range(1, n):
            temp = sumP[j]
            if j >= w:
                temp += dp[i - 1][j - w]
            dp[i][j] = max(temp, dp[i][j - 1])
    print(dp[k][n - 1])
