import sys
import math
input = sys.stdin.readline

c = int(input())
while c != 0:
    sqrtC = int(math.sqrt(c))
    while (c % sqrtC != 0):
        sqrtC -= 1
    w = int(c / sqrtC)
    print('Minimum perimeter is ' + str(2 * (sqrtC + w)) + ' with dimensions ' + str(sqrtC) + ' x ' + str(w))
    c = int(input())
