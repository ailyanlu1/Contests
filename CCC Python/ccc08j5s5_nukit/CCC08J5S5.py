import sys
input = sys.stdin.readline

MAX = 31
reactions = ((2, 1, 0, 2), (1, 1, 1, 1), (0, 0, 2, 1), (0, 3, 0, 0), (1, 0, 0, 1))
dp = [[[[False for d in range(MAX)] for c in range(MAX)] for b in range(MAX)] for a in range(MAX)]
n = int(input())
for t in range(n):
    A, B, C, D = map(int, input().strip().split())
    for a in range(A + 1):
        for b in range(B + 1):
            for c in range(C + 1):
                for d in range(D + 1):
                    dp[a][b][c][d] = False
                    for r in reactions:
                        if a >= r[0] and b >= r[1] and c >= r[2] and d >= r[3] and not dp[a - r[0]][b - r[1]][c - r[2]][d - r[3]]:
                            dp[a][b][c][d] = True
    print('Patrick' if dp[A][B][C][D] else 'Roland')
