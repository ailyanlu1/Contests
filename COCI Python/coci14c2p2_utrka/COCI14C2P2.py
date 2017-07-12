import sys
input = sys.stdin.readline

N = int(input())
start = sorted([input().strip() for i in range(N)])
finish = sorted([input().strip() for i in range(N - 1)])
for a, b in zip(start, finish):
    if a != b:
        print(a)
        break
else:
    print(start[-1])
