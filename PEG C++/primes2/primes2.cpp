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

vector<int> &primes(int start, int end) {
    if (start > 1) start -= 1;
    int sqrtE = (int) sqrt(end);
    int range = end - start;
    bool sieve1[sqrtE];
    memset(sieve1, false, sizeof(sieve1));
    vector<int> list;
    sieve1[0] = true;
    for (int x = 1; x < sqrtE; x++) {
        if (sieve1[x] == false) {
            list.push_back(x + 1);
            for (int y = (x + 1) * (x + 1) - 1; y < sqrtE; y += (x + 1)) {
                sieve1[y] = true;
            }
        }
    }
    bool sieve2[range];
    memset(sieve2, false, sizeof(sieve2));
    for (int x : list) {
        for (int y = x * x - 1; y < end; y += x) {
            if (y < start) continue;
            sieve2[y - start] = true;
        }
    }
    vector<int> *primes = new vector<int>;
    for (int x = 0; x < range; x++) {
        if (sieve2[x] == false) primes->push_back(start + x + 1);
    }
    return *primes;
}

int N, M;

int main() {
    ri(N);
    ri(M);
    for (int x : primes(N, M)) {
        printf("%d\n", x);
    }
    return 0;
}
