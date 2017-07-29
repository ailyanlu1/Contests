import sys
input = sys.stdin.readline


class WeightedEdge:
    def __init__(self, v, w, weight):
        self.__v = v
        self.__w = w
        self.__weight = weight

    def getWeight(self):
        return self.__weight

    def either(self):
        return self.__v

    def other(self, vertex):
        if vertex == self.__v:
            return self.__w
        elif vertex == self.__w:
            return self.__v
        else:
            raise ValueError('Illegal endpoint')

    def __eq__(self, e):
        return ((self.__v == e.v and self.__w == e.w) or (self.__v == e.w and self.__w == e.v)) and self.__weight == e.weight

    def __ne__(self, e):
        return not (((self.__v == e.v and self.__w == e.w) or (self.__v == e.w and self.__w == e.v)) and self.__weight == e.weight)

    def _lt__(self, e):
        return self.weight < e.weight

    def _le__(self, e):
        return self.weight <= e.weight

    def _gt__(self, e):
        return self.weight > e.weight

    def _ge__(self, e):
        return self.weight >= e.weight


class WeightedGraph:
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

    def addEdge(self, e):
        v = e.either()
        w = e.other(v)
        self.__adjList[v].append(e)
        self.__adjList[w].append(e)
        self.__E += 1

    def adj(self, v):
        return self.__adjList[v]

    def degree(self, v):
        return len(self.__adjList[v])

    def edges(self):
        allEdges = []
        for v in range(self.__V):
            selfLoops = 0
            for e in self.adj(v):
                if e.other(v) > v:
                    allEdges.append(e)
                elif e.other(v) == v:
                    if selfLoops % 2 == 0:
                        allEdges.append(e)
                    selfLoops += 1
        return allEdges


c, r, d = map(int, input().split())
G = WeightedGraph(c)
for i in range(r):
    x, y, w = map(int, input().split())
    G.addEdge(WeightedEdge(x - 1, y - 1, w))
dest = []
for i in range(d):
    dest.append(int(input()) - 1)
maxWeight = [0] * c
for v in range(c):
    for e in G.adj(v):
        maxWeight[e.other(v)] = max(maxWeight[e.other(v)], e.getWeight())
print(min(maxWeight[i] for i in dest))
