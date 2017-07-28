import sys
input = sys.stdin.readline

N, M = map(int, input().split())
A, B, C = map(int, input().split())

S = [0] * (N + 2)
pre = [0] * (N + 2)
suf = [0] * (N + 2)
S[1: N + 1] = sorted(list(map(int, input().split())))
for i in range(1, N + 1):
    pre[i] = pre[i - 1] + (S[i] - 1) * B
for i in range(N, 0, -1):
    suf[i] = suf[i + 1] + (S[i] - 1) * A + C * (N - i)
print(min(pre[i] + suf[i + 1] for i in range(0, N + 1)))
