import sys
input = sys.stdin.readline


def ccw(p1, p2, p3):
    a2 = (p2[0] - p1[0]) * (p3[1] - p1[1]) - (p2[1] - p1[1]) * (p3[0] - p1[0])
    if a2 < 0:
        return -1
    elif a2 > 0:
        return +1
    else:
        return 0


def intersects(p1, p2, p3, p4):
    if max(p1[0], p2[0]) < min(p3[0], p4[0]) or min(p1[0], p2[0]) > max(p3[0], p4[0]) or \
            max(p1[1], p2[1]) < min(p3[1], p4[1]) or min(p1[1], p2[1]) > max(p3[1], p4[1]):
        return False
    if ccw(p1, p2, p3) * ccw(p1, p2, p4) > 0 or ccw(p3, p4, p1) * ccw(p3, p4, p2) > 0:
        return False
    return True


xr, yr, xj, yj = map(int, input().split())
n = int(input())
cnt = 0
for i in range(n):
    line = list(map(int, input().split()))
    line += line[1:3]
    for j in range(line[0]):
        if intersects((xr, yr), (xj, yj), (line[2 * j + 1], line[2 * j + 2]), (line[2 * j + 3], line[2 * j + 4])):
            cnt += 1
            break
print(cnt)
