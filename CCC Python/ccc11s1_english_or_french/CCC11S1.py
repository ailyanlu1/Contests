import sys
input = sys.stdin.readline

N = int(input())
text = ''
for i in range(N):
    text += input().strip().lower()
print('English' if text.count('t') > text.count('s') else 'French')
