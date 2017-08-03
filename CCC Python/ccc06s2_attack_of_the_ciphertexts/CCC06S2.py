import sys
input = sys.stdin.readline

plain = input()
cipher = input()
code = {}
for i in range(len(plain)):
    code[cipher[i]] = plain[i]
cipher = input()
plain = []
for char in cipher:
    plain.append(code.get(char, '.'))
print(''.join(plain))
