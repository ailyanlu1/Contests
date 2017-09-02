import sys
input = sys.stdin.readline

T = int(input())
for t in range(T):
    N = int(input())
    cars = [int(input()) for i in range(N)]
    branch = []
    cnt = 1
    while len(cars) > 0:
        c = cars.pop()
        if c == cnt:
            cnt += 1
        else:
            branch.append(c)
        while len(branch) > 0 and branch[-1] == cnt:
            branch.pop()
            cnt += 1
    print('Y' if all(branch[i] < branch[i + 1] for i in range(len(branch) - 1)) else 'N')
