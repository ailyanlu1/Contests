import sys
input = sys.stdin.readline

Y = int(input())
while True:
    Y += 1
    if len(set(str(Y))) == len(str(Y)):
        break
print(Y)
