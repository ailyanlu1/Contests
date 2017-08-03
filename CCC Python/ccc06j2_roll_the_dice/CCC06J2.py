import sys
input = sys.stdin.readline

m = int(input())
n = int(input())

count = 0
for x in range(1, 10):
    if m >= x and n >= (10 - x):
        count += 1
if count == 1:
    print('There is 1 way to get the sum 10.')
else:
    print('There are ' + str(count) + ' ways to get the sum 10.')
