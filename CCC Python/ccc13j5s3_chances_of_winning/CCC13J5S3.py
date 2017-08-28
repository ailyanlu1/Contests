import sys
from itertools import combinations
input = sys.stdin.readline

T = int(input()) - 1
G = int(input())
points = [0] * 4
matches = set(combinations([0, 1, 2, 3], 2))


def solve(ind, points):
    if ind == len(matches):
        maxPoints = -1
        maxInd = 0
        maxCnt = 0
        for i in range(len(points)):
            if points[i] > maxPoints:
                maxPoints = points[i]
                maxInd = i
                maxCnt = 1
            elif points[i] == maxPoints:
                maxCnt += 1
        return 1 if maxInd == T and maxCnt == 1 else 0
    ret = 0
    a, b = matches[ind]
    # A win
    temp = list(points)
    temp[a] += 3
    ret += solve(ind + 1, temp)
    # B win
    temp = list(points)
    temp[b] += 3
    ret += solve(ind + 1, temp)
    # Draw
    temp = list(points)
    temp[a] += 1
    temp[b] += 1
    ret += solve(ind + 1, temp)
    return ret


for i in range(G):
    A, B, SA, SB = map(int, input().strip().split())
    A -= 1
    B -= 1
    matches.remove((A, B))
    if SA > SB:
        points[A] += 3
    elif SA < SB:
        points[B] += 3
    else:
        points[A] += 1
        points[B] += 1
matches = list(matches)
print(solve(0, points))
