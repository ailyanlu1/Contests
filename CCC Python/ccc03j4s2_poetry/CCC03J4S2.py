import sys
input = sys.stdin.readline

vowels = ['a', 'e', 'i', 'o', 'u']


def getLastSyllable(line):
    ret = []
    for c in reversed(line):
        if c == ' ':
            break
        ret.append(c)
        if c in vowels:
            break
    return ''.join(reversed(ret))


N = int(input())
for i in range(N):
    last = []
    for i in range(4):
        last.append(getLastSyllable(input().strip().lower()))
    if last[0] == last[1] and last[1] == last[2] and last[2] == last[3]:
        print('perfect')
    elif last[0] == last[1] and last[2] == last[3]:
        print('even')
    elif last[0] == last[2] and last[1] == last[3]:
        print('cross')
    elif last[0] == last[3] and last[1] == last[2]:
        print('shell')
    else:
        print('free')
