import sys
input = sys.stdin.readline

a = int(input())
b = int(input())
c = int(input())
d = int(input())

if a >= 8 and d >= 8 and b == c:
    print("ignore")
else:
    print("answer")
