from collections import deque
import sys
input = sys.stdin.readline


class Graph:
    def __init__(self, V):
        self.__V = V
        self.__E = 0
        self.__adjSet = []
        for v in range(V):
            self.__adjSet.append(set())

    def V(self):
        return self.__V

    def E(self):
        return self.__E

    def addEdge(self, v, w):
        self.__adjSet[v].add(w)
        self.__adjSet[w].add(v)
        self.__E += 1

    def delEdge(self, v, w):
        self.__adjSet[v].remove(w)
        self.__adjSet[w].remove(v)
        self.__E -= 1

    def adj(self, v):
        return self.__adjSet[v]

    def degree(self, v):
        return len(self.__adjSet[v])


SZ = 50

G = Graph(SZ)
G.addEdge(1, 6)
G.addEdge(2, 6)
G.addEdge(3, 4)
G.addEdge(3, 5)
G.addEdge(3, 6)
G.addEdge(3, 15)
G.addEdge(4, 5)
G.addEdge(4, 6)
G.addEdge(5, 6)
G.addEdge(6, 7)
G.addEdge(7, 8)
G.addEdge(8, 9)
G.addEdge(9, 10)
G.addEdge(9, 12)
G.addEdge(10, 11)
G.addEdge(11, 12)
G.addEdge(12, 13)
G.addEdge(13, 14)
G.addEdge(13, 15)
G.addEdge(16, 17)
G.addEdge(16, 18)
G.addEdge(17, 18)


def bfs(s, t):
    marked = [False] * G.V()
    distTo = [float('inf')] * G.V()
    q = deque()
    distTo[s] = 0
    marked[s] = True
    q.append(s)
    while len(q) != 0:
        v = q.popleft()
        if v == t:
            print(distTo[t])
            return
        for w in G.adj(v):
            if not marked[w]:
                distTo[w] = distTo[v] + 1
                marked[w] = True
                q.append(w)
    print('Not connected')


c = input().strip()
while (c != 'q'):
    if c == 'i':
        G.addEdge(int(input()), int(input()))
    elif c == 'd':
        G.delEdge(int(input()), int(input()))
    elif c == 'n':
        print(G.degree(int(input())))
    elif c == 'f':
        fof = set()
        friends = set()
        x = int(input())
        friends.add(x)
        for v in G.adj(x):
            friends.add(v)
            if v in fof:
                fof.remove(v)
            for w in G.adj(v):
                if w not in friends:
                    fof.add(w)
        print(len(fof))
    else:
        bfs(int(input()), int(input()))
    c = input().strip()
