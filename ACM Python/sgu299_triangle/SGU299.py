# http://codeforces.com/problemsets/acmsguru/problem/99999/299
import sys
input = sys.stdin.readline

N = int(input())
A = [int(input()) for i in range(N)]
A.sort()
for i in range(N - 2):
    if A[i] + A[i + 1] > A[i + 2]:
        print(A[i], A[i + 1], A[i + 2])
        break
else:
    print(0, 0, 0)
