import sys

curDay, days = map(int, sys.stdin.readline().split())
curDay -= 1
cur = 1

print('Sun Mon Tue Wed Thr Fri Sat')

for i in range(0, curDay):
    print('    ', end='')

while cur <= days:
    print('%3d' % (cur) + ' ', end='')
    cur += 1
    curDay += 1
    if curDay == 7:
        curDay = 0
        print()
