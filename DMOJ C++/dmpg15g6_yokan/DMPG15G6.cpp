/*
 * DMPG15G6.cpp
 *
 *  Created on: Jun 4, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define INT_INF 0x3f3f3f
#define pb push_back
#define ri(x) scanf("%d", &x)
#define prs(x) printf(x)
#define For(i, a, n) for (int i = a; i < n; i++)
#define Fore(i, a, n) for (int i = a; i <= n; i++)
#define For0(i, n) For(i, 0, n)
#define For1(i, n) Fore(i, 1, n)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;

#define MAXN 200000
#define REP 31

int N, Q, M, l, r, flavour[MAXN + 1], len, ind, cnt;
double target;
vector<int> freq[MAXN + 1];
bool satisfied;

int lowerBound(int i, int key) {
    int lo = 0;
    int hi = freq[i].size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (key <= freq[i][mid]) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int upperBound(int i, int key) {
    int lo = 0;
    int hi = freq[i].size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (key >= freq[i][mid]) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int main() {
    srand((unsigned) time(0));
    scanf("%d%d", &N, &M);
    For1(i, N) {
        ri(flavour[i]);
        freq[flavour[i]].pb(i);
    }
    ri(Q);
    unordered_set<int> hs;
    For0(q, Q) {
        satisfied = false;
        scanf("%d%d", &l, &r);
        len = r - l + 1;
        target = (double) len / 3;
        hs.clear();
        For0(i, REP) {
            ind = flavour[randi(l, r)];
            cnt = upperBound(ind, r) - lowerBound(ind, l);
            if (cnt >= 2 * target || hs.size() > 1) {
                satisfied = true;
                break;
            } else if (cnt >= target) {
                hs.insert(ind);
            }
        }
        if (satisfied) prs("YES\n");
        else prs("NO\n");
    }
    return 0;
}
