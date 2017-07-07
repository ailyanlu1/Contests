/*
 * ICPC_ECNA16G.cpp
 *
 *  Created on: Jul 7, 2017
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
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
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

#define MAXM 50

int m, total, num, prevNum, peg[MAXM + 1], blockedPeg = 1, incPeg = 0;
ll moves = 0;

int main() {
    for (int i = 0; i < 3; i++) {
        ri(m);
        total += m;
        prevNum = MAXM + 1;
        for (int j = 0; j < m; j++) {
            ri(num);
            if (num >= prevNum) {
                printf("No");
                return 0;
            }
            peg[num] = i;
            prevNum = num;
        }
    }
    for (int i = total; i > 0; i--) {
        if (peg[i] == blockedPeg) {
            printf("No");
            return 0;
        }
        moves *= 2;
        if (peg[i] == incPeg) moves++;
        else incPeg = blockedPeg;
        blockedPeg = 3 - peg[i] - blockedPeg;
    }
    printf("%lld", moves);
    return 0;
}
