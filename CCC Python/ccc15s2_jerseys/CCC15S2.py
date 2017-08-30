import sys
input = sys.stdin.readline


conv = {'S': 0, 'M': 1, 'L': 2}
J = int(input())
jerseys = [0] * (J + 1)
A = int(input())
cnt = 0
for i in range(1, J + 1):
    jerseys[i] = conv[input().strip()]
for i in range(A):
    line = input().strip().split()
    s = line[0]
    n = int(line[1])
    if 1 <= n and n <= J and jerseys[n] >= conv[s]:
        jerseys[n] = -1
        cnt += 1
print(cnt)
