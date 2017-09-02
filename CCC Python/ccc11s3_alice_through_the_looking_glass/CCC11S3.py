import sys
input = sys.stdin.readline

base = ((1, 0), (2, 0), (2, 1), (3, 0))
layer = ((1, 1), (2, 2), (3, 1))


def solve(m, x, y):
    cur = (x // m, y // m)
    if cur in base:
        return True
    elif m >= 5 and cur in layer:
        return solve(m // 5, x % m, y % m)
    else:
        return False


T = int(input())
for i in range(T):
    m, x, y = map(int, input().strip().split())
    print('crystal' if solve(pow(5, m - 1), x, y) else 'empty')
