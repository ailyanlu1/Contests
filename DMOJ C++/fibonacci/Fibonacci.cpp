#include <bits/stdc++.h>

#define MOD 1000000007ULL

using namespace std;

typedef unsigned long long ull;
typedef pair<ull, ull> pll;

pll fib (ull n) {
    if (n == 0) return make_pair(0ULL, 1ULL);
    pll res = fib(n / 2);
    ull a = res.first * (res.second * 2ULL - res.first + MOD) % MOD;
    ull b = ((res.first * res.first) % MOD + (res.second * res.second) % MOD) % MOD;
    if (n % 2 == 0) return make_pair(a, b);
    return make_pair(b, (a + b) % MOD);
}

int main() {
    ull n;
    scanf("%llu", &n);
    printf("%llu\n", fib(n).first);
}
