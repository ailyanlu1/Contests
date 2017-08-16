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

#define MAXN 205
#define DLEN 4
#define SLEN 7
#define R first
#define C second

int N, K, M, r, c, d = 0, w = 0, k = 0;
ll day = 0LL;
const pii moves[DLEN] = {mp(0, 1), mp(1, 0), mp(0, -1), mp(-1, 0)};
char schedule[MAXN][MAXN][SLEN + 1];
pair<ll, int> state[MAXN][MAXN][DLEN][SLEN];

int main() {
    ri(N);
    ri(K);
    ri(M);
    for (int i = 0; i < M; i++) {
        ri(r);
        ri(c);
        rs(schedule[r - 1][c - 1]);
    }
    r = 0;
    c = 0;
    ll difDays;
    int difMoves, remMoves;
    while (k < K) {
        if (schedule[r][c][w] == 'L') {
            d = (d + 3) % DLEN;
            k++;
        } else if (schedule[r][c][w] == 'R') {
            d = (d + 1) % DLEN;
            k++;
        }
        if (r + moves[d].R < 0 || r + moves[d].R >= N || c + moves[d].C < 0 || c + moves[d].C >= N) {
            d = (d + 2) % DLEN;
            k++;
        }
        if (state[r][c][d][w].f > 0) {
            difDays = day - state[r][c][d][w].f;
            difMoves = k - state[r][c][d][w].s;
            remMoves = K - k;
            day += remMoves / difMoves * difDays;
            k += remMoves - remMoves % difMoves;
        }
        state[r][c][d][w] = {day, k};
        r += moves[d].R;
        c += moves[d].C;
        w = (w + 1) % SLEN;
        if (k < K) day++;
    }
    printf("%lld\n", day);
    return 0;
}
