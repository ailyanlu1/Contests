import sys
input = sys.stdin.readline

W = int(input())
N = int(input())
cars = [int(input()) for i in range(N)]
cnt = 0
while cnt < len(cars):
    if sum(cars[max(0, cnt - 3):cnt + 1]) > W:
        break
    cnt += 1
print(cnt)
