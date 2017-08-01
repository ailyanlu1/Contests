import sys
input = sys.stdin.readline

daytime = int(input())
evening = int(input())
weekend = int(input())

costA = (max(0, (daytime - 100) * 25) + evening * 15 + weekend * 20) / 100.0
costB = (max(0, (daytime - 250) * 45) + evening * 35 + weekend * 25) / 100.0

print('Plan A costs %.2f' % costA)
print('Plan B costs %.2f' % costB)
if costA < costB:
    print('Plan A is cheapest.')
elif costA > costB:
    print('Plan B is cheapest.')
else:
    print('Plan A and B are the same price.')
