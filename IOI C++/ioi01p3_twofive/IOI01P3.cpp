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
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

#define SZ 5

int dp[SZ + 1][SZ + 1][SZ + 1][SZ + 1][SZ + 1], pos[25], ord = 0, nxt;
char str[SZ * SZ], op;

int to1D(int i, int j) {
    return i * SZ + j;
}

int get(int a, int b, int c, int d, int e) {
    if (a > SZ || b > SZ || c > SZ || d > SZ || e > SZ) return 0;
    if (a < b || b < c || c < d || d < e) return 0;
    if (dp[a][b][c][d][e] != -1) return dp[a][b][c][d][e];
    int s = a + b + c + d + e;
    if (s == SZ * SZ) return 1;
    int ret = 0;
    if (pos[to1D(0, a)] == -1 || pos[to1D(0, a)] == s) ret += get(a + 1, b, c, d, e);
    if (pos[to1D(1, b)] == -1 || pos[to1D(1, b)] == s) ret += get(a, b + 1, c, d, e);
    if (pos[to1D(2, c)] == -1 || pos[to1D(2, c)] == s) ret += get(a, b, c + 1, d, e);
    if (pos[to1D(3, d)] == -1 || pos[to1D(3, d)] == s) ret += get(a, b, c, d + 1, e);
    if (pos[to1D(4, e)] == -1 || pos[to1D(4, e)] == s) ret += get(a, b, c, d, e + 1);
    return dp[a][b][c][d][e] = ret;
}

int main() {
    Fill(pos, -1);
    rc(op);
    if (op == 'W') {
        rs(str);
        for (int i = 0; i < SZ * SZ; i++) {
            for (pos[i] = 0; pos[i] < str[i] - 'A'; pos[i]++) {
                Fill(dp, -1);
                ord += get(0, 0, 0, 0, 0);
            }
        }
        printf("%d\n", ord + 1);
    } else {
        ri(ord);
        for (int i = 0; i < SZ * SZ; i++) {
            for (pos[i] = 0; pos[i] < SZ * SZ; pos[i]++) {
                Fill(dp, -1);
                nxt = get(0, 0, 0, 0, 0);
                if (nxt >= ord) break;
                ord -= nxt;
            }
        }
        for (int i = 0; i < SZ * SZ; i++) {
            printf("%c", pos[i] + 'A');
        }
        printf("\n");
    }
    return 0;
}
