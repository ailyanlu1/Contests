/*
 * APIO12P2.cpp
 *
 *  Created on: Jun 15, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair
#define left(x) x << 1
#define right(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf('%llu', &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf("%c", &x)
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
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;

#define MAXN 100000

int N, K, M, psa[MAXN + 1], loc[MAXN + 1];
vector<pii> range[2], temp;
vector<int> ans;
bool hiding[MAXN + 1];

int main() {
    ri(N);
    ri(K);
    ri(M);
    for (int i = 0; i < M; i++) {
        int A, B, C;
        ri(A);
        ri(B);
        ri(C);
        if (!C) range[0].pb(mp(A, B));
        else range[1].pb(mp(A, B));
    }
    Fill(hiding, true);

    sort(range[0].begin(), range[0].end());
    int last = 0;
    for (int i = 0; i < range[0].size(); i++) {
        for (int j = max(last + 1, range[0][i].f); j <= range[0][i].s; j++) {
            hiding[j] = false;
        }
        last = range[0][i].s;
    }
    for (int i = 1; i <= N; i++) {
        psa[i] = psa[i - 1] + hiding[i];
    }
    last = 0;
    for (int i = 1; i <= N; i++) {
        if (hiding[i]) last = i;
        loc[i] = last;
    }
    if (psa[N] == K) {
        for (int i = 1; i <= N; i++) {
            if (hiding[i]) printf("%d\n", i);
        }
        return 0;
    }

    sort(range[1].begin(), range[1].end());
    last = N + 1;
    for (int i = range[1].size() - 1; i >= 0; i--) {
        if (range[1][i].s < last) {
            temp.pb(range[1][i]);
            last = range[1][i].s;
        }
    }
    for (int i = 0; i < temp.size(); i++) {
        if (psa[temp[i].f - 1] + 1 == psa[temp[i].s]) {
            if (hiding[loc[temp[i].s]]) {
                ans.pb(loc[temp[i].s]);
                hiding[loc[temp[i].s]] = false;
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        psa[i] = psa[i - 1] + hiding[i];
    }
    last = 0;
    for (int i = 1; i <= N; i++) {
        if (hiding[i]) last = i;
        loc[i] = last;
    }

    sort(ans.begin(), ans.end());
    range[1].clear();
    for (int i = 0; i < temp.size(); i++) {
        int l = lower_bound(ans.begin(), ans.end(), temp[i].f) - ans.begin();
        int r = lower_bound(ans.begin(), ans.end(), temp[i].s + 1) - ans.begin();
        if (l == r) range[1].pb(temp[i]);
    }
    sort(range[1].begin(), range[1].end());
    vector<int> a(range[1].size() + 1, 0);
    for (int i = range[1].size() - 1; i >= 0; i--) {
        int next = lower_bound(range[1].begin(), range[1].end(), mp(loc[range[1][i].s] + 1, 0)) - range[1].begin();
        a[i] = a[next] + 1;
    }
    K -= ans.size();
    last = 0;
    int cnt = 0;
    for (int i = 0; i < range[1].size(); i++) {
        if (range[1][i].f > last) {
            int tail = loc[range[1][i].s];
            int next = lower_bound(range[1].begin(), range[1].end(), mp(loc[tail - 1] + 1, 0)) - range[1].begin();
            cnt++;
            if (cnt + a[next] > K) ans.pb(tail);
            last = tail;
        }
    }
    sort(ans.begin(), ans.end());
    if (!ans.size()) {
        printf("-1");
    }
    else {
        for (int i = 0; i < ans.size(); i++) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
