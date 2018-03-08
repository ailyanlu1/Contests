import sys
input = sys.stdin.readline

N = int(input())
for i in range(0, N):
    line = input().strip().split(" ")
    modified = []
    for word in line:
        if len(word) == 4:
            modified.append("****")
        else:
            modified.append(word)
    print(' '.join(modified))
