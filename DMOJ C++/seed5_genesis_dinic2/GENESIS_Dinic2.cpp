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

typedef int unit;
const unit INF = 0x3f3f3f3f;
const unit EPS = 0;

class DinicMaxFlow {
private:
    struct Edge {
        int dest;
        unit cost;
        int next;
        Edge(int dest, unit cost, int next) : dest(dest), cost(cost), next(next) {}
    };

    int N, s = 0, t = 0;
    vector<int> last, level;
    vector<Edge> e;

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i = last[v]; i != -1; i = e[i].next) {
                if (e[i].cost > 0 && level[e[i].dest] == -1) {
                    level[e[i].dest] = level[v] + 1;
                    q.push(e[i].dest);
                }
            }
        }
        return level[t] != -1;
    }

    unit dfs(int v, unit flow) {
        if (v == t) return flow;
        unit ret = 0;
        for (int i = last[v]; i != -1; i = e[i].next) {
            if (e[i].cost > 0 && level[e[i].dest] == level[v] + 1) {
                unit res = dfs(e[i].dest, min(flow, e[i].cost));
                ret += res;
                e[i].cost -= res;
                e[i ^ 1].cost += res;
                flow -= res;
                if (abs(flow) <= EPS) break;
            }
        }
        return ret;
    }

public:
    DinicMaxFlow(int N) : N(N), last(N), level(N) {
        fill(last.begin(), last.end(), -1);
    }

    void addEdge(int v, int w, int vw, int wv = 0) {
        e.push_back(Edge(w, vw, last[v]));
        last[v] = ((int) e.size()) - 1;
        e.push_back(Edge(v, wv, last[w]));
        last[w] = ((int) e.size()) - 1;
    }

    unit getFlow(int src, int sink) {
        s = src;
        t = sink;
        unit res = 0;
        while (bfs()) res += dfs(s, INF);
        return res;
    }
};

inline int in(int i) {
    return (i - 1) * 2;
}

inline int out(int i) {
    return i * 2 - 1;
}

int N, M, E, v, w;
DinicMaxFlow *mf;

int main() {
    ri(N);
    mf = new DinicMaxFlow(out(N));
    for (int i = 1; i <= N - 1; i++) {
        ri(E);
        mf->addEdge(in(i), out(i), E);
    }
    ri(M);
    for (int i = 0; i < M; i++) {
        ri(v);
        ri(w);
        mf->addEdge(out(v), in(w), INT_INF);
    }
    printf("%d\n", mf->getFlow(in(1), in(N)));
    return 0;
}
