import sys
input = sys.stdin.readline

EPS = 1e-3

N = int(input())
sheep = []
low = [0.00] * N
high = [1000.00] * N
eaten = [True] * N

for i in range(N):
    x = float(input())
    y = float(input())
    sheep.append((x, y))

for i in range(N):
    for j in range(i + 1, N):
        if sheep[i][0] == sheep[j][0]:
            if sheep[i][1] < sheep[j][1]:
                eaten[j] = False
            else:
                eaten[i] = False
            continue
        mid = ((sheep[i][0] + sheep[j][0]) / 2, (sheep[i][1] + sheep[j][1]) / 2)
        intersection = mid[1] * (sheep[j][1] - sheep[i][1]) / (sheep[j][0] - sheep[i][0]) + mid[0]
        if (sheep[i][0] < sheep[j][0]):
            high[i] = min(high[i], intersection)
            low[j] = max(low[j], intersection)
        else:
            low[i] = max(low[i], intersection)
            high[j] = min(high[j], intersection)
    if low[i] > high[i] + EPS:
        eaten[i] = False
for i in range(N):
    if eaten[i]:
        print('The sheep at (%.2f, %.2f) might be eaten.' % sheep[i])
