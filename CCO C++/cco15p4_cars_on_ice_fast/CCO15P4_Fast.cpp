/*
 * CCO15P4_Fast.cpp
 *
 *  Created on: Apr 20, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

using namespace std;

#define MAXN 2000

int N, M;
char c;
bool done[MAXN][MAXN][4];
int grid[MAXN][MAXN];
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void check(int i, int j, int d) {
    if (i < 0 || i >= N || j < 0 || j >= M) return;
    if (done[i][j][d]) return;
    done[i][j][d] = true;
    check(i + dir[d][0], j + dir[d][1], d);
    if (grid[i][j] != -1 && grid[i][j] != d) check(i, j, grid[i][j]);
    if (grid[i][j] != -1) {
        grid[i][j] = -1;
        printf("(%d,%d)\n", i, j);
    }
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf(" %c", &c);
            if (c == 'N') grid[i][j] = 0;
            else if (c == 'E') grid[i][j] = 1;
            else if (c == 'S') grid[i][j] = 2;
            else if (c == 'W') grid[i][j] = 3;
            else grid[i][j] = -1;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] != -1) {
                check(i, j, grid[i][j]);
            }
        }
    }
}
