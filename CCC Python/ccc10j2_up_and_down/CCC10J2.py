import sys
input = sys.stdin.readline

# current pos, forwards, cnt, backwards
p = [[0, int(input()), 1, int(input())], [0, int(input()), 1, int(input())]]
S = int(input())

for s in range(S):
    for i in range(2):
        p[i][0] += p[i][2] // abs(p[i][2])
        if abs(p[i][2]) == p[i][p[i][2] // abs(p[i][2])]:
            p[i][2] = -p[i][2] // abs(p[i][2])
        else:
            p[i][2] += p[i][2] // abs(p[i][2])
if p[0][0] > p[1][0]:
    print('Nikky')
elif p[0][0] < p[1][0]:
    print('Byron')
else:
    print('Tied')
