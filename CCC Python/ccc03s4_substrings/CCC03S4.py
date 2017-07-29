import sys
input = sys.stdin.readline


def LCP(a, b):
    for i in range(min(len(a), len(b))):
        if a[i] != b[i]:
            return i
    return min(len(a), len(b))


N = int(input())
for i in range(N):
    S = input().strip()
    suffix = []
    for j in range(len(S)):
        suffix.append(S[j:])
    suffix.sort()
    count = len(suffix[0]) + 1
    for j in range(1, len(S)):
        count += len(suffix[j]) - LCP(suffix[j - 1], suffix[j])
    print(count)
