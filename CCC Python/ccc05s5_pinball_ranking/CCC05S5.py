import bisect
import sys
import math
input = sys.stdin.readline

large = []
small = []
total = 0.0
N = int(input())
sqrtN = math.sqrt(N)
for i in range(N):
    r = int(input())
    small.append(r)
    largeInd = bisect.bisect_right(large, r)
    total += len(large) - largeInd + sum(x > r for x in small) + 1
    if len(small) > sqrtN:
        large += small
        large.sort()
        small = []
print('%.2f' % (total / N))
