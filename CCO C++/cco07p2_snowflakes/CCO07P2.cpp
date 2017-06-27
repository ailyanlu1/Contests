/*
 * CCO07P2.cpp
 *
 *  Created on: Apr 25, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

unordered_set<string> hs;
int lengths[6];
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 6; j++) {
            scanf("%d", &lengths[j]);
        }
        sort(begin(lengths), end(lengths));
        string str = "";
        for (int j = 0; j < 6; j++) {
            str += lengths[j];
        }
        hs.insert(str);
    }
    if (hs.size() == N) printf("No two snowflakes are alike.");
    else printf("Twin snowflakes found.");
    return 0;
}
