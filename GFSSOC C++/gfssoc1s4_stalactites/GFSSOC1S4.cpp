/*
 * GFSSOC1S4.cpp
 *
 *  Created on: May 10, 2017
 *      Author: wleung
 */


#include <bits/stdc++.h>

#define MAXN 251

using namespace std;

int N, Q;
char C;
long long arr[MAXN][MAXN][MAXN];

long long rsq(int indX, int indY, int indZ) {
	long long sum = 0;
	for (int x = indX; x > 0; x -= (x & -x)) {
		for (int y = indY; y > 0; y -= (y & -y)) {
			for (int z = indZ; z > 0; z -= (z & -z)) {
				sum += arr[x][y][z];
			}
		}
	}
	return sum;
}

long long rsq(int x1, int y1, int z1, int x2, int y2, int z2) {
	x1--;
	y1--;
	z1--;
	return rsq(x2, y2, z2)
			- rsq(x1, y2, z2) - rsq(x2, y1, z2) - rsq(x2, y2, z1)
			+ rsq(x1, y1, z2) + rsq(x1, y2, z1) + rsq(x2, y1, z1)
			- rsq(x1, y1, z1);
}

void update(int indX, int indY, int indZ, int value) {
	for (int x = indX; x <= N; x += (x & -x)) {
		for (int y = indY; y <= N; y += (y & -y)) {
			for (int z = indZ; z <= N; z += (z & -z)) {
				arr[x][y][z] += value;
			}
		}
	}
}

int main() {
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> Q;
	long long sum = 0;
	for (int i = 0; i < Q; i++) {
		string C;
		cin >> C;
		if (C == "C") {
			int x, y, z, value;
			cin >> x >> y >> z >> value;
			update(x, y, z, value - rsq(x, y, z, x, y, z));
		} else if (C == "S") {
			int x1, y1, z1, x2, y2, z2;
			cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
			sum += rsq(x1, y1, z1, x2, y2, z2);
		}
	}
	cout << sum << "\n";
}
