import sys
input = sys.stdin.readline


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


x, m = map(int, input().split())
print(modInv(x, m))
