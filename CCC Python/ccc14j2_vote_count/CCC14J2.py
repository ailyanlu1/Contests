import sys
input = sys.stdin.readline

V = int(input())
cnt = {}
for char in input().strip():
    cnt[char] = cnt.get(char, 0) + 1
if cnt.get('A', 0) > cnt.get('B', 0):
    print('A')
elif cnt.get('A', 0) < cnt.get('B', 0):
    print('B')
else:
    print('Tie')
