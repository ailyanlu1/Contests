import sys
input = sys.stdin.readline

instructions = []
while True:
    dir = input().strip()
    street = input().strip()
    instructions.append((dir, street))
    if street == 'SCHOOL':
        break
for i in range(len(instructions) - 1, -1, -1):
    if instructions[i][0] == 'L':
        print('Turn RIGHT ', end='')
    else:
        print('Turn LEFT ', end='')
    if i == 0:
        print('into your HOME.')
    else:
        print('onto ' + instructions[i - 1][1] + ' street.')
