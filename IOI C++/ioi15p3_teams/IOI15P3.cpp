/*
 * IOI15P3.cpp
 *
 *  Created on: Aug 9, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
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

#define MAXN 500005
#define LGN 20

int n, SZ, ROOT[MAXN], L[MAXN * LGN], R[MAXN * LGN], CNT[MAXN * LGN], VAL[MAXN * 4], LAZY[MAXN * 4];

void propogate(int ind) {
    if (LAZY[ind] != -1) {
        LAZY[l(ind)] = L[LAZY[ind]];
        VAL[l(ind)] = CNT[LAZY[l(ind)]];
        LAZY[r(ind)] = R[LAZY[ind]];
        VAL[r(ind)] = CNT[LAZY[r(ind)]];
        LAZY[ind] = -1;
    }
}

int inc(int cur, int cL, int cR, int ind) {
    if (cL > ind || cR < ind) return cur;
    int cSz = ++SZ;
    CNT[cSz] = CNT[cur];
    if (cL >= ind && cR <= ind) {
        CNT[cSz]++;
        return cSz;
    }
    int m = mid(cL, cR);
    L[cSz] = inc(L[cur], cL, m, ind);
    R[cSz] = inc(R[cur], m + 1, cR, ind);
    CNT[cSz] = CNT[L[cSz]] + CNT[R[cSz]];
    return cSz;
}

int updateQuery(int cur1, int cur2, int cL, int cR, int ind, int k) {
    if (cL != cR) propogate(cur2);
    if (cL >= ind && CNT[cur1] - VAL[cur2] <= k) {
        int ret = CNT[cur1] - VAL[cur2];
        LAZY[cur2] = cur1;
        VAL[cur2] = CNT[cur1];
        return ret;
    }
    if (cR < ind || k == 0) return 0;
    if (cL == cR) {
        VAL[cur2] += k;
        return k;
    }
    int m = mid(cL, cR);
    int ret = updateQuery(L[cur1], l(cur2), cL, m, ind, k);
    VAL[cur2] = VAL[l(cur2)] + VAL[r(cur2)];
    if (ret == k) return ret;
    ret += updateQuery(R[cur1], r(cur2), m + 1, cR, ind, k - ret);
    VAL[cur2] = VAL[l(cur2)] + VAL[r(cur2)];
    return ret;
}

vector<int> adj[MAXN];

void init(int N, int A[], int B[]) {
    n = N;
    for (int i = 0; i < N; i++) {
        adj[A[i]].pb(B[i]);
    }
    SZ = 0;
    for (int a = 1; a <= N; a++) {
        ROOT[a] = ROOT[a - 1];
        for (int b : adj[a]) {
            ROOT[a] = inc(ROOT[a], 1, N, b);
        }
    }
}

int can(int M, int K[]) {
    LAZY[1] = 0;
    VAL[1] = 0;
    int sum = 0;
    for (int i = 0; i < M; i++) {
        sum += K[i];
    }
    if (sum > n) return 0;
    sort(K, K + M);
    for (int i = 0; i < M; i++) {
        if (K[i] != updateQuery(ROOT[K[i]], 1, 1, n, K[i], K[i])) return 0;
    }
    return 1;
}

#define MAXM 200005

int N, A[MAXN], B[MAXN], Q, M, K[MAXM];

int main() {
    ri(N);
    for (int i = 0; i < N; i++) {
        ri(A[i]);
        ri(B[i]);
    }
    init(N, A, B);
    ri(Q);
    for (int i = 0; i < Q; i++) {
        ri(M);
        for (int j = 0; j < M; j++) {
            ri(K[j]);
        }
        printf("%d\n", can(M, K));
    }
    return 0;
}
