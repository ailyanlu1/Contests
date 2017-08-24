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

    def outdegree(self, v):
        return len(self.__adjList[v])


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


R = 0
C = 0


def isPoint(r, c):
    return r >= 0 and r < R and c >= 0 and c < C


def toPoint(r, c):
    return r * C + c


T = int(input())
for t in range(T):
    R = int(input())
    C = int(input())
    G = Digraph(R * C)
    endBlocked = False
    for r in range(R):
        line = input().strip()
        for c in range(C):
            if (line[c] == '+' or line[c] == '|') and isPoint(r - 1, c):
                G.addEdge(toPoint(r, c), toPoint(r - 1, c))
            if (line[c] == '+' or line[c] == '|') and isPoint(r + 1, c):
                G.addEdge(toPoint(r, c), toPoint(r + 1, c))
            if (line[c] == '+' or line[c] == '-') and isPoint(r, c - 1):
                G.addEdge(toPoint(r, c), toPoint(r, c - 1))
            if (line[c] == '+' or line[c] == '-') and isPoint(r, c + 1):
                G.addEdge(toPoint(r, c), toPoint(r, c + 1))
            if r == R - 1 and c == C - 1 and line[c] == '*':
                endBlocked = True
    if endBlocked:
        print(-1)
        continue
    bfs = BreadthFirstSearch(G, 0)
    if bfs.hasPathTo(R * C - 1):
        print(bfs.getDistTo(R * C - 1) + 1)
    else:
        print(-1)
