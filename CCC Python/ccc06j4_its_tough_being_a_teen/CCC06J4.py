import sys
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


G = Digraph(8)
G.addEdge(1, 7)
G.addEdge(1, 4)
G.addEdge(2, 1)
G.addEdge(3, 4)
G.addEdge(3, 5)

a = int(input())
b = int(input())
while a != 0 or b != 0:
    G.addEdge(a, b)
    a = int(input())
    b = int(input())
indegree = [None] * 8
order = []
for v in range(1, 8):
    indegree[v] = G.indegree(v)
while True:
    for v in range(1, 8):
        if indegree[v] == 0:
            indegree[v] -= 1
            for w in G.adj(v):
                indegree[w] -= 1
            order.append(str(v))
            break
    else:
        break
if len(order) == 7:
    print(' '.join(order))
else:
    print('Cannot complete these tasks. Going to bed.')
