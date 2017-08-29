import sys
input = sys.stdin.readline

partner = {}
N = int(input())
A = list(input().strip().split())
B = list(input().strip().split())
for a, b in zip(A, B):
    if a == b or (b in partner.keys() and partner[b] != a):
        print('bad')
        sys.exit(0)
    partner[a] = b
print('good')
