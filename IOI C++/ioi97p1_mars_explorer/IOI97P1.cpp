/*
 * IOI97P1.cpp
 *
 *  Created on: Jul 2, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf("%c", &x)
#define rs(x) scanf("%s", x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

#define MAXPQ 255
#define S 0
#define E 1

int P, Q, N, grid[MAXPQ][MAXPQ], dir[MAXPQ][MAXPQ];

int dfs(int y, int x) {
    if (grid[y][x] == -1) return -1;
    if (y == Q - 1 && x == P - 1) return grid[y][x];
    int south = -1;
    int east = -1;
    if (y < Q - 1) south = dfs(y + 1, x);
    if (x < P - 1) east = dfs(y, x + 1);
    if (south == -1 && east == -1) return -1;
    if (south >= east) {
        dir[y][x] = S;
        return grid[y][x] + south;
    } else {
        dir[y][x] = E;
        return grid[y][x] + east;
    }
}

int main() {
    ri(N);
    ri(P);
    ri(Q);
    for (int y = 0; y < Q; y++) {
        for (int x = 0; x < P; x++) {
            ri(grid[y][x]);
            if (grid[y][x] == 1) grid[y][x] = -1;
            else if (grid[y][x] == 2) grid[y][x] = 1;
        }
    }
    for (int i = 1; i <= N; i++) {
        if (dfs(0, 0) == -1) break;
        int x = 0, y = 0;
        while (y < Q - 1 || x < P - 1) {
            grid[y][x] = 0;
            printf("%d %d\n", i, dir[y][x]);
            if (dir[y][x] == S) y++;
            else x++;
        }
        grid[Q - 1][P - 1] = 0;
    }
    return 0;
}
