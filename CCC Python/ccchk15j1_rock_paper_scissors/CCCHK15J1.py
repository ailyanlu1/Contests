import sys
input = sys.stdin.readline

N = int(input())

diff = [0] * N
a = list(input().strip().split())
b = list(input().strip().split())
for i in range(len(a)):
    if a[i] == "rock":
        diff[i] = (diff[i] + 1) % 3
    elif a[i] == "paper":
        diff[i] = (diff[i] + 2) % 3
for i in range(len(b)):
    if b[i] == "rock":
        diff[i] = (diff[i] + 2) % 3
    elif b[i] == "paper":
        diff[i] = (diff[i] + 1) % 3
cntA = 0
cntB = 0
for i in range(N):
    if diff[i] == 1:
        cntA += 1
    elif diff[i] == 2:
        cntB += 1
print(str(cntA) + " " + str(cntB))
