// https://abc100.contest.atcoder.jp/tasks/abc100_d
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

#define MAXN 1005

int N, M, bestInd[1 << 3];
ll A[MAXN][3], ans[1 << 3][2], best[1 << 3];
bool taken[MAXN][1 << 3];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) cin >> A[i][j];
        for (int j = 0; j < (1 << 3); j++) taken[i][j] = false;
    }
    for (int i = 0; i < (1 << 3); i++) for (int j = 0; j < 2; j++) ans[i][j] = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < (1 << 3); j++) {
            best[j] = -0x3f3f3f3f3f3f3f3f;
            bestInd[j] = -1;
        }
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < (1 << 3); k++) {
                if (taken[j][k]) continue;
                ll val = 0;
                for (int m = 0; m < 3; m++) {
                    if ((k >> m) & 1) val += A[j][m];
                    else val -= A[j][m];
                }
                if (best[k] < val) {
                    best[k] = val;
                    bestInd[k] = j;
                }
            }
        }
        for (int k = 0; k < (1 << 3); k++) {
            taken[bestInd[k]][k] = true;
            ans[k][0] += best[k];
            ans[k][1] = abs(ans[k][0]);
        }
    }
    ll bestAns = 0;
    for (int k = 0; k < (1 << 3); k++) bestAns = max(bestAns, ans[k][1]);
    cout << bestAns << nl;
    return 0;
}
