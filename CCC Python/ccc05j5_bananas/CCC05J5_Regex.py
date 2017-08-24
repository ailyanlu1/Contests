import sys
import re
input = sys.stdin.readline

word = input().strip()
a = re.compile('BA(NA)*S')
monkey = re.compile('^A(NA)*$')
while word != 'X':
    temp = word
    while True:
        word = a.sub('A', word)
        if temp == word:
            break
        temp = word
    if monkey.match(word):
        print('YES')
    else:
        print('NO')
    word = input().strip()
