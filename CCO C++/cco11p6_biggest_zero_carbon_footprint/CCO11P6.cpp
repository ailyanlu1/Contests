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

#define MAXT 10010
#define x first
#define y second

bool xOrder(pii &p, pii &q) {
    return p.x == q.x ? p.y < q.y : p.x < q.x;
}

bool yOrder(pii &p, pii &q) {
    return p.y == q.y ? p.x < q.x : p.y < q.y;
}

int N, M, T, ans = 0;
pii p[MAXT];

int main() {
    ri(N);
    ri(M);
    ri(T);
    for (int i = 0; i < T; i++) {
        ri(p[i].x);
        ri(p[i].y);
    }
    p[T++] = {0, 0};
    p[T++] = {0, M};
    p[T++] = {N, 0};
    p[T++] = {N, M};
    sort(p, p + T, xOrder);
    for (int i = 0; i < T; i++) {
        int minY = 0, maxY = M;
        for (int j = i + 1; j < T; j++) {
            if (p[i].x == p[j].x) continue;
            ans = max(ans, (maxY - minY) * (p[j].x - p[i].x));
            if (p[i].y > p[j].y) minY = max(minY, p[j].y);
            else maxY = min(maxY, p[j].y);
        }
    }
    sort(p, p + T, yOrder);
    for (int i = 0; i < T; i++) {
        int minX = 0, maxX = N;
        for (int j = i + 1; j < T; j++) {
            if (p[i].y == p[j].y) continue;
            ans = max(ans, (maxX - minX) * (p[j].y - p[i].y));
            if (p[i].x > p[j].x) minX = max(minX, p[j].x);
            else maxX = min(maxX, p[j].x);
        }
    }
    printf("%d\n", ans);
    return 0;
}
