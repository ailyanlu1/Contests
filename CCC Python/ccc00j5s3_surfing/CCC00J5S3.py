import sys
import re
input = sys.stdin.readline

linkRegex = re.compile('<A HREF=\"([^\"]*)\">')


class Digraph:
    def __init__(self, V):
        self.__V = V
        self.__E = 0
        self.__adjList = {}
        self.__indegreeArr = {}

    def getV(self):
        return self.__V

    def getE(self):
        return self.__E

    def addEdge(self, v, w):
        self.__adjList[v] = self.__adjList.get(v, []) + [w]
        self.__indegreeArr[w] = self.__indegreeArr.get(w, 0) + 1
        self.__E += 1

    def adj(self, v):
        return self.__adjList.get(v, [])

    def outdegree(self, v):
        return len(self.__adjList.get(v, []))

    def indegree(self, v):
        return self.__indegreeArr.get(v, 0)


class DepthFirstSearch:
    def __init__(self, G, s):
        self.__marked = set()
        self.__dfs(G, s)

    def __dfs(self, G, v):
        self.__marked.add(v)
        for w in G.adj(v):
            if w not in self.__marked:
                self.__dfs(G, w)

    def hasPathTo(self, v):
        return v in self.__marked


n = int(input())
G = Digraph(n)
for i in range(n):
    linkFrom = input().strip()
    line = input().strip()
    while '</HTML>' not in line:
        for linkTo in re.findall(linkRegex, line):
            G.addEdge(linkFrom, linkTo)
            print('Link from ' + linkFrom + ' to ' + linkTo)
        line = input().strip()
while True:
    linkFrom = input().strip()
    if linkFrom == 'The End':
        break
    linkTo = input().strip()
    dfs = DepthFirstSearch(G, linkFrom)
    if (dfs.hasPathTo(linkTo)):
        print('Can surf from ' + linkFrom + ' to ' + linkTo + '.')
    else:
        print("Can't surf from " + linkFrom + ' to ' + linkTo + '.')
