// https://abc100.contest.atcoder.jp/tasks/abc100_d
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

#define MAXN 1005

int N, M;
ll A[MAXN][3], sum[MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) for (int j = 0; j < 3; j++) cin >> A[i][j];
    ll bestAns = -0x3f3f3f3f3f3f3f3f;
    for (int i = 0; i < (1 << 3); i++) {
        for (int j = 0; j < N; j++) {
            sum[j] = 0;
            for (int k = 0; k < 3; k++) if ((i >> k) & 1) sum[j] += A[j][k]; else sum[j] -= A[j][k];
        }
        sort(sum, sum + N, greater<ll>());
        ll ans = 0;
        for (int j = 0; j < M; j++) ans += sum[j];
        bestAns = max(bestAns, ans);
    }
    cout << bestAns << nl;
    return 0;
}
