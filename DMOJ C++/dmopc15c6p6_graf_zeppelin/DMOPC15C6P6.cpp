/*
 * DMOPC15C6P6.cpp
 *
 *  Created on: May 4, 2017
 *      Author: wleung
 */

#include <bits/stdc++.h>

using namespace std;

int N, M, K;
bitset<1500> adj[1500], cur[1500], total[1500];

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < M; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--;
		b--;
		adj[a][b] = adj[b][a] = cur[a][b] = cur[b][a] = total[a][b] = total[b][a] = 1;
	}
	for (int k = 1; k < K; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (cur[i][j]) total[i] |= adj[j];
			}
		}
		for (int i = 0; i < N; i++) {
			cur[i] |= total[i];
		}
	}
	for (int i = 0; i < N; i++) {
		int count = total[i].count();
		if (!total[i][i]) count += 1;
		printf("%d\n", count);
	}
	return 0;
}
