import sys
input = sys.stdin.readline

q = int(input())
a = int(input())
b = int(input())
c = int(input())

cur = 0
count = 0

while q > 0:
    count += 1
    q -= 1
    if cur == 0:
        a += 1
        if a % 35 == 0:
            q += 30
    elif cur == 1:
        b += 1
        if b % 100 == 0:
            q += 60
    else:
        c += 1
        if c % 10 == 0:
            q += 9
    cur = (cur + 1) % 3
print('Martha plays ' + str(count) + ' times before going broke.')
