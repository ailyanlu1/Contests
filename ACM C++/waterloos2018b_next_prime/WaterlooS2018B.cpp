#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

int T;
ll N;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        if (N <= 2) {
            cout << 2 << nl;
        } else {
            bool isPrime = false;
            do {
                isPrime = true;
                ll sqrtN = sqrt(N);
                for (ll i = 2; i <= sqrtN; i++) {
                    if (N % i == 0) {
                        N++;
                        isPrime = false;
                        break;
                    }
                }
            } while (!isPrime);
            cout << N << nl;
        }
    }
    return 0;
}
