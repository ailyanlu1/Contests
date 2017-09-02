import sys
input = sys.stdin.readline

var = {'A': 0, 'B': 0}
while True:
    line = list(input().strip().split())
    if line[0] == '1':
        var[line[1]] = int(line[2])
    elif line[0] == '2':
        print(var[line[1]])
    elif line[0] == '3':
        var[line[1]] += int(var[line[2]])
    elif line[0] == '4':
        var[line[1]] *= int(var[line[2]])
    elif line[0] == '5':
        var[line[1]] -= int(var[line[2]])
    elif line[0] == '6':
        var[line[1]] //= int(var[line[2]])
    else:
        break
