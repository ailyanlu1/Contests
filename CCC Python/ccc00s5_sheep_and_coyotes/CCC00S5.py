import sys
input = sys.stdin.readline

N = int(input())
sheep = []
eaten = [False] * N

for i in range(N):
    x = float(input())
    y = float(input())
    sheep.append((x, y))

x = 0.00
while x <= 1000.00:
    ind = 0
    minDist = (sheep[0][0] - x) ** 2 + (sheep[0][1]) ** 2
    for i in range(1, N):
        dist = (sheep[i][0] - x) ** 2 + (sheep[i][1]) ** 2
        if dist < minDist:
            minDist = dist
            ind = i
    eaten[ind] = True
    x += 0.01
for i in range(N):
    if eaten[i]:
        print('The sheep at (%.2f, %.2f) might be eaten.' % sheep[i])
