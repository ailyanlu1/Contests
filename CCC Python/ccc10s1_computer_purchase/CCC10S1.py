import sys
input = sys.stdin.readline

N = int(input())
best1Val = 0
best2Val = 0
best1 = ''
best2 = ''

for i in range(N):
    name, R, S, D = input().strip().split()
    val = 2 * int(R) + 3 * int(S) + int(D)
    if val > best1Val or (val == best1Val and name < best1):
        best2 = best1
        best2Val = best1Val
        best1 = name
        best1Val = val
    elif val > best2Val or (val == best2Val and name < best2):
        best2 = name
        best2Val = val
print(best1)
print(best2)
