/*
 * IOI15P5.cpp
 *
 *  Created on: Jun 12, 2017
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
#define rllu(x) scanf('%llu', &x)
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

#define MAXN 200000

int *s, *x, *y, *p, *q, n;
int cur1[MAXN], cur2[MAXN];
int rev1[MAXN], rev2[MAXN];

bool trial(int t) {
	for (int i = 0; i < n; i++) {
		cur2[i] = i;
	}
	for (int i = t - 1; i >= 0; i--) {
		swap(cur2[x[i]], cur2[y[i]]);
	}
	for (int i = 0; i < n; i++) {
		rev2[cur2[i]] = i;
		cur1[i] = s[i];
		rev1[cur1[i]] = i;
	}
	int pt = 0;
	for (int i = 0; i < t; i++) {
		swap(cur2[x[i]], cur2[y[i]]);
		swap(cur1[x[i]], cur1[y[i]]);
		rev1[cur1[x[i]]] = x[i];
		rev2[cur2[x[i]]] = x[i];
		rev1[cur1[y[i]]] = y[i];
		rev2[cur2[y[i]]] = y[i];
		while (pt < n && rev1[pt] == rev2[pt]) {
			pt++;
		}
		if (pt == n) {
			p[i] = q[i] = 0;
			continue;
		}
		int p1 = rev1[pt];
		int p2 = rev2[pt];
		p[i] = p1;
		q[i] = p2;
		swap(cur1[p1], cur1[p2]);
		rev1[cur1[p1]] = p1;
		rev1[cur1[p2]] = p2;
	}
	while (pt < n && rev1[pt] == rev2[pt]) {
		pt++;
	}
	return (pt == n);
}

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
	n = N, s = S, x = X, y = Y, p = P, q = Q;
	int ans = 0;
	int i = M;
	while (ans != i) {
		int m = (ans + i) / 2;
		if (trial(m)) i = m;
		else ans = m + 1;
	}
	trial(ans);
	return ans;
}

int main() {
	int N;
	ri(N);
	int S[N];
	for (int i = 0; i < N; i++) {
		ri(S[i]);
	}
	int M;
	ri(M);
	int X[M], Y[M], P[M], Q[M];
	for (int i = 0; i < M; i++) {
		ri(X[i]);
		ri(Y[i]);
	}
	printf("%d\n", findSwapPairs(N, S, M, X, Y, P, Q));
	for (int i = 0; i < M; i++) {
		printf("%d %d\n", P[i], Q[i]);
	}
	return 0;
}
