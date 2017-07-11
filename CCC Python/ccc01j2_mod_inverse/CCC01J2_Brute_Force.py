import sys
input = sys.stdin.readline

x = int(input())
m = int(input())
ans = -1
for i in range(m):
    if x * i % m == 1:
        ans = i
        break
if ans == -1:
    print('No such integer exists.')
else:
    print(ans)
