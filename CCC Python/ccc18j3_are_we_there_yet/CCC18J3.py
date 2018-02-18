import sys
input = sys.stdin.readline

D = list(map(int, input().strip().split()))
dist = [[0 for j in range(5)] for i in range(5)]

for i in range(5):
    for j in range(i + 1, 5, 1):
        dist[i][j] = dist[i][j - 1] + D[j - 1]
    for j in range(i - 1, -1, -1):
        dist[i][j] = dist[i][j + 1] + D[j]

print('\n'.join(' '.join(str(j) for j in i) for i in dist))
