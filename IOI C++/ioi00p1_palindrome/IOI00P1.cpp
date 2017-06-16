
/*
 * IOI00P1.cpp
 *
 *  Created on: May 22, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAXN 5000

using namespace std;

int N;
string s1, s2;
int dp[2][MAXN + 1];

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> s1;
    s2 = s1;
    reverse(s2.begin(), s2.end());
    int s = 1;
    for (int i = 1; i <= s1.length(); i++) {
        s = 1 - s;
        for (int j = 1; j <= s2.length(); j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[s][j] = 1 + dp[1 - s][j - 1];
            } else {
                dp[s][j] = max(dp[1 - s][j], dp[s][j - 1]);
            }
        }
    }
    cout << N - dp[s][s2.length()] << "\n";
    return 0;
}
