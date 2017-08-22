import sys
input = sys.stdin.readline

if set(input().strip().replace(' ', '')) ^ set(input().strip().replace(' ', '')):
    print('Is not an anagram.')
else:
    print('Is an anagram.')
