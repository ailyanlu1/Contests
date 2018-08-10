import sys
input = sys.stdin.readline
print((1 if int(input()) > 0 else 4) if int(input()) > 0 else (2 if int(input()) > 0 else 3))
