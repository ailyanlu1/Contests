import sys


def bfs(adj, N, s, t):
    m = []
    d = []
    for r in range(N):
        m.append(False)
        d.append(999999)
    d[s] = 0
    m[s] = True
    queue = []
    queue.append(s)
    while len(queue) > 0:
        v = queue.pop(0)
        if (v == t):
            return d[t]
        for w in adj[v]:
            if (not m[w]):
                m[w] = True
                d[w] = d[v] + 1
                queue.append(w)
    return False


N = 8

line = sys.stdin.readline().strip().split()
A = (int(line[0]) - 1) * N + (int(line[1]) - 1)

line = sys.stdin.readline().strip().split()
B = (int(line[0]) - 1) * N + (int(line[1]) - 1)

adj = []
for i in range(N):
    for j in range(N):
        row = []
        adj.append(row)

moves = [[1, 2], [1, -2], [-1, 2], [-1, -2], [2, 1], [2, -1], [-2, 1], [-2, -1]]

for i in range(N):
    for j in range(N):
        for k in moves:
            if ((i + k[0]) >= 0 and (i + k[0]) < N and (j + k[1]) >= 0 and (j + k[1]) < N):
                adj[i * N + j].append((i + k[0]) * N + (j + k[1]))

print(bfs(adj, N * N, A, B))
