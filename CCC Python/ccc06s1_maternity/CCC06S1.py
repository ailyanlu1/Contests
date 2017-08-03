import sys
input = sys.stdin.readline

mother = input().strip()
father = input().strip()
X = int(input())
for i in range(X):
    baby = input().strip()
    valid = True
    for j in range(len(baby)):
        if baby[j].islower():
            if mother[j * 2 + 1].isupper() or father[j * 2 + 1].isupper():
                valid = False
        if baby[j].isupper():
            if mother[j * 2].islower() and father[j * 2].islower():
                valid = False
    if valid:
        print('Possible baby.')
    else:
        print('Not their baby!')
