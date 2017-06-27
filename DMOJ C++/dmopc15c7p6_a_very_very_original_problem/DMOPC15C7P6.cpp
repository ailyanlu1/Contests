/*
 * DMOPC15C7P6.cpp
 *
 *  Created on: Jun 26, 2017
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

#define MAXLEN (int) 1e5

string s;
int a, b, L, maxInd[MAXLEN * 2 + 1];
ll pre[MAXLEN * 2 + 2], suf[MAXLEN * 2 + 2], ans;
char text[MAXLEN * 2 + 1];

int main() {
    cin >> s;
    L = s.length() * 2 + 1;
    for (int i = 0; i < L; i++) {
        text[i] = '#';
    }
    for (int i = 1; i < L; i += 2) {
        text[i] = s[i / 2];
    }
    for (int i = 1; i < L; i++) {
        int j = (a - (i - a));
        if (b > i) maxInd[i] = min(b - i, maxInd[j]);
        while (i + maxInd[i] + 1 < L && i - maxInd[i] - 1 >= 0
                && text[i + maxInd[i] + 1] == text[i - maxInd[i] - 1]) {
            maxInd[i]++;
        }
        if (i + maxInd[i] > b) {
            a = i;
            b = i + maxInd[i];
        }
    }
    for (int i = 0; i < L; i++) {
        pre[i]++;
        pre[i + maxInd[i]]--;
        suf[i + 1]--;
        suf[i - maxInd[i] + 1]++;
    }
    for (int i = 1; i < L; i++) {
        pre[i] += pre[i - 1];
        suf[i] += suf[i - 1];
    }
    for (int i = 3; i < L; i += 2) {
        pre[i] += pre[i - 2];
    }
    for (int i = 3; i < L; i += 2) {
        ans += suf[i] * pre[i - 2];
    }
    printf("%lld\n", ans);
    return 0;
}
