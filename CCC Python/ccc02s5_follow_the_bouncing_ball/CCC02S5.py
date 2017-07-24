import sys
import math
input = sys.stdin.readline

width = int(input())
height = int(input())
startX = int(input())
startY = int(input())
slope = startY / (width - startX)
b = -slope * startX
x = 2 * width
while(True):
    y = slope * x + b
    loc = y - math.floor(y / height) * height
    if loc == startY:
        print(0)
        sys.exit()
    elif loc == 0:
        print(int(x / width) + math.floor(y / height) - 2)
        sys.exit()
    elif loc < 5:
        print(int(x / width) + math.floor(y / height) - 1)
        sys.exit()
    x += width
