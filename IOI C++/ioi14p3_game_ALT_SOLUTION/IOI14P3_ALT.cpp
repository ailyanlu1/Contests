/*
 * IOI14P3_ALT.cpp
 *
 *  Created on: May 27, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAXN 1500

using namespace std;

int cnt[MAXN];

void initialize(int n) {

}

int hasEdge(int u, int v) {
    return ++cnt[(u > v ? u : v)] == (u > v ? u : v);
}

int main() {
    int n;
    scanf("%d", &n);
    initialize(n);
    int r = n * (n - 1) / 2;
    for (int i = 0; i < r; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", hasEdge(u, v));
    }
    return 0;
}
