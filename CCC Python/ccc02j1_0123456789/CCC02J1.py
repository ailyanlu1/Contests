import sys
input = sys.stdin.readline

N = int(input())
hor = ' *' * 3 + '\n'
ver2 = ('*' + ' ' * 5 + '*\n') * 3
verL = ('*' + ' ' * 6 + '\n') * 3
verR = (' ' * 6 + '*\n') * 3
if N == 0:
    print(hor + ver2 + '\n' + ver2 + hor)
elif N == 1:
    print('\n' + verR + '\n' + verR + '\n')
elif N == 2:
    print(hor + verR + hor + verL + hor)
elif N == 3:
    print(hor + verR + hor + verR + hor)
elif N == 4:
    print('\n' + ver2 + hor + verR + '\n')
elif N == 5:
    print(hor + verL + hor + verR + hor)
elif N == 6:
    print(hor + verL + hor + ver2 + hor)
elif N == 7:
    print(hor + verR + '\n' + verR + '\n')
elif N == 8:
    print(hor + ver2 + hor + ver2 + hor)
else:  # N == 9
    print(hor + ver2 + hor + verR + hor)
