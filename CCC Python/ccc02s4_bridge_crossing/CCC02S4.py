import sys
input = sys.stdin.readline

M = int(input())
Q = int(input())

name = ['']
time = [0]
dp = [0] * (Q + 1)
bound = [False] * (Q + 1)
for i in range(1, Q + 1):
    name.append(input().strip())
    time.append(int(input()))
for i in range(1, Q + 1):
    for j in range(1, min(i, M) + 1):
        if dp[i] == 0:
            dp[i] = dp[i - j] + max(time[i - j + 1: i + 1])
        else:
            dp[i] = min(dp[i], dp[i - j] + max(time[i - j + 1: i + 1]))
i = Q
while i > 0:
    for j in range(1, min(i, M) + 1):
        if dp[i] == dp[i - j] + max(time[i - j + 1: i + 1]):
            i -= j
            bound[i] = True
print('Total Time: ' + str(dp[Q]))
for i in range(1, Q + 1):
    print(name[i] + ' ', end='')
    if bound[i]:
        print()
print()
