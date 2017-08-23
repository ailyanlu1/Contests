import sys
input = sys.stdin.readline


def solve2(s1, s2):
    ret = []
    for a in s1:
        for b in s2:
            ret.extend([a + b, a - b, b - a, a * b])
            if b != 0 and a % b == 0:
                ret.append(a // b)
            if a != 0 and b % a == 0:
                ret.append(b // a)
    return ret


def solve3(s1, s2, s3):
    return solve2(solve2(s1, s2), s3) + solve2(solve2(s2, s3), s1) + solve2(solve2(s3, s1), s2)


def solve4(s1, s2, s3, s4):
    return solve2(solve3(s1, s2, s3), s4) + solve2(solve3(s2, s3, s4), s1) + solve2(solve3(s3, s4, s1), s2) + solve2(solve3(s4, s1, s2), s3) + \
        solve2(solve2(s1, s2), solve2(s3, s4)) + solve2(solve2(s2, s3), solve2(s4, s1))


n = int(input())
for i in range(n):
    a = int(input())
    b = int(input())
    c = int(input())
    d = int(input())
    s = set(solve4([a], [b], [c], [d]))
    ans = 0
    for x in s:
        if x <= 24 and x > ans:
            ans = x
    print(ans)
