/*
 * COCI08C1P5.cpp
 *
 *  Created on: Jun 20, 2017
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

struct Flower {
    short r, c;
    int petals, dp;
};

bool operator < (const Flower &a, const Flower &b) {
    return a.petals > b.petals;
}

struct Best4 {
    Flower *best[4];

    void update(Flower *f) {
        for (int i = 3; i >= 0; i--) {
            if (f->dp <= best[i]->dp) continue;
            if (i + 1 < 4) best[i + 1] = best[i];
            best[i] = f;
        }
    }

    int query(int r, int c) {
        for (int i = 0; i < 4; i++) {
            if (abs(r - best[i]->r) <= 1 && abs(c - best[i]->c) <= 1) continue;
            return best[i]->dp;
        }
        return -INT_INF;
    }
};

#define MAXN 1500

int N, R, C;
Flower F[MAXN * MAXN];
Best4 RR[MAXN], CC[MAXN];

int main() {
    ri(N);
    ri(R);
    ri(C);
    R--;
    C--;
    int ind = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            F[ind].r = i;
            F[ind].c = j;
            F[ind].dp = 1;
            ri(F[ind].petals);
            ind++;
        }
    }
    Flower temp = {-SHORT_INF, -SHORT_INF, -INT_INF, -INT_INF};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 4; j++) {
            RR[i].best[j] = CC[i].best[j] = &temp;
        }
    }
    sort(F, F + N * N);
    for (int i = 0, j; i < N * N; i = j) {
        for (j = i; j < N * N && F[i].petals == F[j].petals; j++) {
            Flower *f = &F[j];
            if (f->r - 1 >= 0) F[j].dp = max(F[j].dp, RR[f->r - 1].query(f->r, f->c) + 1);
            if (f->c - 1 >= 0) F[j].dp = max(F[j].dp, CC[f->c - 1].query(f->r, f->c) + 1);
            if (f->r + 1 < N) F[j].dp = max(F[j].dp, RR[f->r + 1].query(f->r, f->c) + 1);
            if (f->c + 1 < N) F[j].dp = max(F[j].dp, CC[f->c + 1].query(f->r, f->c) + 1);
        }
        for (j = i; j < N * N && F[i].petals == F[j].petals; j++) {
            Flower *f = &F[j];
            RR[f->r].update(f);
            CC[f->c].update(f);
            if (f->r == R && f->c == C) {
                printf("%d\n", f->dp);
                return 0;
            }
        }
    }
    return 0;
}
