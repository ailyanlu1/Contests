import sys
input = sys.stdin.readline

stack = []
K = int(input())
for i in range(K):
    x = int(input())
    if x == 0:
        stack.pop()
    else:
        stack.append(x)
print(sum(stack))
