import sys
input = sys.stdin.readline

lo = int(input())
hi = int(input())

cnt = 0
for x in range(lo, hi + 1):
    cntDivisors = 0
    for y in range(1, x + 1):
        if x % y == 0:
            cntDivisors += 1
            if cntDivisors > 4:
                break
    if cntDivisors == 4:
        cnt += 1
print('The number of RSA numbers between ' + str(lo) + ' and ' + str(hi) + ' is ' + str(cnt))
