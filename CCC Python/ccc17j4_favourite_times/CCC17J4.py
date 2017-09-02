import sys
input = sys.stdin.readline

CYCLE_CNT = 31
CYCLE = 720

D = int(input())
H = 12
M = 0
cnt = 0
for i in range(D % CYCLE):
    M += 1
    if M == 60:
        H += 1
        M = 0
    if H == 13:
        H = 1
    clock = str(H) + '%02d' % M
    dif = int(clock[1]) - int(clock[0])
    for j in range(1, len(clock)):
        if int(clock[j]) - int(clock[j - 1]) != dif:
            break
    else:
        cnt += 1
print(cnt + CYCLE_CNT * (D // CYCLE))
