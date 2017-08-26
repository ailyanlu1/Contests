import sys
input = sys.stdin.readline

donors = ([0], [1, 0], [2, 0], [1, 2, 3, 0], [4, 0], [1, 4, 5, 0], [2, 4, 6, 0], [1, 2, 3, 4, 5, 6, 7, 0])
units = list(map(int, input().strip().split()))
patients = list(map(int, input().strip().split()))
cnt = 0
for i in range(len(donors)):
    for j in donors[i]:
        x = min(units[j], patients[i])
        if x == 0:
            continue
        units[j] -= x
        patients[i] -= x
        cnt += x
print(cnt)
