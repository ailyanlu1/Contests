import sys
input = sys.stdin.readline

N = int(input())
lot = ["C" for j in range(N)]
yesterday = input().strip()
for i in range(len(yesterday)):
    if (yesterday[i] == '.'):
        lot[i] = '.'
today = input().strip()
for i in range(len(today)):
    if (today[i] == '.'):
        lot[i] = '.'
print(str(lot.count('C')))
