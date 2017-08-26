#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
#define m(x, y) (x + (y - x) / 2)
#define Min(a, b) (a = min(a, b))
#define Max(a, b) (a = max(a, b))
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
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

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return hash<T1> {}(p.first) << 31 | hash<T2> {}(p.second);}};

#define MAXK 25

int K, k, lights = 0;
char dp[1 << MAXK];
queue<int> q;

int main() {
    ri(K);
    FOR(i, K) {
        ri(k);
        lights = 2 * lights + k;
    }
    FOR(i, 1 << K) {
        dp[i] = -1;
    }
    dp[lights] = 0;
    q.push(lights);
    int s, l, r, next;
    while (!q.empty()) {
        s = q.front();
        q.pop();
        if (s == 0) break;
        FOR(i, K) {
            if (!(s & (1 << i))) {
                next = s ^ (1 << i);
                l = i - 1;
                r = i + 1;
                while (l >= 0 && (next & (1 << l))) {
                    l--;
                }
                while (r < K && (next & (1 << r))) {
                    r++;
                }
                if (r - l - 1 >= 4) {
                    For(j, l + 1, r) {
                        next ^= (1 << j);
                    }
                }
                if (dp[next] == -1) {
                    dp[next] = dp[s] + 1;
                    q.push(next);
                }
            }
        }
    }
    printf("%d\n", (int) dp[0]);
    return 0;
}
