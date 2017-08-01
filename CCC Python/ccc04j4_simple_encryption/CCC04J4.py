import sys
import string
input = sys.stdin.readline

key = input().strip()
word = input().strip()
encoded = []
keyInd = 0
for char in word:
    if char not in string.ascii_uppercase:
        continue
    encoded.append(chr(ord('A') + (ord(char) - ord('A') + ord(key[keyInd]) - ord('A')) % 26))
    keyInd = (keyInd + 1) % len(key)
print(''.join(encoded))
