import sys
input = sys.stdin.readline

good = set('IOSHZXN')
word = input().strip()
for c in word:
    if c not in good:
        print('NO')
        sys.exit(0)
print('YES')
