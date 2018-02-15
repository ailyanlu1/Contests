#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000

int N, A[MAXN];

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    while (cin >> N) {
        for (int i = 0; i < N; i++) cin >> A[i];
        if (N == 1) {
            cout << 1 << "\n";
            continue;
        }
        int diff = A[N - 2] - A[N - 1];
        int i;
        for (i = N - 2; i > 0; i--) {
            if (diff != A[i - 1] - A[i]) {
                cout << i + 1 << "\n";
                break;
            }
        }
        if (i == 0) cout << 1 << "\n";
    }
    return 0;
}
