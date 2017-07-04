/*
 * IOI12P3_Ropes.cpp
 *
 *  Created on: Jul 3, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>
#include <ext/rope>

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
using namespace __gnu_cxx;

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

int rev;
rope<char> text[MAXN];

void Init() {
    rev = 0;
}

void TypeLetter(char L) {
    text[rev] = *(new rope<char>(text[rev - 1])) + L;
    // text[rev] = text[rev - 1] + L;
    rev++;
}

void UndoCommands(int U) {
    text[rev] = *(new rope<char>(text[rev - U - 1]));
    // text[rev] = text[rev - U - 1];
    rev++;
}

char GetLetter(int P) {
    return text[rev - 1][P];
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
