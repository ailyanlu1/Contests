import sys
input = sys.stdin.readline

n = int(input())
flow = [int(input()) for i in range(n)]
while True:
    op = input().strip()
    if op == '99':
        s = int(input()) - 1
        p = int(input())
        flow = flow[:s] + [flow[s] * (p / 100)] + [flow[s] * (1 - p / 100)] + flow[s + 1:]
    elif op == '88':
        s = int(input()) - 1
        flow = flow[:s] + [flow[s] + flow[s + 1]] + flow[s + 2:]
    else:
        break
print(' '.join(str(int(round(f))) for f in flow))
