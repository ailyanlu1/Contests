import sys
input = sys.stdin.readline

line = input().strip()
hour = int(('00' + line)[:-2])
minute = int(line[-2:])
print(line + ' in Ottawa')
hour = (hour + 21) % 24
cities = ['Victoria', 'Edmonton', 'Winnipeg', 'Toronto', 'Halifax', "St.John's"]
for city in cities:
    if city == cities[-1]:
        if minute + 30 < 60:
            hour = (hour + 23) % 24
        minute = (minute + 30) % 60
    print('%s%02d in ' % ('' if hour == 0 else str(hour), minute) + city)
    hour = (hour + 1) % 24
