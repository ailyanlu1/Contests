import sys
input = sys.stdin.readline

curDay, days = map(int, input().split())
curDay -= 1
cur = 1

print('Sun Mon Tue Wed Thr Fri Sat')

for i in range(curDay):
    print('    ', end='')

while True:
    print('%3d' % (cur), end='')
    if cur == days:
        print()
        break
    cur += 1
    curDay += 1
    if curDay == 7:
        curDay = 0
        print()
    else:
        print(" ", end='')
