from collections import deque
import sys
input = sys.stdin.readline

song = deque(['A', 'B', 'C', 'D', 'E'])
b = int(input())
n = int(input())
while (b, n) != (4, 1):
    if b == 1:
        song.rotate(-n)
    elif b == 2:
        song.rotate(n)
    elif b == 3:
        temp = song[0]
        song[0] = song[1]
        song[1] = temp
    b = int(input())
    n = int(input())
print(' '.join(song))
