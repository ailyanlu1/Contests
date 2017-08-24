import sys
input = sys.stdin.readline

boxes = []
n = int(input())
for i in range(n):
    boxes.append(sorted(list(map(int, input().strip().split()))))
m = int(input())
for i in range(m):
    item = sorted(list(map(int, input().strip().split())))
    minVol = float('inf')
    for box in boxes:
        for j in range(3):
            if item[j] > box[j]:
                break
        else:
            minVol = min(minVol, box[0] * box[1] * box[2])
    if minVol == float('inf'):
        print('Item does not fit.')
    else:
        print(minVol)
