import sys
input = sys.stdin.readline

a = int(input())
b = int(input())
c = int(input())
n = int(input())
cnt = 0
for i in range(n // a + 1):
    for j in range(n // b + 1):
        for k in range(n // c + 1):
            if a * i + b * j + c * k <= n and i + j + k > 0:
                print('%d Brown Trout, %d Northern Pike, %d Yellow Pickerel' % (i, j, k))
                cnt += 1
print('Number of ways to catch fish: ' + str(cnt))
