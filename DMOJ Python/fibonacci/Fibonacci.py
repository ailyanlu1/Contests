MOD = 1000000007


def fib(n):
    if (n == 0):
        return (0, 1)
    res = fib(n // 2)
    a = res[0] * (res[1] * 2 - res[0] + MOD) % MOD
    b = ((res[0] * res[0]) % MOD + (res[1] * res[1]) % MOD) % MOD
    if (n % 2 == 0):
        return (a, b)
    return (b, (a + b) % MOD)


N = int(input())

print(fib(N)[0])
