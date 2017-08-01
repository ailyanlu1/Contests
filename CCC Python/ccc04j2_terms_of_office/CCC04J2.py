import sys
input = sys.stdin.readline

X = int(input())
Y = int(input())
while X <= Y:
    print('All positions change in year ' + str(X))
    X += 60
