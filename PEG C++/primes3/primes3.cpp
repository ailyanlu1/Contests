#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
#define mid(x, y) (x + (y - x) / 2)
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) (rand() % (b - a + 1) + a)

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

unsigned long long mulMod(unsigned long long a, unsigned long long b, unsigned long long mod) {
    unsigned long long x = 0, y = a % mod;
    for (; b > 0; b /= 2) {
        if (b % 2 == 1) x = (x + y) % mod;
        y = (y * 2) % mod;
    }
    return x % mod;
}

unsigned long long powMod(unsigned long long base, unsigned long long pow, unsigned long long mod) {
    unsigned long long x = 1, y = base;
    for (; pow > 0; pow /= 2) {
        if (pow % 2 == 1) x = mulMod(x, y, mod);
        y = mulMod(y, y, mod);
    }
    return x % mod;
}

bool isPrime(unsigned long long n, int iterations) {
    if (n < 2 || (n != 2 && n % 2 == 0)) return false;
    unsigned long long s = n - 1;
    while (s % 2 == 0) s /= 2;
    srand(time(0));
    for (int i = 0; i < iterations; i++) {
        unsigned long long temp = s;
        unsigned long long r = powMod(rand() % (n - 1) + 1, temp, n);
        while (temp != n - 1 && r != 1 && r != n - 1) {
            r = mulMod(r, r, n);
            temp *= 2;
        }
        if (r != n - 1 && temp % 2 == 0) return false;
    }
    return true;
}

int T;
llu N;

int main() {
    ri(T);
    for (int i = 0; i < T; i++) {
        rllu(N);
        if (isPrime(N, 5)) printf("PRIME\n");
        else printf("NOT\n");
    }
    return 0;
}
