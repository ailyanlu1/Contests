import sys
input = sys.stdin.readline

N = int(input())
hor = ' *' * 3 + '\n'
ver2 = ('*' + ' ' * 5 + '*\n') * 3
verL = ('*\n') * 3
verR = (' ' * 6 + '*\n') * 3
if N == 0:
    print(hor + ver2 + '\n' + ver2 + hor, end="")
elif N == 1:
    print('\n' + verR + '\n' + verR + '\n', end="")
elif N == 2:
    print(hor + verR + hor + verL + hor, end="")
elif N == 3:
    print(hor + verR + hor + verR + hor, end="")
elif N == 4:
    print('\n' + ver2 + hor + verR + '\n', end="")
elif N == 5:
    print(hor + verL + hor + verR + hor, end="")
elif N == 6:
    print(hor + verL + hor + ver2 + hor, end="")
elif N == 7:
    print(hor + verR + '\n' + verR + '\n', end="")
elif N == 8:
    print(hor + ver2 + hor + ver2 + hor, end="")
else:  # N == 9
    print(hor + ver2 + hor + verR + hor, end="")
