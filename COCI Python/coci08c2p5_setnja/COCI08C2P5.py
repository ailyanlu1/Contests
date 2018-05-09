import sys
input = sys.stdin.readline

pre = 1
tot = 1
for c in input().strip():
    if c == 'L':
        tot *= 2
    elif c == 'R':
        tot = tot * 2 + pre
    elif c == '*':
        tot = tot * 5 + pre
        pre *= 3
print(tot)
