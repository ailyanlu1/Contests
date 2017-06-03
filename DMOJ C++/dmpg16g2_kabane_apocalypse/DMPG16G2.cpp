/*
 * DMPG16G2.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define INT_INF 0x3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define x first
#define y second
#define ri(x) scanf("%d", &x);
#define rll(x) scanf("%lld", &x);
#define rllu(x) scanf('%llu', &x)
#define rd(x) scanf("%lf", &x);
#define rc(x) scanf("%c", &x);
#define pri(x) printf("%d", x);
#define prll(x) printf("%lld", x);
#define prllu(x) printf("%llu", x);
#define prd(x) printf("%f", x);
#define prs(x) printf(x);
#define prsi(x, s) printf("%d" s, x);
#define prsll(x, s) printf("%lld" s, x);
#define prsllu(x, s) printf("%llu" s, x);
#define prsd(x, s) printf("%f" s, x);
#define For(i, a, n) for (int i = a; i < n; i++)
#define Fore(i, a, n) for (int i = a; i <= n; i++)
#define For0(i, n) For(i, 0, n)
#define For1(i, n) Fore(i, 1, n)
#define Forc(i, c) for (int i = c.begin(); i != c.end(); i++)
#define Rev(i, n, a) for (int i = n; i > a; i--)
#define Reve(i, n, a) for (int i = n; i >= a; i--)
#define Rev0(i, n) Reve(i, n - 1, 0)
#define Rev1(i, n) Reve(i, n, 1)
#define Revc(i, c) for (int i = c.end(); i-- != c.begin();)
#define Fill(a, x) memset(a, x, sizeof(a))
#define All(a) a.begin(), a.end()

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

#define MAXN 1000

int N;
int grid[MAXN][MAXN];
int height[MAXN][MAXN];

struct State {
	int i, h;
	State (int index, int height) {
		this->i = index;
		this->h = height;
	}
};

ll getSubmatrix(int val) {
	For0(i, N) {
		For0(j, N) {
			if ((val & grid[i][j]) == 0) {
				height[i][j] = 1;
				if (i > 0) height[i][j] += height[i - 1][j];
			} else {
				height[i][j] = 0;
			}
		}
	}
	ll ret = 0;
	stack<State> s;
	For0(i, N) {
		For0(j, N) {
			State st = State(j, height[i][j]);
			while (!s.empty() && s.top().h >= st.h) {
				State top = s.top();
				s.pop();
				ll diffW = j - top.i;
				ll diffH = top.h;
				if (s.empty() || s.top().h < st.h) diffH -= height[i][j];
				else diffH -= s.top().h;
				st.i = top.i;
				ret += diffW * (diffW + 1) / 2 * diffH;
			}
			s.push(st);
		}
		while (!s.empty()) {
			State top = s.top();
			s.pop();
			ll diffW = N - top.i;
			ll diffH = top.h;
			if (!s.empty()) diffH -= s.top().h;
			ret += diffW * (diffW + 1) / 2 * diffH;
		}
	}
	return ret;
}

int main() {
	ri(N);
	For0(i, N) {
		For0(j, N) {
			char c = '\n';
			while (c == '\n') rc(c);
			if (c == '.') grid[i][j] = 0;
			else grid[i][j] = 1 << (c - 'A');
		}
	}
	ll ans = 0;
	For0(i, (1 << 5)) {
		int k = 0;
		For0(j, 5) {
			if ((i & (1 << j)) > 0) k++;
		}
		if (k % 2 == 0) ans += getSubmatrix(i);
		else ans -= getSubmatrix(i);
	}
	prll(ans);
	return 0;
}
