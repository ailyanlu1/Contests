import sys
input = sys.stdin.readline

D = int(input())
C = int(input())
clubs = [int(input()) for i in range(C)]

dp = [float('inf')] * (D + 1)

dp[0] = 0

for d in range(D + 1):
    for dc in clubs:
        if d - dc >= 0:
            dp[d] = min(dp[d], dp[d - dc] + 1)
if dp[D] == float('inf'):
    print('Roberta acknowledges defeat.')
else:
    print('Roberta wins in ' + str(dp[D]) + ' strokes.')
