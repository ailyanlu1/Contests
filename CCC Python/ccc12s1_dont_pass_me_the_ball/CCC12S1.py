import sys
input = sys.stdin.readline

J = int(input())
print((J - 1) * (J - 2) * (J - 3) // 6)
