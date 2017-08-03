import sys
input = sys.stdin.readline

burgerCal = {1: 461, 2: 431, 3: 420, 4: 0}
sideCal = {1: 100, 2: 57, 3: 70, 4: 0}
drinkCal = {1: 130, 2: 160, 3: 118, 4: 0}
dessertCal = {1: 167, 2: 266, 3: 75, 4: 0}

burger = int(input())
side = int(input())
drink = int(input())
dessert = int(input())
total = burgerCal[burger] + sideCal[side] + drinkCal[drink] + dessertCal[dessert]
print('You total Calorie count is ' + str(total) + '.')
