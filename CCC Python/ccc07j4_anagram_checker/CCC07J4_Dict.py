import sys
input = sys.stdin.readline

freq = {}
phrase = input().strip()
for c in phrase:
    if c != ' ':
        freq[c] = freq.get(c, 0) + 1
phrase = input().strip()
for c in phrase:
    if c != ' ':
        freq[c] = freq.get(c, 0) - 1
for c in freq.keys():
    if freq[c] != 0:
        print('Is not an anagram.')
        sys.exit(0)
print('Is an anagram.')
