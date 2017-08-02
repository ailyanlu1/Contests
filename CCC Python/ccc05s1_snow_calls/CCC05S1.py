import sys
import string
input = sys.stdin.readline

phone = {}
cur = 2
i = 0
while i < 26:
    for j in range(3):
        phone[string.ascii_uppercase[i]] = cur
        i += 1
    if cur == 7 or cur == 9:
        phone[string.ascii_uppercase[i]] = cur
        i += 1
    cur += 1

t = int(input())
for i in range(t):
    old = input().strip().replace('-', '')
    new = []
    for char in old[:10]:
        new.append(phone.get(char, char))
    newStr = ''.join(map(str, new))
    print(newStr[:3] + '-' + newStr[3:6] + '-' + newStr[6:])
