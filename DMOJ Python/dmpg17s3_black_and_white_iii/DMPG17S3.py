MOD = 10**9 + 7
K, M = map(int, input().split())
black = 0
for i in range(1 << K):
    black += input().count('#')
print(pow(pow(2, pow(4, M, MOD - 1), MOD) - 1, black, MOD))
