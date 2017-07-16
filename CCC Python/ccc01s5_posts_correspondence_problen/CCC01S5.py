import sys
input = sys.stdin.readline

m = int(input())
n = int(input())
A = [input().strip() for i in range(n)]
B = [input().strip() for i in range(n)]


def solve(a, b, length, moves):
    if length == 0 or not(a.startswith(b) or b.startswith(a)):
        return None
    if a != '' and a == b:
        return moves
    for i in range(n):
        ret = solve(a + A[i], b + B[i], length - 1, moves + [i + 1])
        if ret is not None:
            return ret
    return None


moves = solve('', '', m, [])
if moves is None:
    print('No solution.')
else:
    print(len(moves))
    for i in moves:
        print(i)
