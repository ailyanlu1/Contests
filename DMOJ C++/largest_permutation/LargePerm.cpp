/*
 * LargePerm.cpp
 *
 *  Created on: Jun 28, 2017
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

#define MAXN 100000

int N, K, a[MAXN], ind[MAXN + 1];

int main() {
    ri(N);
    ri(K);
    for(int i = 0; i < N; i++) {
        ri(a[i]);
        ind[a[i]] = i;
    }
    for (int i = 0; i < N && K; i++) {
        if (a[i] == N - i) continue;
        int dest = ind[N - i];
        swap(ind[N - i], ind[a[i]]);
        swap(a[dest], a[i]);
        K--;
    }
    for (int i = 0; i < N; i++) {
        printf("%d", a[i]);
    }
    return 0;
}
