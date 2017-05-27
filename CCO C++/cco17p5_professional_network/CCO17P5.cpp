/*
 * CCO17P5.cpp
 *
 *  Created on: May 27, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAXN 200000

using namespace std;

int N;
int cost;
pair<int, int> arr[MAXN];
priority_queue<int> paid;
queue<pair<int, int>> hold;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int A, B;
		scanf("%d%d", &A, &B);
		arr[i] = make_pair(A, B);
	}
	sort(arr, arr + N);
	for (int i = 0; i < N; i++) {
		while (!hold.empty() && i >= hold.front().first) {
			paid.push(hold.front().second);
			hold.pop();
		}
		if (i >= arr[i].first) {
			if (!paid.empty() && arr[i].second < paid.top()) {
				cost += arr[i].second - paid.top();
				paid.pop();
				hold.push(arr[i]);
			}
		} else {
			cost += arr[i].second;
			if (!paid.empty()) {
				cost -= paid.top();
				paid.pop();
			}
			hold.push(arr[i]);
		}
	}
	printf("%d\n", cost);
	return 0;
}
