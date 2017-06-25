/*
 * Halloween14P3.cpp
 *
 *  Created on: Jun 25, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf("%c", &x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a

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

#define MAXN 5000
#define MOD (ll) (1e9 + 7)
#define BASE 137

string S;
int N;

ll pwr[MAXN + 1], hsh[MAXN + 1];
bitset<MAXN + 1> done;

ll getHash(int i, int j) {
    return (hsh[j] - hsh[i - 1] * pwr[j - i + 1] % MOD + MOD) % MOD;
}

int main() {
    cin >> S;
    S = " " + S;
    N = S.length();
    pwr[0] = 1LL;
    for (int i = 1; i < N; i++) {
        pwr[i] = (pwr[i - 1] * BASE) % MOD;
        hsh[i] = (hsh[i - 1] * BASE + (S[i] - 'a' + 1)) % MOD;
    }
    ll ans = 0;
    umlli freq;
    set<ll> vis;
    for (int i = 1; (i << 1) <= N; i++) {
        done.reset();
        for (int j = 1; j <= N - i; j++) {
            if (done.test(j)) continue;
            int count = 1;
            ll cur = getHash(j, j + i - 1);
            if (vis.count(cur)) continue;
            for (int k = j + i; k <= N - i; k += i, count++) {
                if (cur != getHash(k, k + i - 1)) break;
                done.set(k);
                vis.insert(getHash(j, k + i - 1));
            }
            if (count <= 1) continue;
            freq[cur] = max(freq[cur], count);
        }
    }
    for (auto &p: freq) {
        ans += p.s - 1;
    }
    printf("%lld\n", ans);
    return 0;
}
