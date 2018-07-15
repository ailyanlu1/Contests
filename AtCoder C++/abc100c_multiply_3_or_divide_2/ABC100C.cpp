// https://abc100.contest.atcoder.jp/tasks/abc100_c
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

int N;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int a;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        cin >> a;
        for (; a % 2 == 0; cnt++) a /= 2;
    }
    cout << cnt << nl;
    return 0;
}
