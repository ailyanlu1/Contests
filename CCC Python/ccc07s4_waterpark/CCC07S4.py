import sys
input = sys.stdin.readline

n = int(input())
slides = []
x, y = map(int, input().strip().split())
while (x, y) != (0, 0):
    slides.append((x, y))
    x, y = map(int, input().strip().split())
slides.sort()
dp = [0] * n
dp[0] = 1
for s in slides:
    dp[s[1] - 1] += dp[s[0] - 1]
print(dp[n - 1])
