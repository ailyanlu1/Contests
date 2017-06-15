/*
 * IOI14P6.cpp
 *
 *  Created on: Jun 5, 2017
 *      Author: Wesley Leung
 */

// 24/100 TLE
#include <bits/stdc++.h>

#define INT_INF 0x3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define m(x, y) x + (y - x) / 2
#define x first
#define y second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf('%llu', &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf("%c", &x)
#define pri(x) printf("%d", x)
#define prll(x) printf("%lld", x)
#define prllu(x) printf("%llu", x)
#define prd(x) printf("%f", x)
#define prs(x) printf(x)
#define prsi(x, s) printf("%d" s, x)
#define prsll(x, s) printf("%lld" s, x)
#define prsllu(x, s) printf("%llu" s, x)
#define prsd(x, s) printf("%f" s, x)
#define For(i, a, n) for (int i = a; i < n; i++)
#define Fore(i, a, n) for (int i = a; i <= n; i++)
#define For0(i, n) For(i, 0, n)
#define For1(i, n) Fore(i, 1, n)
#define Forc(i, c) for (auto i = c.begin(); i != c.end(); i++)
#define Rev(i, n, a) for (int i = n; i > a; i--)
#define Reve(i, n, a) for (int i = n; i >= a; i--)
#define Rev0(i, n) Reve(i, n - 1, 0)
#define Rev1(i, n) Reve(i, n, 1)
#define Revc(i, c) for (int i = c.end(); i-- != c.begin();)
#define Fill(a, x) memset(a, x, sizeof(a))
#define All(a) a.begin(), a.end()
#define randi(a, b) rand() % (b - a + 1) + a

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;

ll solve(int start, int d, int t, int attraction[]) {
	priority_queue< int, vector<int>, greater<int> > pq;
	int i = start;
	ll ret = 0;
	ll curAns = 0;
	while ((start <= d && i <= d) || (start > d && i >= d)) {
		t--;
		curAns += attraction[i];
		pq.push(attraction[i]);
		if (t >= 0) ret = max(ret, curAns);
		while (t < 2 && !pq.empty()) {
			t++;
			curAns -= pq.top();
			pq.pop();
		}
		t--;
		if (start <= d) i++;
		else i--;
	}
	return ret;
}

ll findMaxAttraction(int n, int start, int d, int attraction[]) {
	ll ans = 0;
	For0(i, n) {
		ans = max(ans, solve(i, 0, d - abs(i - start), attraction));
		ans = max(ans, solve(i, n - 1, d - abs(i - start), attraction));
	}
	return ans;
}

int main() {
	int n, start, d;
	ri(n);
	ri(start);
	ri(d);
	int attraction[n];
	For0(i, n) {
		ri(attraction[i]);
	}
	prll(findMaxAttraction(n, start, d, attraction));
	return 0;
}
