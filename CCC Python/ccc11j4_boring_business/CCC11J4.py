import sys
input = sys.stdin.readline

MAX = 200
grid = [[False for j in range(MAX * 2 + 1)] for i in range(MAX * 2 + 1)]
moves = ((0, 1), (1, 0), (0, -1), (-1, 0))


def mark(sx, sy, ex, ey):
    for x in range(min(sx, ex), max(sx, ex) + 1):
        for y in range(min(sy, ey), max(sy, ey) + 1):
            grid[x + MAX][y + MAX] = True


mark(0, -1, 0, -3)
mark(0, -3, 3, -3)
mark(3, -3, 3, -5)
mark(5, -5, 5, -3)
mark(5, -3, 7, -3)
mark(7, -3, 7, -7)
mark(7, -7, -1, -7)
mark(-1, -7, -1, -5)
cx = -1
cy = -5
while(True):
    line = list(input().strip().split())
    c = line[0]
    l = int(line[1])
    if c == 'u':
        d = 0
    elif c == 'r':
        d = 1
    elif c == 'd':
        d = 2
    elif c == 'l':
        d = 3
    else:
        break
    for i in range(1, l + 1):
        if grid[cx + moves[d][0] * i + MAX][cy + moves[d][1] * i + MAX]:
            print(str(cx + moves[d][0] * l) + ' ' + str(cy + moves[d][1] * l) + ' DANGER')
            sys.exit(0)
        grid[cx + moves[d][0] * i + MAX][cy + moves[d][1] * i + MAX] = True
    cx += moves[d][0] * l
    cy += moves[d][1] * l
    print(str(cx) + ' ' + str(cy) + ' safe')
