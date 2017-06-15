/*
 * DMOPC14C4P5.cpp
 *
 *  Created on: Jun 4, 2017
 *      Author: Wesley Leung
 */


// 64/100 RTE
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

#define MAXN 200000
#define MAXH 300000
#define SIZE MAXH * 2

struct FenwickTree {
private:
	ll* array;
	int size;

public:
	FenwickTree(int size) {
		this->size = size;
		array = new ll[size + 1];
	}

    /**
     * Range Sum query from 1 to ind
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind index
     * @return sum
     */
	ll rsq(int ind) {
		ll sum = 0LL;
		for (int x = ind; x > 0; x -= (x & -x)) {
			sum += array[x];
		}
		return sum;
	}

    /**
     * Range Sum Query from a to b.
     * Search for the sum from array index from a to b
     * a and b are 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  a left index
     * @param  b right index
     * @return sum
     */
	ll rsq(int a, int b) {
		return rsq(b) - rsq(a - 1);
	}

    /**
     * Update the array at ind and all the affected regions above ind.
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind   index
     * @param  value value
     */
	void update(int ind, ll value) {
		for (int x = ind; x <= size; x += (x & -x)) {
			array[x] += value;
		}
	}

	int getSize() {
		return size;
	}
};

int N, K;
FenwickTree leftFT(SIZE), rightFT(SIZE), leftSumFT(SIZE), rightSumFT(SIZE);
int arr[MAXN];

int main() {
	ri(N);
	ri(K);
	For0(i, N) {
		ri(arr[i]);
		arr[i] += MAXH;
	}
	ll minTime = LLONG_MAX;
	int adj = 0;
	For0(i, N) {
		adj++;
		if (i % 2 == 0) {
			leftFT.update(arr[i - i / 2] - i / 2 - 1, 1);
			rightFT.update(arr[i - i / 2] + i / 2, -1);
			leftSumFT.update(arr[i - i / 2] - i / 2 - 1, arr[i - i / 2] - i / 2 - 1);
			rightSumFT.update(arr[i - i / 2] + i / 2, -(arr[i - i / 2] + i / 2));
		}
		rightFT.update(arr[i] + adj - 1, 1);
		rightSumFT.update(arr[i] + adj - 1, arr[i] + adj - 1);
		if (i < K - 1 || i % 2 == 1) continue;
		int lo = 1;
		int hi = SIZE;
		int median = INT_INF;
		ll left, right;
		while (lo <= hi) {
			int mid = m(lo, hi);
			left = leftFT.rsq(mid) + rightFT.rsq(mid + adj);
			right = i - left + 1;
			if (left == right) {
				median = mid;
				break;
			} else if (left < right) {
				lo = mid + 1;
			} else {
				hi = mid - 1;
			}
		}
		if (median == INT_INF) median = lo;
		left = leftFT.rsq(median) + rightFT.rsq(median + adj);
		right = i - left + 1;
		ll smallRight = rightFT.rsq(median + adj);
		ll largeRight = rightFT.rsq(SIZE) - smallRight;
		ll smallSum = leftSumFT.rsq(median) + rightSumFT.rsq(median + adj) - adj * smallRight;
		ll largeSum = leftSumFT.rsq(SIZE) + rightSumFT.rsq(SIZE) - adj * (smallRight + largeRight) - smallSum;
		minTime = min(minTime, (left - right) * median - smallSum + largeSum);
	}
	if (minTime == LLONG_MAX) prll(-1LL);
	else prll(minTime);
	return 0;
}
