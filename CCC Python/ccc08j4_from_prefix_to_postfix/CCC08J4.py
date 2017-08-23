import sys
input = sys.stdin.readline

line = input().strip()
while line != '0':
    stack = []
    for c in reversed(line.split()):
        if c == '+' or c == '-':
            a = stack.pop()
            b = stack.pop()
            stack.append(a + b + c + ' ')
        else:
            stack.append(c + ' ')
    print(stack[-1])
    line = input().strip()
