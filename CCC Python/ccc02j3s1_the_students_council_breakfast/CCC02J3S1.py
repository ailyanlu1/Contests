import sys
input = sys.stdin.readline

pink = int(input())
green = int(input())
red = int(input())
orange = int(input())
total = int(input())
count = 0
minTickets = float('inf')

for p in range(0, total // pink + 1):
    for g in range(0, total // green + 1):
        for r in range(0, total // red + 1):
            for o in range(0, total // orange + 1):
                if p * pink + g * green + r * red + o * orange == total:
                    print('# of PINK is ' + str(p) + ' # of GREEN is ' + str(g) + ' # of RED is ' + str(r) + ' # of ORANGE is ' + str(o))
                    count += 1
                    minTickets = min(minTickets, p + g + r + o)
print('Total combinations is ' + str(count) + '.')
print('Minimum number of tickets to print is ' + str(minTickets) + '.')
