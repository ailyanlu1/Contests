import sys
input = sys.stdin.readline

ROWS = 5
COLS = 6
curR = 0
curC = 0
moves = 0
word = input().strip() + '~'
for char in word:
    r = ROWS - 1
    c = COLS - 1
    if char == ' ':
        c = 2
    elif char == '-':
        c = 3
    elif char == '.':
        c = 4
    elif char == '~':
        c = 5
    else:
        r = (ord(char) - ord('A')) // COLS
        c = (ord(char) - ord('A')) % COLS
    moves += abs(curR - r) + abs(curC - c)
    curR = r
    curC = c
print(moves)
