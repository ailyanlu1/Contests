/*
 * DMOPC15C6P6.cpp
 *
 *  Created on: May 4, 2017
 *      Author: wleung
 */

// 10/100 TLE

#include <bits/stdc++.h>

using namespace std;

int N, M, K;
set<int> adj [1501];
bool marked[1501];
int distTo[1501];
queue<int> q;

int bfs(int s) {
	int count = 0;
	for (int v = 0; v < 1501; v++) {
		distTo[v] = INT_MAX;
		marked[v] = false;
	}
	distTo[s] = 0;
	marked[s] = true;
	q.push(s);
	count++;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int w: adj[v]) {
			if (!marked[w]) {
				distTo[w] = distTo[v] + 1;
				marked[w] = true;
				count++;
				if (distTo[w] < K) q.push(w);
			}
		}
	}
	return count;
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < M; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--;
		b--;
		adj[a].insert(b);
		adj[b].insert(a);
	}
	for (int i = 0; i < N; i++) {
		printf("%d\n", bfs(i));
	}
	return 0;
}
