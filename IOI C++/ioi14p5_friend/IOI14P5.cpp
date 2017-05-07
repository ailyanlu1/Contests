/*
 * IOI14P5.cpp
 *
 *  Created on: May 7, 2017
 *      Author: wleung
 */


#include <bits/stdc++.h>

using namespace std;

int findSample(int n, int confidence[], int host[], int protocol[]) {
	int ret = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (i == 0) {
			ret += confidence[i];
		} else if (protocol[i] == 0) {
			ret += confidence[i];
			confidence[host[i]] = max(0, confidence[host[i]] - confidence[i]);
		} else if (protocol[i] == 1) {
			confidence[host[i]] += confidence[i];
		} else /*if (protocol[i] == 2)*/{
			confidence[host[i]] = max(confidence[host[i]], confidence[i]);
		}
	}
	return ret;
}

int main() {
	int n;
	scanf("%d", &n);
	int confidence[n], host[n], protocol[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &confidence[i]);
	}
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &host[i], &protocol[i]);
	}
	printf("%d\n", findSample(n, confidence, host, protocol));
	return 0;
}
