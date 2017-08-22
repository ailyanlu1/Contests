from datetime import date
import sys
input = sys.stdin.readline

election = date(2007, 2, 27)
N = int(input())
for i in range(N):
    y, m, d = map(int, input().strip().split())
    born = date(y, m, d)
    if election.year - born.year - ((election.month, election.day) < (born.month, born.day)) >= 18:
        print('Yes')
    else:
        print('No')
