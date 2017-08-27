import sys
input = sys.stdin.readline

K = int(input())
grid = ['*x*', ' xx', '* *']
for i in range(3):
    for k in range(K):
        for c in grid[i]:
            print(c * K, end='')
        print()
