import sys

R, C = map(int, sys.stdin.readline().split())
K = int(input())
grid = [[0] * (C + 1) for i in range(0, R + 1)]
for i in range(0, K):
    r, c = map(int, sys.stdin.readline().split())
    grid[r][c] = -1
grid[1][1] = 1
for i in range(1, R + 1):
    for j in range(1, C + 1):
        if grid[i][j] != -1:
            grid[i][j] += max(grid[i - 1][j], 0) + max(grid[i][j - 1], 0)
print(grid[R][C])
