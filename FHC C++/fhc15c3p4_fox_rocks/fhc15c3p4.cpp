/*
 * fhc15c3p4.cpp
 *
 *  Created on: Jun 11, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define INT_INF 0x3f3f3f3f
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

#define MAXN 50100

int matr[15000][4][8];
double p1[15000][4][8];
double p2[15000][4][8];
double pnext[15000][4][4];
double pin[15000][4][4];

struct mat {
public:
    double m[8][8];
};

mat mult(mat x, mat y) {
    mat ans;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ans.m[i][j] = 0;
            for (int k = 0; k < 8; k++) {
                ans.m[i][j] += x.m[i][k] * y.m[k][j];
            }
        }
    }
    return ans;
}

mat step(mat x, int p) {
    for (int i = 0; i < p; i++) {
        x = mult(x, x);
    }
    mat ans;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ans.m[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; i++) {
        ans.m[i][i] = 1;
    }
    while (p) {
        if (p & 1) ans = mult(x, ans);
        x = mult(x, x);
        p /= 2;
    }
    return ans;
}

void recalc(int p) {
    for (int h = 0; h < 5; h++) {
        mat x;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                x.m[i][j] = 0;
            }
        }

        for (int i = 0; i < 4; i++) {
            int cc = 0;
            for (int j = 0; j < 8; j++) {
                cc += matr[p][i][j];
            }
            if (i != h && cc > 0) {
                for (int j = 0; j < 8; j++) {
                    x.m[i][j] = (double) matr[p][i][j] / (double) cc;
                }
            } else {
                x.m[i][i] = 1;
            }
        }

        for (int i = 4; i < 8; i++) {
            x.m[i][i] = 1;
        }
        x = step(x, 8);

        if (h == 4) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    pnext[p][i][j] = x.m[i][j + 4];
                }
            }
        } else {
            for (int i = 0; i < 4; i++) {
                pin[p][i][h] = x.m[i][h];
            }
        }
    }
}

double get(int a, int b) {
    int p = a / 4;
    a %= 4;
    if (b / 4 < p) return 0;
    double pp[4];
    for (int i = 0; i < 4; i++) {
        pp[i] = 0;
    }
    pp[a] = 1;
    while (b / 4 != p) {
        double tp[4];
        for (int i = 0; i < 4; i++) {
            tp[i] = 0;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                tp[j] += pnext[p][i][j] * pp[i];
            }
        }
        for (int i = 0; i < 4; i++) {
            pp[i] = tp[i];
        }
        p++;
    }
    b %= 4;
    double ans = 0;
    for (int i = 0; i < 4; i++) {
        ans += pp[i] * pin[p][i][b];
    }
    return ans;
}

void make(int a, int b, int c, int rec) {
    int p1 = a / 4;
    int p2 = b / 4;
    a %= 4;
    b %= 4;
    if (p2 > p1) b += 4;
    matr[p1][a][b] = c;
    if (rec) recalc(p1);
}

void run(int testCaseNum) {
    printf("Case #%d: ", testCaseNum);
    int N, P, D;
    ri(N);
    ri(P);
    ri(D);
    Fill(matr, 0);
    for (int i = 0; i < P; i++) {
        int a, b, r;
        ri(a);
        ri(b);
        ri(r);
        make(a, b, r, 0);
    }
    for (int i = 0; i < (N + 3) / 4; i++) {
        recalc(i);
    }

    for (int i = 0; i < D; i++) {
        int e, x, y, z;
        ri(e);
        ri(x);
        ri(y);
        if (e == 1) {
            ri(z);
            make(x, y, z, 1);
        } else if (e == 2) {
            make(x, y, 0, 1);
        } else if (e == 3) {
            printf("%.6lf ", get(x, y));
        }
    }
    printf("\n");
}

int main() {
    freopen("fox_rocks.txt", "r", stdin);
    freopen("fox_rocks.out", "w", stdout);
    int T;
    ri(T);
    for (int i = 1; i <= T; i++) {
        run(i);
    }
    return 0;
}
