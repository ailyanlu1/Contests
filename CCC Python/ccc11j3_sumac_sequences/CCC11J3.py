import sys
input = sys.stdin.readline

t1 = int(input())
t2 = int(input())
cnt = 2
while t1 >= t2:
    temp = t1 - t2
    t1 = t2
    t2 = temp
    cnt += 1
print(cnt)
