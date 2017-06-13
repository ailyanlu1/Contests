/*
 * COCI07C6P6.cpp
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

#define MAXN 100000

int N, a[MAXN], b[MAXN], perm[3];
ll dp[MAXN + 1];

int main() {
	ri(N);
	for (int i = 0; i < N; i++) {
		ri(a[i]);
		ri(b[i]);
	}
	sort(a, a + N);
	sort(b, b + N);
	dp[N] = 0;
	for (int i = N - 1; i >= 0; i--) {
		dp[i] = LL_INF;
		for (int k = 1; k <= 3 && i + k <= N; k++) {
			for (int j = 0; j < k; j++) {
				perm[j] = j;
			}
			do {
				ll cost = 0;
				for (int j = 0; j < k; j++) {
					ll add = abs(a[i + j] - b[i + perm[j]]);
					if (add) cost += add;
					else cost = LL_INF;
				}
				dp[i] = min(dp[i], cost + dp[i + k]);
			} while (next_permutation(perm, perm + k));
		}
	}
	printf("%lld", dp[0]);
	return 0;
}
