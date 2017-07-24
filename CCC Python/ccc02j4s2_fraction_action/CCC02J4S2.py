import sys
input = sys.stdin.readline


def gcd(p, q):
    while q != 0:
        temp = q
        q = p % q
        p = temp
    return p


num = int(input())
den = int(input())

g = gcd(num, den)
num = num // g
den = den // g

if num == 0:
    print(0)
elif den == 1:
    print(num)
elif num < den:
    print(str(num) + '/' + str(den))
else:
    print(str(num // den) + ' ' + str(num % den) + '/' + str(den))
