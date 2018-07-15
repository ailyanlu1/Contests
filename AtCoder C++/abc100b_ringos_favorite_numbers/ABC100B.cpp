// https://abc100.contest.atcoder.jp/tasks/abc100_b
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

int D, N;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> D >> N;
    int base = 1;
    for (int i = 0; i < D; i++) base *= 100;
    cout << base * (N + (N == 100)) << nl;
    return 0;
}
