import sys
input = sys.stdin.readline

N = int(input())
T = int(input())
weight = [[0 for i in range(N)] for i in range(N)]
for i in range(T):
    u, v, w = map(int, input().strip().split())
    weight[u - 1][v - 1] = weight[v - 1][u - 1] = w
distTo = [float('inf')] * N
K = int(input())
for i in range(K):
    z, p = map(int, input().strip().split())
    distTo[z - 1] = p
D = int(input()) - 1
marked = [False] * N
for v in range(N - 1):
    minV = -1
    for w in range(N):
        if not marked[w] and (minV == -1 or distTo[minV] > distTo[w]):
            minV = w
    if minV == D:
        break
    marked[minV] = True
    for w in range(N):
        if weight[minV][w] != 0:
            distTo[w] = min(distTo[w], distTo[minV] + weight[minV][w])
print(distTo[D])
