import sys
input = sys.stdin.readline

N = int(input())
for i in range(N):
    X = input().strip()
    Y = input().strip()
    Z = input().strip()
    if (X.startswith(Y) or Y.startswith(Z) or Z.startswith(X) or
            X.startswith(Z) or Z.startswith(Y) or Y.startswith(X) or
            X.endswith(Y) or Y.endswith(Z) or Z.endswith(X) or
            X.endswith(Z) or Z.endswith(Y) or Y.endswith(X)):
        print('No')
    else:
        print('Yes')
