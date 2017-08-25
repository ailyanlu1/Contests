import sys
input = sys.stdin.readline

code = {}
k = int(input())
for i in range(k):
    c, b = input().strip().split()
    code[b] = c
seq = input().strip()
while len(seq) > 0:
    for b in code:
        if seq.startswith(b):
            seq = seq[len(b):]
            print(code[b], end='')
print()
