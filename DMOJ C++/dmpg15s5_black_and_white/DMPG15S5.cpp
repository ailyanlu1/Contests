/*
 * DMPG15S5.cpp
 *
 *  Created on: May 11, 2017
 *      Author: wleung
 */


#include <bits/stdc++.h>

#define MAXN 10000

using namespace std;

bool board[MAXN + 1][MAXN + 1];
int N, M, x, y, w, h;

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d%d%d%d", &x, &y, &w, &h);
        board[x][y] ^= true;
        board[x][y + h] ^= true;
        board[x + w][y] ^= true;
        board[x + w][y + h] ^= true;
    }

    for (int i = 0; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            board[i][j] ^= board[i][j - 1];
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            board[i][j] ^= board[i - 1][j];
        }
    }
    int ans = 0;
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            if (board[i][j]) ans ++;
        }
    }
    printf("%d", ans);
    return 0;
}
