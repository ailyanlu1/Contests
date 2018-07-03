#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

#define MAXN 105

int N, rowCnt[MAXN][2], colCnt[MAXN][2];
char grid[MAXN][MAXN];

void update(int i, int j, int delta) {
    if (grid[i][j] == 'X') {
        rowCnt[i][0] += delta;
        colCnt[j][0] += delta;
    } else if (grid[i][j] == 'O') {
        rowCnt[i][1] += delta;
        colCnt[j][1] += delta;
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    memset(grid, 0, sizeof(grid));
    memset(rowCnt, 0, sizeof(rowCnt));
    memset(colCnt, 0, sizeof(colCnt));
    string cmd;
    int cur = 0;
    while (true) {
        cin >> cmd;
        if (cmd == "QUIT") {
            cout << "TIE GAME" << nl;
            return 0;
        }
        int x = 0;
        for (int i = 1; i < sz(cmd); i++) x = x * 10 + cmd[i] - '0';
        if (cmd[0] == 'L') {
            int i;
            for (i = 1; i <= N; i++) if (grid[x][i] == 0) break;
            for (; i > 1; i--) {
                update(x, i, -1);
                grid[x][i] = grid[x][i - 1];
                update(x, i, 1);
            }
            update(x, 1, -1);
            grid[x][1] = cur % 2 == 0 ? 'X' : 'O';
            update(x, 1, 1);
        } else if (cmd[0] == 'R') {
            int i;
            for (i = N; i >= 1; i--) if (grid[x][i] == 0) break;
            for (; i < N; i++) {
                update(x, i, -1);
                grid[x][i] = grid[x][i + 1];
                update(x, i, 1);
            }
            update(x, N, -1);
            grid[x][N] = cur % 2 == 0 ? 'X' : 'O';
            update(x, N, 1);
        } else if (cmd[0] == 'T') {
            int i;
            for (i = 1; i <= N; i++) if (grid[i][x] == 0) break;
            for (; i > 1; i--) {
                update(i, x, -1);
                grid[i][x] = grid[i - 1][x];
                update(i, x, 1);
            }
            update(1, x, -1);
            grid[1][x] = cur % 2 == 0 ? 'X' : 'O';
            update(1, x, 1);
        } else if (cmd[0] == 'B') {
            int i;
            for (i = N; i >= 1; i--) if (grid[i][x] == 0) break;
            for (; i < N; i++) {
                update(i, x, -1);
                grid[i][x] = grid[i + 1][x];
                update(i, x, 1);
            }
            update(N, x, -1);
            grid[N][x] = cur % 2 == 0 ? 'X' : 'O';
            update(N, x, 1);
        }
        int cnt0 = 0, cnt1 = 0;
        for (int i = 1; i <= N; i++) {
            if (colCnt[i][0] == N) cnt0++;
            if (rowCnt[i][0] == N) cnt0++;
            if (colCnt[i][1] == N) cnt1++;
            if (rowCnt[i][1] == N) cnt1++;
        }
        if (cnt0 > cnt1) {
            cout << "X WINS" << nl;
            return 0;
        }
        if (cnt1 > cnt0) {
            cout << "O WINS" << nl;
            return 0;
        }
        cur++;
    }
    return 0;
}
