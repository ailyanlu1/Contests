import sys
input = sys.stdin.readline

depths = []
for i in range(4):
    depths.append(int(input()))
if all(x < y for x, y in zip(depths, depths[1:])):
    print('Fish Rising')
elif all(x > y for x, y in zip(depths, depths[1:])):
    print('Fish Diving')
elif all(x == y for x, y in zip(depths, depths[1:])):
    print('Fish At Constant Depth')
else:
    print('No Fish')
