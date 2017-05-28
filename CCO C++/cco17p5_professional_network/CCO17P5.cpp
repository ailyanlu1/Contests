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
vector<pair<int, int>> arr;
priority_queue<int> paid;
queue<int> hold;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int A, B;
		scanf("%d%d", &A, &B);
		arr.push_back(make_pair(A, B));
	}
	sort(arr.begin(), arr.end());
	for (int i = 0; i < N; i++) {
		while (!hold.empty() && i >= arr[hold.front()].first) {
			paid.push(arr[hold.front()].second);
			hold.pop();
		}
		if (i >= arr[i].first) {
			if (!paid.empty() && arr[i].second < paid.top()) {
				cost += arr[i].second - paid.top();
				paid.pop();
				hold.push(i);
			}
		} else {
			cost += arr[i].second;
			if (!paid.empty()) {
				cost -= paid.top();
				paid.pop();
			}
			hold.push(i);
		}
	}
	printf("%d\n", cost);
	return 0;
}
