/*
 * CCO15P4.cpp
 *
 *  Created on: Apr 20, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

using namespace std;

#define MAXN 2000

int N, M;
char grid[MAXN][MAXN];

void check(int i, int j) {
    if (grid[i][j] == 'N') {for (int k = i - 1; k >= 0; k--) if (grid[k][j] != '.') check(k, j);}
    else if (grid[i][j] == 'E') {for (int k = j + 1; k < M; k++) if (grid[i][k] != '.') check(i, k);}
    else if (grid[i][j] == 'S') {for (int k = i + 1; k < N; k++) if (grid[k][j] != '.') check(k, j);}
    else /*if (grid[i][j] == 'W')*/ {for (int k = j - 1; k >= 0; k--) if (grid[i][k] != '.') check(i, k);}
    grid[i][j] = '.';
    printf("(%d,%d)\n", i, j);
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) scanf("%s", grid[i]);
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) if (grid[i][j] != '.') check(i, j);
}
