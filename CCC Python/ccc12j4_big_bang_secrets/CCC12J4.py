import sys
input = sys.stdin.readline

K = int(input())
word = input().strip()
for i in range(len(word)):
    print(chr(ord('A') + (ord(word[i]) - ord('A') - K - 3 * (i + 1)) % 26), end='')
print()
