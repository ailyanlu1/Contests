import sys
input = sys.stdin.readline


class UF:
    def __init__(self, n):
        self._count = n
        self._parent = [i for i in range(n)]
        self._rank = [0] * n

    def find(self, p):
        while (p != self._parent[p]):
            self._parent[p] = self._parent[self._parent[p]]
            p = self._parent[p]
        return p

    def count(self):
        return self._count

    def connected(self, p, q):
        return self.find(p) == self.find(q)

    def rank(self, p):
        return self._rank[self.find(p)]

    def union(self, p, q):
        rootP = self.find(p)
        rootQ = self.find(q)
        if rootP == rootQ:
            return
        if self._rank[rootP] < self._rank[rootQ]:
            self._parent[rootP] = rootQ
        elif self._rank[rootP] > self._rank[rootQ]:
            self._parent[rootQ] = rootP
        else:
            self._parent[rootQ] = rootP
            self._rank[rootP] += 1
        self._count -= 1

    def disjoin(self, p, q):
        rootP = self.find(p)
        rootQ = self.find(q)
        if self._rank[rootP] < self._rank[rootQ]:
            self._parent[rootP] = rootP
        elif self._rank[rootP] > self._rank[rootQ]:
            self._parent[rootQ] = rootQ
        else:
            self._parent[rootQ] = rootP
            self._rank[rootP] -= 1
        self._count += 1


edges = []
disconnected = []
count = 0
line = input().strip()
while line != '**':
    edges.append((ord(line[0]) - ord('A'), ord(line[1]) - ord('A')))
    line = input().strip()
for e in edges:
    uf = UF(26)
    for f in edges:
        if e != f:
            uf.union(f[0], f[1])
    if not uf.connected(0, 1):
        count += 1
        disconnected.append(e)
for e in disconnected:
    print(chr(e[0] + ord('A')) + chr(e[1] + ord('A')))
print('There are ' + str(count) + ' disconnecting roads.')
