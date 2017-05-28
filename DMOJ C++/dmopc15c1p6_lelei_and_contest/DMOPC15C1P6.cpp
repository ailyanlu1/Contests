/*
 * DMOPC15C1P6.cpp
 *
 *  Created on: May 28, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAXN 200000

using namespace std;

int M, N, Q;

struct FenwickTree {
private:
	int* a;
	int* b;
	int size;

public:
	FenwickTree(int size) {
		this->size = size;
		a = new int[size + 1];
		b = new int[size + 1];
	}

	int rsq(int* bit, int ind) {
		int sum = 0;
		for (int x = ind; x > 0; x -= (x & -x)) {
			sum = (sum + bit[x]) % M;
		}
		return sum;
	}

	int rsq(int ind) {
			return (rsq(a, ind) * ind - rsq(b, ind) + M) % M;
		}

	int rsq(int l, int r) {
		return (rsq(r) - rsq(l - 1) + M) % M;
	}

	void update(int* bit, int ind, int value) {
		for (int x = ind; x <= size; x += (x & -x)) {
			bit[x] = (bit[x] + value) % M;
		}
	}

	void update(int l, int r, int value) {
		update(a, l, value);
		update(a, r + 1, M - value);
		update(b, l, (l - 1) % M * value);
		update(b, r + 1, r % M * (M - value));
	}

	int getSize() {
		return size;
	}
};

FenwickTree ft(MAXN);

int main() {
	scanf("%d%d%d", &M, &N, &Q);
	for (int i = 1; i <= N; i++) {
		int x;
		scanf("%d", &x);
		ft.update(i, i, x % M);
	}

	for (int i = 0; i < Q; i++) {
		int t;
		scanf("%d", &t);
		if (t == 1) {
			int l, r, x;
			scanf("%d%d%d", &l, &r, &x);
			ft.update(l, r, x % M);
		} else /*if (t == 2)*/{
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%d\n", ft.rsq(l, r));
		}
	}
	return 0;
}
