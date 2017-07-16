import sys
input = sys.stdin.readline

MOD = int(1e9 + 7)

F, N = map(int, input().split())

flowers = [int(input()) for i in range(F)]
flowers.sort()
ans = 0
for i in range(1, N + 1):
    ans = (ans + pow(flowers[N - i], i, MOD)) % MOD
print(ans)
