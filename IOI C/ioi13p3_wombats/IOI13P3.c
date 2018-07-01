#include <stdio.h>
#include <stdlib.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
#define mid(x, y) (x + (y - x) / 2)
#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) (rand() % (b - a + 1) + a)

typedef long long ll;
typedef unsigned long long llu;

#define MAXR 5000
#define MAXC 200
#define SZ 10

int r, c, h[MAXR][MAXC], v[MAXR][MAXC], ans[MAXR / SZ * 3][MAXC][MAXC], temp[2][MAXC];

void calc(int cur, int cL, int cR) {
    int i, j, k;
    for (i = 0; i < c; i++) {
        for (j = 0; j < c; j++) {
            temp[0][j] = INT_INF;
        }
        temp[0][i] = 0;
        for (j = cL; j <= cR; j++) {
            for (k = 1; k < c; k++) {
                temp[0][k] = min(temp[0][k], temp[0][k - 1] + h[j][k - 1]);
            }
            for (k = c - 2; k >= 0; k--) {
                temp[0][k] = min(temp[0][k], temp[0][k + 1] + h[j][k]);
            }
            if (j == cR) {
                for (k = 0; k < c; k++) {
                    ans[cur][i][k] = temp[0][k];
                }
            } else {
                for (k = 0; k < c; k++) {
                    temp[0][k] += v[j][k];
                }
            }
        }
    }
}

void push_rec(int cur, int cL, int cR, int l, int r) {
    int m = mid(cL, cR);
    temp[1][m] = INT_INF;
    int ind = l, i;
    for (i = l; i <= r; i++) {
        if (temp[0][i] + ans[cur][i][m] < temp[1][m]) {
            temp[1][m] = temp[0][i] + ans[cur][i][m];
            ind = i;
        }
    }
    if (cL != m) push_rec(cur, cL, m - 1, l, ind);
    if (cR != m) push_rec(cur, m + 1, cR, ind, r);
}

void push(int cur, int m) {
    int i, j;
    for (i = 0; i < c; i++) {
        for (j = 0; j < c; j++) {
            temp[0][j] = ans[l(cur)][i][j] + v[m][j];
        }
        push_rec(r(cur), 0, c - 1, 0, c - 1);
        for (j = 0; j < c; j++) {
            ans[cur][i][j] = temp[1][j];
        }
    }
}

void build(int cur, int cL, int cR) {
    if (cR - cL <= SZ) {
        calc(cur, cL, cR);
        return;
    }
    int m = mid(cL, cR);
    build(l(cur), cL , m);
    build(r(cur), m + 1, cR);
    push(cur, m);
}

void update(int cur, int cL, int cR, int ind) {
    if (cR - cL <= SZ) {
        calc(cur, cL, cR);
        return;
    }
    int m = mid(cL, cR);
    if (ind <= m) update(l(cur), cL , m, ind);
    else update(r(cur), m + 1, cR, ind);
    push(cur, m);
}

void init(int R, int C, int H[5000][200], int V[5000][200]) {
    r = R;
    c = C;
    int i, j;
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            h[i][j] = H[i][j];
            v[i][j] = V[i][j];
        }
    }
    build(1, 0, r - 1);
}

void changeH(int P, int Q, int W) {
    h[P][Q] = W;
    update(1, 0, r - 1, P);
}

void changeV(int P, int Q, int W) {
    v[P][Q] = W;
    update(1, 0, r - 1, P);
}

int escape(int V1, int V2) {
    return ans[1][V1][V2];
}

int main() {
    ri(r);
    ri(c);
    int i, j;
    for (i = 0; i < r; i++) {
        for (j = 0; j < c - 1; j++) {
            ri(h[i][j]);
        }
    }
    for (i = 0; i < r - 1; i++) {
        for (j = 0; j < c; j++) {
            ri(v[i][j]);
        }
    }
    init(r, c, h, v);
    int Q;
    ri(Q);
    int t, p, q, w, v1, v2;
    for (i = 0; i < Q; i++) {
        ri(t);
        if (t == 1) {
            ri(p);
            ri(q);
            ri(w);
            changeH(p, q, w);
        } else if (t == 2) {
            ri(p);
            ri(q);
            ri(w);
            changeV(p, q, w);
        } else if (t == 3) {
            ri(v1);
            ri(v2);
            printf("%d\n", escape(v1, v2));
        } else {
            i--;
        }
    }
    return 0;
}
