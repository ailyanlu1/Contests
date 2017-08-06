/*
 * THICC17P4.cpp
 *
 *  Created on: Aug 5, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

#define MAXL 105

string word1, word2;
int N, T, dp[2][MAXL], tot;
double best = D_INF;

int minDistance() {
    int len1 = word1.length();
    int len2 = word2.length();

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j <= len2; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i % 2][j] = j;
            } else if (j == 0) {
                dp[i % 2][j] = i;
            } else if (word1[i - 1] == word2[j - 1]) {
                dp[i % 2][j] = dp[1 - i % 2][j - 1];
            } else {
                int replace = dp[1 - i % 2][j - 1] + 1;
                int insert = dp[1 - i % 2][j] + 1;
                int del = dp[i % 2][j - 1] + 1;

                int min = replace > insert ? insert : replace;
                min = del > min ? min : del;
                dp[i % 2][j] = min;
            }
        }
    }
    return dp[len1 % 2][len2];
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> word1;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> T;
        tot = 0;
        for (int i = 0; i < T; i++) {
            cin >> word2;
            tot += minDistance();
        }
        best = min(best, (double) tot / (double) T);
    }
    printf("%.6f\n", best);
    return 0;
}
