import sys
input = sys.stdin.readline

perm = (0, 1, 0, 1, 2, 1, 2, 3, 2, 3, 0, 3)
dir = ((1, 0), (0, 1), (-1, 0), (0, -1))

W = int(input())
H = int(input())
C = (int(input()), int(input()))  # 0 is W, 1 is H
length = [W - 2 * C[0] - 1, H - 2 * C[1] - 1]  # 0 is hor, 1 is ver
steps = int(input())

cur = [C[0] + 1, 1]
d = 0
dirCnt = 0
first = True
for i in range(steps):
    if d == 0 and length[0] <= 0:
        d = 1
        dirCnt = 0
    if d == 6 and length[0] <= 0 or d == 3 and length[1] <= 0:
        break
    cur[0] += dir[perm[d]][0]
    cur[1] += dir[perm[d]][1]
    dirCnt += 1
    if not first and d == 0 and dirCnt == length[perm[d] % 2] - 1:
        d = 1
        dirCnt = 0
        length[0] -= 2
        length[1] -= 2
    if d == 11 and dirCnt == C[perm[d] % 2] - 1:
        d = 0
        dirCnt = 0
    if d % 3 == 0 and dirCnt == length[perm[d] % 2]:
        first = False
        d += 1
        dirCnt = 0
    if d % 3 != 0 and dirCnt == C[perm[d] % 2]:
        d += 1
        dirCnt = 0
print(cur[0])
print(cur[1])
