import sys
input = sys.stdin.readline

delta = -int(input()) + int(input())
fine = 0
if delta >= 31:
    fine = 500
elif delta >= 21:
    fine = 270
elif delta >= 1:
    fine = 100
if fine == 0:
    print('Congratulations, you are within the speed limit!')
else:
    print('You are speeding and your fine is $' + str(fine) + '.')
