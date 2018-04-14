import sys
input = sys.stdin.readline

N, M = map(int, input().strip().split())
if N % M == 0:
    print("yes " + str(N // M))
else:
    now = M
    while N % M != 0:
        M += 1
    print("no " + str(M - now))
