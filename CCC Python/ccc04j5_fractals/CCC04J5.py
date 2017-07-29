import sys
input = sys.stdin.readline

l, w, x = map(int, input().split())
fract = [(0, 1), (w, 1)]
for i in range(l):
    temp = []
    for j in range(len(fract) - 1):
        temp.append(fract[j])
        a = (fract[j + 1][0] - fract[j][0]) // 3
        b = (fract[j + 1][1] - fract[j][1]) // 3
        temp.append((fract[j][0] + a, fract[j][1] + b))
        temp.append((fract[j][0] + a - b, fract[j][1] + a + b))
        temp.append((fract[j + 1][0] - a - b, fract[j + 1][1] + a - b))
        temp.append((fract[j + 1][0] - a, fract[j + 1][1] - b))
    temp.append(fract[-1])
    fract = temp
temp = []
for i in range(len(fract) - 1):
    temp.append(fract[i])
    for j in range(min(fract[i][0], fract[i + 1][0]), max(fract[i][0], fract[i + 1][0])):
        temp.append((j, fract[i][1]))
    for j in range(min(fract[i][1], fract[i + 1][1]), max(fract[i][1], fract[i + 1][1])):
        temp.append((fract[i][0], j))
temp.append(fract[-1])
fract = temp
ans = set()
for f in fract:
    if f[0] == x:
        ans.add(f[1])
print(' '.join(str(y) for y in sorted(ans)))
