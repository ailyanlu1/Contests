import sys
input = sys.stdin.readline

base = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}
num = input().strip()
decimal = 0
for i in range(0, len(num), 2):
    c = base[num[i + 1]]
    decimal += (-1 if i + 2 < len(num) and c < base[num[i + 3]] else 1) * (ord(num[i]) - ord('0')) * c
print(decimal)
