/*
 * CCO17P4.cpp
 *
 *  Created on: May 27, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAXN 500
#define MAXH 50

using namespace std;

int N;
vector<int> h;
set<int> heights;
bool dp[2][MAXH * MAXN + 1];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int hi;
        scanf("%d", &hi);
        h.push_back(hi);
    }
    sort(h.begin(), h.end());
    reverse(h.begin(), h.end());
    dp[1][0] = true;
    heights.insert(h[1]);
    for (int i = 2; i < N; i++) {
        for (int j = 0; j <= MAXH * N; j++) {
            if (dp[1-i%2][j]) dp[i%2][j] = true;
            for (int k: heights) {
                if (j < (k - h[i])) continue;
                if (dp[1-i%2][j - k + h[i]]) dp[i%2][j] = true;
            }
        }
        heights.insert(h[i]);
    }
    for (int i = 0; i <= MAXH * N; i++) {
        if (dp[1-N%2][i]) printf("%d ", i);
    }
    return 0;
}
