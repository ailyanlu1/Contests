import sys
input = sys.stdin.readline

N = int(input())
K = int(input())
SS = N
for i in range(K):
    N *= 10
    SS += N
print(SS)
