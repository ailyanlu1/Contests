/*
 * IOI12P3.cpp
 *
 *  Created on: Jul 3, 2017
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

#define MAXN 1000000
#define LOGN 20

char text[MAXN];
int cur[MAXN + 1], len[MAXN + 1], last[MAXN + 1][LOGN], rev;

void Init() {
    cur[0] = -1;
    rev = 1;
}

void TypeLetter(char L) {
    cur[rev] = rev;
    text[rev] = L;
    last[rev][0] = cur[rev - 1];
    for (int i = 1; last[rev][i - 1] != -1; i++) {
        last[rev][i] = last[last[rev][i - 1]][i - 1];
    }
    len[rev] = len[last[rev][0]] + 1;
    rev++;
}

void UndoCommands(int U) {
    cur[rev] = cur[rev - U - 1];
    rev++;
}

char GetLetter(int P) {
    int ind = cur[rev - 1];
    for (int i = LOGN - 1; i >= 0; i--) {
        if (len[last[ind][i]] > P) ind = last[ind][i];
    }
    return text[ind];
}

int main() {
    Init();
    int N;
    ri(N);
    for (int i = 0; i < N; i++) {
        char c;
        rc(c);
        if (c == 'T') {
            char L;
            rc(L);
            TypeLetter(L);
        } else if (c == 'U') {
            int U;
            ri(U);
            UndoCommands(U);
        } else if (c == 'P') {
            int P;
            ri(P);
            printf("%c\n", GetLetter(P));
        } else {
            i--;
        }
    }
    return 0;
}
