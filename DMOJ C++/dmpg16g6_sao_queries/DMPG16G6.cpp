/*
 * DMPG16G6.cpp
 *
 *  Created on: May 29, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

using namespace std;

const int MOD = (1 << 18);
const int MULT = (1 << 6);
const int SIZE = (1 << 12);

int N, Q, l, r;
int arr[MOD], freq[MOD];
int pre[SIZE][SIZE];
vector<int> nums[MOD];

int count(int val, int l, int r) {
	return upper_bound(nums[val].begin(), nums[val].end(), r)
		- lower_bound(nums[val].begin(), nums[val].end(), l);
}

int main() {
	scanf("%d%d", &N, &Q);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	for (int i = 0; i * MULT < N; i++) {
		int x = 0;
		memset(freq, 0, sizeof freq);
		for (int j = i * MULT; j < N; j++) {
			x = (x + (freq[arr[j]] << 1 | 1)) % MOD;
			freq[arr[j]]++;
			if ((j + 1) % MULT == 0) pre[i][(j + 1) / MULT] = x;
		}
	}
	for (int i = 0; i < N; i++) {
		nums[arr[i]].push_back(i);
	}
	int ans = 0;
	for (int q = 0; q < Q; q++) {
		scanf("%d%d", &l, &r);
		l ^= ans;
		r ^= ans;
		ans = pre[l / MULT][r / MULT];
		for (int i = l / MULT * MULT; i < l; i++) {
			ans -= count(arr[i], i + 1, r / MULT * MULT - 1) << 1 | 1;
		}
		for (int i = r / MULT * MULT; i <= r; i++) {
			ans += count(arr[i], l, i - 1) << 1 | 1;
		}
		ans = (ans % MOD + MOD) % MOD;
		printf("%d\n", ans);
	}
	return 0;
}
