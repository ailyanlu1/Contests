import sys
input = sys.stdin.readline

r = int(input())
c = int(input())
grid = [[' '] * c for i in range(r)]
for i in range(r):
    line = input().strip()
    for j in range(c):
        grid[i][j] = line[j]
m = int(input())
moves = [' '] * m
for i in range(m):
    moves[i] = input().strip()

for i in range(r):
    for j in range(c):
        if grid[i][j] != 'X':
            for d in range(4):
                curI = i
                curJ = j
                for k in moves:
                    if k == 'F':
                        if d == 0:
                            curI -= 1
                        elif d == 1:
                            curJ += 1
                        elif d == 2:
                            curI += 1
                        else:  # d == 3
                            curJ -= 1
                    elif k == 'L':
                        d = (d + 3) % 4
                    else:  # k == 'R'
                        d = (d + 1) % 4
                    if curI < 0 or curI >= r or curJ < 0 or curJ >= c or grid[curI][curJ] == 'X':
                        break
                else:
                    grid[curI][curJ] = '*'
print('\n'.join(''.join(row) for row in grid))
