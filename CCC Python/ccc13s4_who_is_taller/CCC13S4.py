from collections import deque
import sys
input = sys.stdin.readline


def bfs(s, t):
    marked = [False] * N
    if s == t:
        return True
    q = deque()
    marked[s] = True
    q.append(s)
    while len(q) != 0:
        v = q.popleft()
        for w in adj[v]:
            if not marked[w]:
                if w == t:
                    return True
                marked[w] = True
                q.append(w)
    return False


N, M = map(int, input().split())
adj = []
for i in range(N):
    adj.append([])

for i in range(M):
    x, y = map(int, input().split())
    adj[x - 1].append(y - 1)

p, q = map(int, input().split())

if bfs(p - 1, q - 1):
    print("yes")
elif bfs(q - 1, p - 1):
    print("no")
else:
    print("unknown")
