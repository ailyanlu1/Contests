import sys
import math
input = sys.stdin.readline

DIR = [[1, 0], [0, 1], [-1, 0], [0, -1]]
start = int(input())
end = int(input())

diff = end - (start - 1)
diffSqrt = math.sqrt(diff)
height = math.ceil(diffSqrt)
width = round(diffSqrt)

grid = [[0 for j in range(width)] for i in range(height)]

curNum = start
curI = (height + 1) // 2 - 1
curJ = (width + 1) // 2 - 1

d = 0
length = 1
while curNum <= end:
    for i in range(length):
        if curNum > end:
            break
        grid[curI][curJ] = curNum
        curI += DIR[d][0]
        curJ += DIR[d][1]
        curNum += 1
    d = (d + 1) % 4
    if d % 2 == 0:
        length += 1

for i in range(height):
    for j in range(width):
        if grid[i][j] != 0:
            print(grid[i][j], end=' ')
    print()
