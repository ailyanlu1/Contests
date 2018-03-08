import sys
from collections import deque
input = sys.stdin.readline


class Digraph:
    def __init__(self, V):
        self.__V = V
        self.__E = 0
        self.__adjList = []
        for v in range(V):
            self.__adjList.append([])
        self.__indegreeArr = [0] * V

    def V(self):
        return self.__V

    def E(self):
        return self.__E

    def addEdge(self, v, w):
        self.__adjList[v].append(w)
        self.__indegreeArr[w] += 1
        self.__E += 1

    def adj(self, v):
        return self.__adjList[v]

    def outdegree(self, v):
        return len(self.__adjList[v])

    def indegree(self, v):
        return self.__indegreeArr[v]


class BreadthFirstSearch:
    def __init__(self, G, s):
        self.__marked = [False] * G.V()
        self.__distTo = [float('inf')] * G.V()
        self.__bfs(G, s)

    def __bfs(self, G, s):
        q = deque()
        self.__distTo[s] = 0
        self.__marked[s] = True
        q.append(s)
        while len(q) != 0:
            v = q.popleft()
            for w in G.adj(v):
                if not self.__marked[w]:
                    self.__distTo[w] = self.__distTo[v] + 1
                    self.__marked[w] = True
                    q.append(w)

    def getDistTo(self, v):
        return self.__distTo[v]

    def hasPathTo(self, v):
        return self.__marked[v]


N = int(input())
finish = []
G = Digraph(N)
for i in range(N):
    M = list(map(int, input().strip().split()))
    if (M[0] == 0):
        finish.append(i)
    for j in range(1, M[0] + 1):
        G.addEdge(i, M[j] - 1)

bfs = BreadthFirstSearch(G, 0)
reachable = True
for i in range(N):
    if (not bfs.hasPathTo(i)):
        reachable = False
        break
if reachable:
    print("Y")
else:
    print("N")
shortest = float('inf')
for i in finish:
    shortest = min(shortest, bfs.getDistTo(i))
print(shortest + 1)
