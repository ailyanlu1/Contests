import sys
input = sys.stdin.readline

MAXN = 1024
A = [[0] * MAXN for i in range(MAXN)]
B = [[0] * MAXN for i in range(MAXN)]
temp = [[0] * MAXN for i in range(MAXN)]
BR = 1
BC = 1
B[0][0] = 1
N = int(input())
for i in range(N):
    R, C = map(int, input().split())
    for r in range(R):
        A[r] = list(map(int, input().split()))
    for r in range(R * BR):
        for c in range(C * BC):
            temp[r][c] = A[r // BR][c // BC] * B[r % BR][c % BC]
    BR *= R
    BC *= C
    for r in range(BR):
        for c in range(BC):
            B[r][c] = temp[r][c]
maxE = float('-inf')
minE = float('inf')
maxR = float('-inf')
minR = float('inf')
maxC = float('-inf')
minC = float('inf')
sumR = [0] * BR
sumC = [0] * BC
for r in range(BR):
    for c in range(BC):
        maxE = max(maxE, B[r][c])
        minE = min(minE, B[r][c])
        sumR[r] += B[r][c]
        sumC[c] += B[r][c]
print(maxE)
print(minE)
print(max(sumR))
print(min(sumR))
print(max(sumC))
print(min(sumC))
