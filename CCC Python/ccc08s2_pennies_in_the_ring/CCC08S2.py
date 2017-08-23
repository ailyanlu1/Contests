import sys
import math
input = sys.stdin.readline

n = int(input())
while (n != 0):
    cnt = n
    for x in range(1, n):
        cnt += int(math.sqrt(n * n - x * x))
    print(cnt * 4 + 1)
    n = int(input())
