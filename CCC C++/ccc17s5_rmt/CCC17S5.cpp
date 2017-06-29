/*
 * CCC17S5.cpp
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

int queryLine(int x, int l, int r) {
    int ans = 0;
    int lo = 0;
    int hi = lines[x].size() - 1;
    int mid;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (lines[x][mid] <= r) lo = mid + 1;
        else hi = mid - 1;
    }
    ans += psa[x][lo + cur[x]];

    lo = 0;
    hi = lines[x].size() - 1;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (lines[x][mid] < l) lo = mid + 1;
        else hi = mid - 1;
    }

    ans -= psa[x][lo + cur[x]];
    return ans;
}

int queryLarge(int l, int r) {
    int ans = 0;
    for (int i = 0; i < large.size(); i++) {
        ans += queryLine(large[i], l, r);
    }
    return ans;
}

void updateSmall(int x) {
    for (int i = 0; i < lines[x].size(); i++) {
        update(lines[x][i], -A[lines[x][(i + cur[x]) % lines[x].size()]]);
    }
    cur[x] = (cur[x] + lines[x].size() - 1) % lines[x].size();
    for (int i = 0; i < lines[x].size(); i++) {
        update(lines[x][i], A[lines[x][(i + cur[x]) % lines[x].size()]]);
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
    int type, l, r, x;
    for (int i = 0; i < Q; i++) {
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d%d", &l, &r);
            printf("%d\n", rsq(r) - rsq(l - 1) + queryLarge(l, r));
        } else {
            scanf("%d", &x);
            if (small[x]) updateSmall(x);
            else cur[x] = (cur[x] + lines[x].size() - 1) % lines[x].size();;
        }
    }
    return 0;
}
