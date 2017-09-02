import sys
input = sys.stdin.readline

MAXX = 105

M = int(input())
cur = 0
state = [0] * MAXX
sendTime = [0] * MAXX
totTime = [0] * MAXX

for i in range(M):
    line = input().strip().split()
    c = line[0]
    X = int(line[1])
    if c == 'W':
        cur += X - 1
    elif c == 'R':
        state[X] = -1
        sendTime[X] = cur
        cur += 1
    else:
        state[X] = 1
        totTime[X] += cur - sendTime[X]
        cur += 1
for i in range(MAXX):
    if state[i] == 1:
        print(str(i) + ' ' + str(totTime[i]))
    elif state[i] == -1:
        print(str(i) + ' -1')
