import sys
import math
input = sys.stdin.readline


def dist(a, b):
    return math.sqrt((a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2)


points = []
N = int(input())
for i in range(N):
    x, y = map(float, input().split())
    points.append((x, y))
diameter = 0.0
for x in range(N):
    for y in range(x + 1, N):
        for z in range(y + 1, N):
            a = dist(points[x], points[y])
            b = dist(points[y], points[z])
            c = dist(points[z], points[x])
            s = (a + b + c) / 2
            if a ** 2 + b ** 2 < c ** 2 or b ** 2 + c ** 2 < a ** 2 or c ** 2 + a ** 2 < b ** 2:
                diameter = max(diameter, max(a, max(b, c)))
            else:
                area = math.sqrt(s * (s - a) * (s - b) * (s - c))
                diameter = max(diameter, (a * b * c) / (2 * area))
print('%.2f' % diameter)
