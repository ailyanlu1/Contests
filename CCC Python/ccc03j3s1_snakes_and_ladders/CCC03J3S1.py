import sys
input = sys.stdin.readline

moves = {54: 19, 90: 48, 99: 77, 9: 34, 40: 64, 67: 86}

cur = 1
n = int(input())
while n != 0:
    if cur + n <= 100:
        cur = moves.get(cur + n, cur + n)
    print('You are now on square ' + str(cur))
    if cur == 100:
        break
    n = int(input())
if cur == 100:
    print('You Win!')
if n == 0:
    print('You Quit!')
