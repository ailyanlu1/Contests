/*
 * TLE16C1P6.cpp
 *
 *  Created on: Jul 31, 2017
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

#define MAXN 300

bool A[MAXN][MAXN];
bool b[MAXN];
int n, p, q;
char line[10];

void solve() {
    for (int p = 0; p < n; p++) {
        // find pivot row and swap
        int m = p;
        for (int i = 0; i < p; i++) {
            int j = i;
            while (j < n && !A[i][j]) {
                j++;
            }
            if (j == p) m = i;
        }
        for (int i = p + 1; i < n; i++) {
            if (A[i][p]) m = i;
        }
        if (!A[m][p]) continue;
        swap(A[p], A[m]);
        swap(b[p], b[m]);
        // pivot within A and b
        for (int i = 0; i < n; i++) {
            if (p == i || !A[i][p]) continue;
            b[i] ^= b[p];
            for (int j = p; j < n; j++) {
                A[i][j] ^= A[p][j];
            }
        }
    }
    // back substitution
    for (int i = n - 1; i >= 0; i--) {
        if (!A[i][i] && b[i]) throw runtime_error("Matrix has no solution");
        if (!b[i]) continue;
        for (int j = i - 1; j >= 0; j--) {
            b[j] ^= A[j][i];
            A[j][i] = false;
        }
    }
}

int main() {
    ri(n);
    for (int i = 0; i < n; i++) {
        rs(line);
        if (line[0] == '!') {
            sscanf(line, "!%d", &p);
            p--;
            A[i][p] ^= true;
        } else {
            sscanf(line, "%d==%d", &p, &q);
            p--;
            q--;
            A[i][p] ^= true;
            A[i][q] ^= true;
        }
        A[i][i] ^= true;
        b[i] = true;
    }
    try {
        solve();
        for (int i = 0; i < n; i++) {
            printf("%s\n", b[i] ? "true" : "false");
        }
    } catch (runtime_error &e) {
        printf("No perfect solution found");
    }
    return 0;
}
