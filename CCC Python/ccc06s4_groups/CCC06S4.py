import sys
input = sys.stdin.readline


class BreakException(Exception):
    pass


while True:
    N = int(input())
    if N == 0:
        break
    table = [[0] * (N + 1)] + [[0] + list(map(int, input().split())) for i in range(N)]
    try:
        for x in range(1, N + 1):
            for y in range(1, N + 1):
                for z in range(1, N + 1):
                    if table[x][table[y][z]] != table[table[x][y]][z]:
                        raise BreakException
    except BreakException:
        print('no')
        continue
    i = 0
    for x in range(1, N + 1):
        for y in range(1, N + 1):
            if table[x][y] != y:
                break
        else:
            i = x
            break
    else:
        print('no')
        continue
    for x in range(1, N + 1):
        for y in range(1, N + 1):
            if table[x][y] == i:
                break
        else:
            break
    else:
        print('yes')
        continue
    print('no')
