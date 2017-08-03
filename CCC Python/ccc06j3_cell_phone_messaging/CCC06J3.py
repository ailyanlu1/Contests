import sys
import string
input = sys.stdin.readline

phone = {}
i = 0
cur = 2
while i < 26:
    for j in range(3):
        phone[string.ascii_lowercase[i]] = (cur, j + 1)
        i += 1
    if string.ascii_uppercase[i] == 'S' or string.ascii_uppercase[i] == 'Z':
        phone[string.ascii_lowercase[i]] = (cur, 4)
        i += 1
    cur += 1
phone[''] = (0, 0)

word = input().strip()
while word != 'halt':
    time = 0
    prev = ''
    for char in word:
        time += phone[char][1]
        if phone[char][0] == phone[prev][0]:
            time += 2
        prev = char
    print(time)
    word = input().strip()
