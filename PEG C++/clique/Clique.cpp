#include <bits/stdc++.h>
using namespace std;

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
#define rld(x) scanf("%Lf", &x)
#define rc(x) scanf(" %c", &x)
#define sc(x) do { scanf("%c", &x); } while (isspace(x))
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define set0(a) memset((a), 0, sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define Fill2(a, x, n, m) FOR(_, n) FOR(__, m) (a)[_][__] = (x)
#define Fill3(a, x, n, m, p) FOR(_, n) FOR(__, m) FOR(___, p) (a)[_][__][___] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))
#define sz(a) ((int) (a).size())
#define len(a) ((int) (a).length())

typedef long long ll;
typedef unsigned long long llu;
typedef long double ld;
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef map<ll, ll> mll;
typedef umap<int, int> umii;
typedef umap<int, ll> umill;
typedef umap<ll, int> umlli;
typedef umap<ll, ll> umll;
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

#define debug(fmt, x) fprintf(stderr, "%d::%s = " fmt, __LINE__, #x, (x)); fflush(stderr)
#define debug2(x) cerr << __LINE__ << "::" << #x << " = " << (x) << '\n' << flush
#define debugva(fmt, ...) fprintf(stderr, "%d::%s = " fmt, __LINE__, #__VA_ARGS__, __VA_ARGS__); fflush(stderr)
#define debugarr(fmt, x, a, b) fprintf(stderr, "%d::%s = {", __LINE__, #x); For(_, a, b) { if (_ != (a)) { fprintf(stderr, ", "); } fprintf(stderr, fmt, (x)[_]); } fprintf(stderr, "}\n"); fflush(stderr)
#define debugarr2(x, a, b) cerr << __LINE__ << "::" << #x << " = {"; For(_, a, b) { if (_ != (a)) { cerr << ", "; } cerr << (x)[_]; } cerr << "}\n" << flush

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

class BronKerboschMaxClique {
private:
    bool **adj;
    int *W;
    int maxClique;

    int solve(int nodes, int curr, int pool, int excl) {
        if (pool == 0 && excl == 0) {
            int cnt = 0;
            for (int i = 0; i < nodes; i++)
                if ((curr & 1LL << i) > 0) cnt += W[i];
            return cnt;
        }
        int res = 0;
        int j = 0;
        for (int i = 0; i < nodes; i++)
            if ((pool & 1LL << i) > 0 || (excl & 1LL << i) > 0) j = i;
        for (int i = 0; i < nodes; i++) {
            if ((pool & 1LL << i) == 0 || adj[i][j]) continue;
            int ncurr = curr, npool = 0, nexcl = 0;
            ncurr |= 1LL << i;
            for (int k = 0; k < nodes; k++) {
                if (adj[i][k]) {
                    npool |= pool & 1LL << k;
                    nexcl |= excl & 1LL << k;
                }
            }
            res = max(res, solve(nodes, ncurr, npool, nexcl));
            pool &= ~(1LL << i);
            excl |= 1 >> i;
        }
        return res;
    }

public:
    /**
     * Adjacency matrix graph constructor.
     *
     * @param G an adjacency matrix graph
     * @param V the number of vertices
     */
    BronKerboschMaxClique(bool **G, int V) {
        adj = new bool*[V];
        W = new int[V];
        for (int v = 0; v < V; v++) {
            W[v] = 1;
            adj[v] = new bool[V];
            for (int w = 0; w < V; w++) adj[v][w] = G[v][w];
        }
        maxClique = solve(V, 0, (1LL << V) - 1, 0);
    }

    int getMaxClique() {
        return maxClique;
    }
} *mc;

#define MAXN 32

int N, M;
bool **adj;

int main() {
    ri(N);
    ri(M);
    adj = new bool*[N];
    FOR(i, N) {
        adj[i] = new bool[N];
        FOR(j, N) adj[i][j] = 0;
    }
    int a, b;
    Fill2(adj, 0, N, N);
    FOR(i, M) {
        ri(a);
        ri(b);
        adj[a - 1][b - 1] = adj[b - 1][a - 1] = 1;
    }
    mc = new BronKerboschMaxClique(adj, N);
    printf("%d\n", mc->getMaxClique());
    return 0;
}
