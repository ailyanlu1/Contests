import sys
input = sys.stdin.readline

line = input().strip()
cntHappy = line.count(':-)')
cntSad = line.count(':-(')
if cntHappy == 0 and cntSad == 0:
    print('none')
elif cntHappy > cntSad:
    print('happy')
elif cntSad > cntHappy:
    print('sad')
else:
    print('unsure')
