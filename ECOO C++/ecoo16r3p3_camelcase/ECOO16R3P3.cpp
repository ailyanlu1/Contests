/*
 * ECOO16R3P3.cpp
 *
 *  Created on: May 4, 2017
 *      Author: wleung
 */

#include <bits/stdc++.h>

using namespace std;

unordered_set<string> dict;
const int NUM_OF_TEST_CASES = 10;
long dp[2002];

void run() {
    string word;
    cin >> word;
    dp[0] = -1;
    for (int i = 1; i <= word.length(); i++) {
        dp[i] = INT_MAX;
    }
    for (int i = 0; i < word.length(); i++) {
        for (int j = 1; i + j <= word.length(); j++) {
            if (dict.find(word.substr(i, j)) != dict.end()) dp[i + j] = min(dp[i + j], dp[i] + 1);
        }
    }
    cout << dp[word.length()] << endl;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        dict.insert(s);
    }
    for (int i = 0; i < NUM_OF_TEST_CASES; i++) {
        run();
    }
    return 0;
}
