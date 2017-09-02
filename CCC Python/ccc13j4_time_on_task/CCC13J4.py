import sys
input = sys.stdin.readline

T = int(input())
C = int(input())
chores = sorted([int(input()) for i in range(C)])
cnt = 0
for c in chores:
    if c > T:
        break
    T -= c
    cnt += 1
print(cnt)
