import sys
input = sys.stdin.readline

a, b = map(int, input().strip().split())
c, d = map(int, input().strip().split())
t = int(input())
dist = abs(a - c) + abs(b - d)
print('Y' if dist <= t and (t - dist) % 2 == 0 else 'N')
