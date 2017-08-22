from collections import deque
import sys
input = sys.stdin.readline


class Digraph:
    def __init__(self, V):
        self.__V = V
        self.__E = 0
        self.__adjList = []
        for v in range(V):
            self.__adjList.append([])

    def V(self):
        return self.__V

    def E(self):
        return self.__E

    def addEdge(self, v, w):
        self.__adjList[v].append(w)
        self.__E += 1

    def adj(self, v):
        return self.__adjList[v]


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


MAXX = 10000
G = Digraph(MAXX)
n = int(input())
for i in range(n):
    x, y = map(int, input().strip().split())
    G.addEdge(x, y)
x, y = map(int, input().strip().split())
while (x, y) != (0, 0):
    bfs = BreadthFirstSearch(G, x)
    if bfs.hasPathTo(y):
        print('Yes ' + str(bfs.getDistTo(y) - 1))
    else:
        print('No')
    x, y = map(int, input().strip().split())
