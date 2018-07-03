// https://abc100.contest.atcoder.jp/tasks/abc100_a
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

int A, B;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> A >> B;
    if (A <= 8 && B <= 8) cout << "Yay!" << nl;
    else cout << ":(" << nl;
    return 0;
}
