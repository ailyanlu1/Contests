import sys
input = sys.stdin.readline


def solve(a, b):
    ret = []
    for i in range(len(a)):
        if a[i] == b[i]:
            ret.append('0')
        else:
            ret.append('1')
    return ''.join(ret)


R = int(input())
L = int(input())
lights = [input().strip().replace(' ', '') for i in range(R)]
possible = set([lights[0]])
for i in range(1, R):
    temp = set([lights[i]])
    for row in possible:
        temp.add(solve(lights[i], row))
    possible = temp
print(len(possible))
