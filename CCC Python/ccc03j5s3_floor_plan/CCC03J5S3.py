import sys
input = sys.stdin.readline

N = int(input())
R = int(input())
C = int(input())
grid = []
for i in range(R):
    grid.append(input().strip())


def isPoint(i, j):
    return i >= 0 and i < R and j >= 0 and j < C


def toPoint(i, j):
    return i * C + j


def getI(p):
    return p // C


def getJ(p):
    return p % C


class Graph:
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
        self.__adjList[w].append(v)
        self.__E += 1

    def adj(self, v):
        return self.__adjList[v]

    def degree(self, v):
        return len(self.__adjList[v])


class ConnectedComponents:
    def __init__(self, G):
        self.marked = [False] * G.V()
        self.id = [0] * G.V()
        self.size = [0] * G.V()
        self.count = 0
        for v in range(G.V()):
            if not self.marked[v] and grid[getI(v)][getJ(v)] == '.':
                self.__dfs(G, v)
                self.count += 1

    def __dfs(self, G, v):
        self.marked[v] = True
        self.id[v] = self.count
        self.size[self.count] += 1
        for w in G.adj(v):
            if not self.marked[w]:
                self.__dfs(G, w)


G = Graph(R * C)

for i in range(R):
    for j in range(C):
        if grid[i][j] == '.':
            if isPoint(i, j + 1) and grid[i][j + 1] == '.':
                G.addEdge(toPoint(i, j), toPoint(i, j + 1))
            if isPoint(i, j - 1) and grid[i][j - 1] == '.':
                G.addEdge(toPoint(i, j), toPoint(i, j - 1))
            if isPoint(i + 1, j) and grid[i + 1][j] == '.':
                G.addEdge(toPoint(i, j), toPoint(i + 1, j))
            if isPoint(i - 1, j) and grid[i - 1][j] == '.':
                G.addEdge(toPoint(i, j), toPoint(i - 1, j))

cc = ConnectedComponents(G)
size = sorted(cc.size, reverse=True)
rooms = 0
for i in range(cc.count):
    if N - size[i] < 0:
        break
    rooms += 1
    N -= size[i]
if rooms == 1:
    print(str(rooms) + ' room', end='')
else:
    print(str(rooms) + ' rooms', end='')
print(', ' + str(N) + ' square metre(s) left over')
