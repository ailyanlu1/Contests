import sys
input = sys.stdin.readline


def gcd(p, q):
    while q != 0:
        p, q = (q, p % q)
    return p


def modInv(n, m):
    a = n
    b = m
    x = 1
    y = 0
    while b != 0:
        q = a // b
        r = a % b
        a = b
        b = r
        q = x - q * y
        x = y
        y = q
    return (x + m) % m


x = int(input())
m = int(input())
if (gcd(x, m) == 1):
    print(modInv(x, m))
else:
    print('No such integer exists.')
