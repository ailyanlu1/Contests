#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) ((x) << 1)
#define r(x) ((x) << 1 | 1)
#define m(x, y) ((x) + ((y) - (x)) / 2)
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
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
#define FILL(a, x) memset((a), (x), sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
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
typedef map<ll, ll> mll;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;
typedef unordered_map<ll, ll> umll;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXN 1000010

int N, K, a, b;
ll C[MAXN];
vector<int> adj[MAXN];

inline void addEdge(int v, int w) {
    adj[v].pb(w);
    adj[w].pb(v);
}

int findLongest(int v, int prev, ll even, ll odd, bool hasEven, bool hasOdd, int len, int run) {
    if (len % 2 == 0) {
        if (hasEven && C[v] == even) run++;
        else {
            hasEven = true;
            even = C[v];
            run = hasOdd ? 2 : 1;
        }
    } else {
        if (hasOdd && C[v] == odd) run++;
        else {
            hasOdd = true;
            odd = C[v];
            run = hasEven ? 2 : 1;
        }
    }
    if (run >= K) return -1;
    int ret = len;
    for (int w : adj[v]) {
        if (w == prev) continue;
        MAX(ret, findLongest(w, v, even, odd, hasEven, hasOdd, len + 1, run));
    }
    return ret;
}

pii findDiameter(int v, int prev, int dist) {
    pii ret = {dist, v};
    for (int w : adj[v]) {
        if (w == prev) continue;
        MAX(ret, findDiameter(w, v, dist + 1));
    }
    return ret;
}

int solve1() {
    int ans = -1;
    FOR(v, N) {
        MAX(ans, findLongest(v, -1, -1, -1, false, false, 1, 0));
    }
    return ans;
}

int solve2() {
    pii furthest = findDiameter(0, -1, 0);
    return findLongest(furthest.s, -1, -1, -1, false, false, 1, 0);
}

int main() {
    ri(N);
    ri(K);
    FOR(i, N) {
        rll(C[i]);
    }
    FOR(i, N - 1) {
        ri(a);
        ri(b);
        addEdge(a - 1, b - 1);
    }
    if (N == K) {
        printf("%d\n", solve2());
    } else {
        printf("%d\n", solve1());
    }
    return 0;
}
