import sys
input = sys.stdin.readline

MOD = 1000000007
n, m = map(int, input().strip().split())
cost = list(map(int, input().strip().split()))

cur = 0
curPow = 0
minCost = 0
for c in reversed(sorted(cost)):
    minCost = (minCost + pow(c, curPow, MOD)) % MOD
    cur += 1
    if cur == m:
        cur = 0
        curPow += 1
print(minCost)
