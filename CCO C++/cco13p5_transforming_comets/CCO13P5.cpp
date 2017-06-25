/*
 * CCO13P5.cpp
 *
 *  Created on: Jun 7, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define INT_INF 0x3f3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define m(x, y) x + (y - x) / 2
#define x first
#define y second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf('%llu', &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf("%c", &x)
#define pri(x) printf("%d", x)
#define prll(x) printf("%lld", x)
#define prllu(x) printf("%llu", x)
#define prd(x) printf("%f", x)
#define prs(x) printf("%s", x)
#define prsi(x, s) printf("%d" s, x)
#define prsll(x, s) printf("%lld" s, x)
#define prsllu(x, s) printf("%llu" s, x)
#define prsd(x, s) printf("%f" s, x)
#define prss(x, s) printf("%s" s, x)
#define prlni(x) prsi(x, "\n")
#define prlnll(x) prsll(x, "\n")
#define prlnllu(x) prsllu(x, "\n")
#define prlnd(x) prsd(x, "\n")
#define prlns(x) prss(x, "\n")
#define For(i, a, n) for (int i = a; i < n; i++)
#define Fore(i, a, n) for (int i = a; i <= n; i++)
#define For0(i, n) For(i, 0, n)
#define For1(i, n) Fore(i, 1, n)
#define Forc(i, c) for (auto i = c.begin(); i != c.end(); i++)
#define Rev(i, n, a) for (int i = n; i > a; i--)
#define Reve(i, n, a) for (int i = n; i >= a; i--)
#define Rev0(i, n) Reve(i, n - 1, 0)
#define Rev1(i, n) Reve(i, n, 1)
#define Revc(i, c) for (int i = c.end(); i-- != c.begin();)
#define Fill(a, x) memset(a, x, sizeof(a))
#define All(a) a.begin(), a.end()
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

int t, N, A, B, T[500005];
pff a[1000005], b[500005];
pii c[500005];

void faliure() {
    T[0] = -1;
    for (int i = 0, j = -1; i < B; i++, j++, T[i] = j) {
        while (j >= 0 && b[i] != b[j]) {
            j = T[j];
        }
    }
}

int KMP() {
    for (int i = 0, j = 0; i < A; i++, j++) {
        while (j >= 0 && a[i] != b[j]) {
            j = T[j];
        }
        if (j == B - 1) {
            return i - j + 1;
        }
    }
    return 0;
}

float rat(pii x, pii y, pii z) {
    pii i = mp(x.x - y.x, x.y - y.y);
    pii j = mp(z.x - y.x, z.y - y.y);
    float ret = sqrt(i.x * i.x + i.y * i.y) / sqrt(j.x * j.x + j.y * j.y);
    return ret;
}

float angle(pii x, pii y, pii z) {
    pii i = mp(x.x - y.x, x.y - y.y);
    pii j = mp(z.x - y.x, z.y - y.y);
    float ret = atan2(i.x * j.y - i.y * j.x, i.x * j.x + i.y * j.y);
    return ret;
}

void prepare(pff* v, int L) {
    for (int i = 0; i < N; i++) {
        ri(c[i].x);
        ri(c[i].y);
    }
    for (int i = 0; i <= L; i++) {
        v[i].x = angle(c[i % N], c[(i + 1) % N], c[(i + 2) % N]);
        v[i].y = rat(c[i % N], c[(i + 1) % N], c[(i + 2) % N]);
    }
}

void run() {
    ri(N);
    prepare(b, B = N);
    prepare(a, A = 2 * N);
    faliure();
    prlni(KMP());
}

int main() {
    ri(t);
    for (int i = 0; i < t; i++) {
        run();
    }
}
