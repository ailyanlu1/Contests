import sys
input = sys.stdin.readline

special = (2, 18)
today = (int(input()), int(input()))
if today < special:
    print('Before')
elif today > special:
    print('After')
else:
    print('Special')
