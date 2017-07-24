import sys
input = sys.stdin.readline


word = input().strip()
while word != 'quit!':
    if len(word) > 4 and word[-2:] == 'or' and word[-3] not in ['a', 'e', 'i', 'o', 'u', 'y']:
        word = word[:-1] + 'u' + word[-1]
    print(word)
    word = input().strip()
