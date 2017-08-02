import sys
input = sys.stdin.readline


def isAWord(word):
    if word == 'A':
        return True
    if len(word) >= 1 and word[0] == 'B' and word[-1] == 'S' and isMonkey(word[1:-1]):
        return True
    return False


def isMonkey(word):
    if isAWord(word):
        return True
    for i in range(len(word)):
        if word[i] == 'N' and isAWord(word[:i]) and isMonkey(word[i + 1:]):
            return True
    return False


word = input().strip()
while word != 'X':
    if isMonkey(word):
        print('YES')
    else:
        print('NO')
    word = input().strip()
