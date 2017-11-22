#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) ((x) << 1)
#define r(x) ((x) << 1 | 1)
#define m(x, y) ((x) + ((y) - (x)) / 2)
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define FILL(a, x) memset((a), (x), sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<int, double> pid;
typedef pair<double, int> pdi;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef pair<llu, llu> pllu;
typedef pair<int, llu> pillu;
typedef pair<llu, int> pllui;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef map<ll, ll> mll;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;
typedef unordered_map<ll, ll> umll;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXK 1010
#define MOD 1000000009

llu comb[MAXK][MAXK], modInv[MAXK], sum[MAXK];

llu pow3(llu base, llu pow, llu mod) {
    if (pow == 0) return 1;
    if (pow == 1) return base;
    if (pow % 2 == 0) return pow3(base * base % mod, pow / 2, mod);
    return base * pow3(base * base % mod, pow / 2, mod) % mod;
}

llu divMod(llu i, llu j, llu p) {
    return i * pow3(j, p - 2, p) % p;
}

void precompute(int m) {
    comb[0][0] = 1LLU;
    for (int i = 1; i < MAXK; i++) {
        modInv[i] = divMod(1, i, m) % m;
        comb[i][0] = 1LLU;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % m;
        }
    }
}

ll sumPow(llu n, int k, int m) {
    n %= m;
    sum[0] = n;
    llu cur = 1;
    llu next = n;
    for (int i = 1; i <= k; i++) {
        cur = next;
        next = (next * n) % m;
        sum[i] = (cur + next) % m;
        for (int j = 2; j <= i; j += 2) {
            sum[i] = (sum[i] + (comb[i][j] * sum[i - j + 1]) % m) % m;
        }
        for (int j = 3; j <= i; j += 2) {
            sum[i] = (sum[i] - ((comb[i][j] * sum[i - j + 1]) % m) + m) % m;
        }
        sum[i] = (sum[i] * modInv[i + 1]) % m;
    }
    return sum[k];
}

int main() {
    int Q, K;
    llu N;
    ri(Q);
    precompute(MOD);
    for (int i = 0; i < Q; i++) {
        rllu(N);
        ri(K);
        printf("%llu\n", N == 1 ? 0LLU : (sumPow(N - 1, K, MOD) - 1 + MOD) % MOD);
    }
    return 0;
}
