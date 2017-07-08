import sys

MAXM = 50
total = 0
peg = [0] * (MAXM + 1)
moves = 0
for i in range(0, 3):
    line = sys.stdin.readline().split()
    m = int(line[0])
    total += m
    prevNum = MAXM + 1
    for j in range(1, m + 1):
        num = int(line[j])
        if num >= prevNum:
            print('No')
            sys.exit()
        peg[num] = i
        prevNum = num
blockedPeg = 1
incPeg = 0
for i in range(total, 0, -1):
    if peg[i] == blockedPeg:
        print('No')
        sys.exit()
    moves *= 2
    if peg[i] == incPeg:
        moves += 1
    else:
        incPeg = blockedPeg
    blockedPeg = 3 - peg[i] - blockedPeg
print(moves)
