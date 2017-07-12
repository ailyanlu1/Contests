import sys
input = sys.stdin.readline

N = int(input())
C = set()
for i in range(2 * N - 1):
    C ^= {input().strip()}
print(C.pop())
