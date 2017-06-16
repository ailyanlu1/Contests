
/*
 * LinkedList.cpp
 *
 *  Created on: Jun 16, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair
#define left(x) x << 1
#define right(x) x << 1 | 1
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
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;

#define MAXN (int) 1e6
#define MAXVAL (llu) (8e12)

int M, shift = 44, prevInd = 0, curInd = MAXN, nextInd = MAXN + 1, freeInd = MAXN - 1, insertInd;
char op;
llu val[MAXN + 2];
ll x;

llu clearFirst(llu i) {
    return i & ~((1llu << shift) - 1);
}

llu clearLast(llu i) {
    return i & ((1llu << shift) - 1);
}

int main() {
    for (int i = 0; i <= MAXN; i++) {
        val[i] = i - 1;
    }
    val[MAXN] = 0 | ((llu) (prevInd ^ nextInd) << shift);
    ri(M);
    for (int i = 0; i < M; i++) {
        rc(op);
        if (op == '<') {
            nextInd = curInd;
            curInd = prevInd;
            prevInd = ((int) (val[curInd] >> shift) ^ nextInd);
        } else if (op == '>') {
            prevInd = curInd;
            curInd = nextInd;
            nextInd = ((int) (val[curInd] >> shift) ^ prevInd);
        } else if (op == '=') {
            rll(x);
            val[curInd] = clearFirst(val[curInd]) | (x + MAXVAL);
        } else if (op == '+') {
            rll(x);
            insertInd = freeInd;
            freeInd = (int) val[freeInd];
            val[insertInd] = (x + MAXVAL) | ((llu) (prevInd ^ curInd) << shift);
            val[prevInd] = clearLast(val[prevInd]) | ((llu) (((int) (val[prevInd] >> shift) ^ curInd) ^ insertInd) << shift);
            val[curInd] = clearLast(val[curInd]) | ((llu) (insertInd ^ nextInd) << shift);
            val[nextInd] = clearLast(val[nextInd]) | ((llu) (((int) (val[nextInd] >> shift) ^ curInd) ^ curInd) << shift);
            nextInd = curInd;
            curInd = insertInd;
        } else if (op == '-') {
            val[curInd] = freeInd;
            freeInd = curInd;
            val[prevInd] = clearLast(val[prevInd]) | ((llu) (nextInd ^ ((int) (val[prevInd] >> shift) ^ curInd)) << shift);
            val[nextInd] = clearLast(val[nextInd]) | ((llu) (prevInd ^ ((int) (val[nextInd] >> shift) ^ curInd)) << shift);
            curInd = nextInd;
            nextInd = ((int) (val[nextInd] >> shift) ^ prevInd);
        } else if (op == '!') {
            printf("%lld\n", ((val[curInd] & ((1llu << shift) - 1)) - MAXVAL));
        } else {
            i--;
        }
    }
    return 0;
}
