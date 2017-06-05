/*
 * CCO17P6.cpp
 *
 *  Created on: Jun 5, 2017
 *      Author: Wesley Leung
 */

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

#define MAXN 100

struct shift {
	int op, x, k;
	shift(int op, int x, int k) {
		this->op = op;
		this->x = x;
		this->k = k;
	}
};

int grid[MAXN][MAXN], N, M;
vector<shift> ops;
string str;

int getVal(int r, int c) {
	return r * M + c;
}

void rightShift(int r, int k) {
	r++;
	if (k < 0) ops.pb(shift(1, r, M + k));
	else ops.pb(shift(1, r, k));
}

void downShift(int c, int k) {
	c++;
	if (k < 0) ops.pb(shift(2, c, N + k));
	else ops.pb(shift(2, c, k));
}

void rotateFront(int r1, int c1, int r2, int c2) {
	r1 = (r1 + N) % N;
	c1 = (c1 + M) % M;
	r2 = (r2 + N) % N;
	c2 = (c2 + M) % M;

	rightShift(r1, c1 - c2);
	downShift(c1, r1 - r2);
	rightShift(r1, c2 - c1);
	downShift(c1, r2 - r1);

	int temp = grid[r1][c1];
	grid[r1][c1] = grid[r1][c2];
	grid[r1][c2] = grid[r2][c1];
	grid[r2][c1] = temp;
}

void rotateBack(int r1, int c1, int r2, int c2) {
	r1 = (r1 + N) % N;
	c1 = (c1 + M) % M;
	r2 = (r2 + N) % N;
	c2 = (c2 + M) % M;

	downShift(c1, r1 - r2);
	rightShift(r1, c1 - c2);
	downShift(c1, r2 - r1);
	rightShift(r1, c2 - c1);

	int temp = grid[r1][c1];
	grid[r1][c1] = grid[r2][c1];
	grid[r2][c1] = grid[r1][c2];
	grid[r1][c2] = temp;
}

int main() {
	ri(N);
	ri(M);
	For0(i, N) {
		For0(j, M) {
			ri(grid[i][j]);
		}
	}
	For0(r1, N - 1) {
		For0(c1, M) {
			int val = getVal(r1, c1);
			if (grid[r1][c1] == val) continue;
			For(c2, c1 + 1, M) {
				if (grid[r1][c2] == val) {
					rotateBack(r1, c2, r1 + 1, c1);
					goto escape1;
				}
			}
			For(r2, r1 + 1, N) {
				For0(c2, M) {
					if (grid[r2][c2] == val) {
						if (c1 == c2) rotateFront(r2, c1, r1, c2 + 1);
						else rotateBack(r2, c1, r1, c2);
						goto escape1;
					}
				}
			}
			escape1: continue;
		}
	}
	For0(c1, M - 2) {
		int val = getVal(N - 1, c1);
		if (grid[N - 1][c1] == val) continue;
		For(c2, c1 + 1, M) {
			if (grid[N - 1][c2] == val) {
				if (c2 == M - 1) {
					rotateBack(N - 1, M - 2, N - 2, M - 3);
					rotateFront(N - 1, M - 2, N - 2, M - 1);
					c2--;
				}
				Rev(c3, c2, c1) {
					rotateBack(N - 1, c3, N - 2, c3 - 1);
					rotateFront(N - 1, c3, N - 2, c3 + 1);
				}
				goto escape2;
			}
		}
		escape2: continue;
	}
	if (grid[N - 1][M - 2] == getVal(N - 1, M - 1)) {
		for (int c1 = M - 2; c1 != 0; c1 = (c1 - 2 + M) % M) {
			rotateBack(N - 1, c1 - 1, N - 2, c1);
			rotateFront(N - 1, c1 - 1, N - 2, c1 - 2);
		}
		rightShift(N - 1, -1);
	}
	prsi((int) ops.size(), "\n");
	for(auto i: ops) {
		printf("%d %d %d\n", i.op, i.x, i.k);
	}
	return 0;
}
