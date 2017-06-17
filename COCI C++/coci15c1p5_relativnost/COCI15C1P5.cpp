/*
 * COCI15C1P5.cpp
 *
 *  Created on: Jun 17, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair
#define mid(x, y) x + (y - x) / 2
#define f first
#define s second
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

#define MAXN 100000
#define MAXC 20
#define MOD 10007

int N, C, Q, p;
int A[MAXN], B[MAXN];
int tree[2 * MAXN][MAXC + 1];

void update(int x) {
    memset(tree[x], 0, sizeof tree[x]);
    for(int i = 0; i <= C; i++) {
        for (int j = 0; j <= C; j++) {
            tree[x][min(i + j, C)] += tree[x * 2][i] * tree[x * 2 + 1][j] % MOD;
        }
    }
    for (int i = 0; i <= C; i++) {
        tree[x][i] %= MOD;
    }
}

void change(int x) {
    int X = x + N;
    memset(tree[X], 0, sizeof tree[X]);
    tree[X][0] = B[x] % MOD;
    tree[X][1] = A[x] % MOD;
    while(X /= 2) {
        update(X);
    }
}

int main() {
    scanf("%d%d", &N, &C);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        tree[i + N][1] = A[i] % MOD;
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
        tree[i + N][0] = B[i] % MOD;
    }
    for (int i = N  - 1; i >= 1; i--) {
        update(i);
    }
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        scanf("%d", &p);
        p--;
        scanf("%d%d", &A[p], &B[p]);
        change(p);
        printf("%d\n", tree[1][C]);
    }
    return 0;
}
