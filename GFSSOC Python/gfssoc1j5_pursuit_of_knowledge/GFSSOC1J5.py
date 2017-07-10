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

    def getV(self):
        return self.__V

    def getE(self):
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
        return self.__indegree[v]


class BreadthFirstSearch:
    def __init__(self, G, s):
        self.__marked = [False] * G.getV()
        self.__distTo = [float('inf')] * G.getV()
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
                    self.__distTo[w] = self.__distTo[v] + T
                    self.__marked[w] = True
                    q.append(w)

    def getDistTo(self, v):
        return self.__distTo[v]


N, M, T = map(int, input().split())
G = Digraph(N)
bfs = [None] * N
for i in range(M):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    G.addEdge(a, b)
for i in range(N):
    bfs[i] = BreadthFirstSearch(G, i)
Q = int(input())
for i in range(Q):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    ans = bfs[a].getDistTo(b)
    if ans == float('inf'):
        print('Not enough hallways!')
    else:
        print(ans)
