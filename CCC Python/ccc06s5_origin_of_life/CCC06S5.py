import sys
from collections import deque
input = sys.stdin.readline

moves = ((0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1))

M, N, A, B, C = map(int, input().split())
vis = set()
adj = [[] for i in range(1 << (M * N))]


def to1D(i, j):
    return i * N + j


s = 0
for i in range(M):
    line = input().strip()
    for j in range(len(line)):
        if line[j] == '*':
            s |= (1 << to1D(i, j))
for state in range(1 << (M * N)):
    nxt = state
    for i in range(M):
        for j in range(N):
            cnt = 0
            for k in moves:
                m = i + k[0]
                n = j + k[1]
                if m < 0 or m >= M or n < 0 or n >= N:
                    continue
                if state & (1 << to1D(m, n)):
                    cnt += 1
            if state & (1 << to1D(i, j)):
                if cnt < A or cnt > B:
                    nxt &= ~(1 << to1D(i, j))
            else:
                if cnt > C:
                    nxt |= (1 << to1D(i, j))
    if nxt != state:
        adj[nxt].append(state)
ans = -1
q = deque()
q.append((s, 0))
while len(q) != 0:
    cur = q.popleft()
    if cur[0] in vis:
        continue
    vis.add(cur[0])
    if len(adj[cur[0]]) == 0:
        ans = cur[1]
        break
    for nxt in adj[cur[0]]:
        q.append((nxt, cur[1] + 1))
print(ans)
