#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

#define MAXM 10

int T, M;
double R[MAXM], x[MAXM];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> M;
        for (int i = 0; i < M; i++) cin >> R[i];
        sort(R, R + M);
        double ans = numeric_limits<double>::infinity();
        do {
            double upper = 0.0;
            for (int i = 0; i < M; i++) {
                x[i] = R[i];
                for (int j = 0; j < i; j++) x[i] = max(x[i], x[j] + sqrt((R[i] + R[j]) * (R[i] + R[j]) - (R[i] - R[j]) * (R[i] - R[j])));
                upper = max(upper, x[i] + R[i]);
            }
            ans = min(ans, upper);
        } while (next_permutation(R, R + M));
        if (M == 0) cout << "0.000" << nl;
        else cout << fixed << setprecision(3) << ans << nl;
    }
    return 0;
}
