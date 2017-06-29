/*
 * CCC17S5_Fenwick_Tree.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair

using namespace std;

#define MAX 150001
#define SMALL_CUTOFF 505

int N, M, Q, L[MAX], A[MAX], cur[MAX], FT[MAX];
vector<int> lines[MAX], psa[MAX], large;
bool small[MAX];

int rsq(int x) {
    int sum = 0;
    for (; x > 0; x -= (x & -x)) {
        sum += FT[x];
    }
    return sum;
}

void update(int x, int value) {
    for (; x <= N; x += (x & -x)) {
        FT[x] += value;
    }
}

int main() {
    scanf("%d%d%d", &N, &M, &Q);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &L[i]);
        lines[L[i]].pb(i);
    }
    for (int i = 1; i <= M; i++) {
        cur[i] = 0;
        small[i] = lines[i].size() <= SMALL_CUTOFF;
        if (!small[i]) {
            large.pb(i);
            psa[i].pb(0);
        }
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        if (small[L[i]]) update(i, A[i]);
    }
    for (int i = 0; i < large.size(); i++) {
        for (int x = 0; x < 2; x++) {
            for (int j = 0; j < lines[large[i]].size(); j++) {
                psa[large[i]].pb(psa[large[i]].back() + A[lines[large[i]][j]]);
            }
        }
    }
    int type, l, r, x, ans;
    for (int q = 0; q < Q; q++) {
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d%d", &l, &r);
            ans = rsq(r) - rsq(l - 1); // small query
            for (int i = 0; i < large.size(); i++) { // large query
                int lo = 0;
                int hi = lines[large[i]].size() - 1;
                int mid;
                while (lo <= hi) {
                    mid = (lo + hi) / 2;
                    if (lines[large[i]][mid] <= r) lo = mid + 1;
                    else hi = mid - 1;
                }
                ans += psa[large[i]][lo + cur[large[i]]];

                lo = 0;
                hi = lines[large[i]].size() - 1;
                while (lo <= hi) {
                    mid = (lo + hi) / 2;
                    if (lines[large[i]][mid] < l) lo = mid + 1;
                    else hi = mid - 1;
                }
                ans -= psa[large[i]][lo + cur[large[i]]];
            }
            printf("%d\n", ans);
        } else {
            scanf("%d", &x);
            if (small[x]) { // small update
                for (int i = 0; i < lines[x].size(); i++) {
                    update(lines[x][i], -A[lines[x][(i + cur[x]) % lines[x].size()]]);
                }
                cur[x] = (cur[x] + lines[x].size() - 1) % lines[x].size();
                for (int i = 0; i < lines[x].size(); i++) {
                    update(lines[x][i], A[lines[x][(i + cur[x]) % lines[x].size()]]);
                }
            } else { // large update
                cur[x] = (cur[x] + lines[x].size() - 1) % lines[x].size();
            }
        }
    }
    return 0;
}
