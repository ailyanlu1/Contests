import sys
input = sys.stdin.readline

m = int(input())
n = int(input())
count = 0

for x in range(m, n + 1):
    ori = str(x)
    rot = ''
    for char in reversed(ori):
        if char == '6':
            rot += '9'
        elif char == '9':
            rot += '6'
        elif char == '0' or char == '1' or char == '8':
            rot += char
        else:
            break
    if rot == ori:
        count += 1
print(count)
