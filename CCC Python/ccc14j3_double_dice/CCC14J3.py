import sys
input = sys.stdin.readline

A = 100
D = 100
N = int(input())
for i in range(N):
    a, d = map(int, input().strip().split())
    if a < d:
        A -= d
    elif a > d:
        D -= a
print(A)
print(D)
