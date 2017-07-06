/*
 * Fibonacci.cpp
 *
 *  Created on: May 28, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MOD 1000000007ULL

using namespace std;

typedef pair<unsigned long long, unsigned long long> pll;

pll fib (unsigned long long n) {
    if (n == 0) return make_pair(0ULL, 1ULL);
    pll res = fib(n / 2);
    unsigned long long a = res.first * (res.second * 2ULL - res.first + MOD) % MOD;
    unsigned long long b = ((res.first * res.first) % MOD + (res.second * res.second) % MOD) % MOD;
    if (n % 2 == 0) return make_pair(a, b);
    return make_pair(b, (a + b) % MOD);
}

int main() {
    unsigned long long n;
    scanf("%llu", &n);
    printf("%llu\n", fib(n).first);
}
