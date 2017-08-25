#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
#define mid(x, y) (x + (y - x) / 2)
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
#define randi(a, b) (rand() % (b - a + 1) + a)

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<int, float> pif;
typedef pair<float, int> pfi;
typedef pair<double, double> pdd;
typedef pair<int, double> pid;
typedef pair<double, int> pdi;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef pair<llu, llu> pllu;
typedef pair<int, llu> pillu;
typedef pair<llu, int> pllui;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

#define MAXH 600

double A[MAXH][MAXH], b[MAXH], x[MAXH], tl, tr, bl, br, c;
int N, H;

void solve() {
    for (int p = 0; p < H; p++) {
        // find pivot row and swap
        int m = p;
        for (int i = p + 1; i < H; i++) {
            if (abs(A[i][p]) > abs(A[m][p])) m = i;
        }
        swap(A[p], A[m]);
        swap(b[p], b[m]);
        // singular or nearly singular
        // pivot within A and b
        for (int i = p + 1; i < H; i++) {
            double alpha = A[i][p] / A[p][p];
            b[i] -= alpha * b[p];
            for (int j = p; j < H; j++) {
                A[i][j] -= alpha * A[p][j];
            }
        }
    }
    // back substitution
    for (int i = 0; i < H; i++) {
        x[i] = 0.0;
    }
    for (int i = H - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < H; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }
}

int main() {
    ri(N);
    H = N * (N + 1) / 2;
    for (int i = 0; i < H; i++) {
        rd(b[i]);
    }
    for (int i = 0, k = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            rd(tl);
            rd(tr);
            rd(bl);
            rd(br);
            rd(c);
            if (k - i - 1 >= 0) A[k][k - i - 1] = tl;
            if (k - i >= 0) A[k][k - i] = tr;
            if (k + i + 1 < H) A[k][k + i + 1] = bl;
            if (k + i + 2 < H) A[k][k + i + 2] = br;
            A[k][k] = -1;
            b[k] *= -c;
            k++;
        }
    }
    solve();
    printf("%f", x[0]);
    return 0;
}
