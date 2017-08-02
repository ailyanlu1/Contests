import sys
input = sys.stdin.readline

rate = 10

N = int(input())
for i in range(N):
    L = int(input())
    names = [input() for j in range(L)]
    depth = 0
    stack = []
    stack.append((names[-1], 0))
    for name in names:
        if len(stack) >= 2 and name == stack[-2][0]:
            stack.pop()
        else:
            stack.append((name, stack[-1][1] + 1))
            depth = max(depth, stack[-1][1])
    print(L * rate - depth * 2 * rate)
