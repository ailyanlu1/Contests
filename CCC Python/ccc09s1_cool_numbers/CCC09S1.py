import sys
input = sys.stdin.readline

a = int(input())
b = int(input())
print(int(pow(b + 1, 1.0 / 6.0)) - int(pow(a - 1, 1.0 / 6.0)))
