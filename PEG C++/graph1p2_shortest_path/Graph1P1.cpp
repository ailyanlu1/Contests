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
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define Forx(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define Revx(i, a) Rev(i, a, -1)
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

#define MAXN 105

bool marked[MAXN];
int N, distTo[MAXN], adj[MAXN][MAXN];

int bfs(int s, int t) {
    queue<int> q;
    Forx(v, N) {
        distTo[v] = INT_MAX;
        marked[v] = false;
    }
    distTo[s] = 0;
    marked[s] = true;
    q.push(s);

    while(!q.empty()) {
        int v = q.front();
        q.pop();
        if (v == t) return distTo[t];
        Forx(w, N) {
            if (!adj[v][w] || marked[w]) continue;
            distTo[w] = distTo[v] + 1;
            marked[w] = true;
            q.push(w);
        }
    }
    return -1;
}

int main() {
    ri(N);
    Forx(i, N) {
        Forx(j, N) {
            ri(adj[i][j]);
        }
    }
    printf("%d\n", bfs(0, N - 1));
    return 0;
}
