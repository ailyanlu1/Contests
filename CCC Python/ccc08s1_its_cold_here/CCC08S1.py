import sys
input = sys.stdin.readline

city = ''
coldestCity = ''
coldestTemp = float('inf')
while city != 'Waterloo':
    line = input().strip()
    city = line.split()[0]
    temp = int(line.split()[1])
    if (temp < coldestTemp):
        coldestCity = city
        coldestTemp = temp
print(coldestCity)
