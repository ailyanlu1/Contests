import sys


def taller(a, N, p, q):
    # v is a "visited" list for track (don't go to same guy twice)
    v = []
    for r in range(N):
        v.append(False)
    queue = []
    for x in a[p]:
        queue.append(x)
    while len(queue) > 0:
        h = queue.pop(0)
        if h == q:
            return True
        if not v[h]:
            v[h] = True
            for x in a[h]:
                queue.append(x)
    return False


x = sys.stdin.readline().strip().split()
N = int(x[0])
M = int(x[1])

# a is the main array holding all the links
a = []
for r in range(N):
    row = []
    a.append(row)


for i in range(M):
    x = sys.stdin.readline().strip().split()
    p = int(x[0]) - 1
    q = int(x[1]) - 1
    a[p].append(q)

x = sys.stdin.readline().strip().split()
p = int(x[0]) - 1
q = int(x[1]) - 1

if taller(a, N, p, q):
    print("yes")
elif taller(a, N, q, p):
    print("no")
else:
    print("unknown")
