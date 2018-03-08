#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define f first
#define s second
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl "\n"

#define ll long long
#define ld long double
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXN 205

umap<char, int> c2i;
char i2c[4] = {'C', 'A', 'L', 'I'};
int dir[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};
int N;
char G[MAXN][MAXN];

typedef int unit;
const unit INF = (1 << 30);
const unit EPS = 0;

class DinicMaxFlow {
private:
    struct Edge {
        int dest;
        unit flow;
        int next;
        Edge(int dest, unit cost, int next) : dest(dest), flow(cost), next(next) {}
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
                if (e[i].flow > EPS && level[e[i].dest] == -1) {
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
            if (e[i].flow > EPS && level[e[i].dest] == level[v] + 1) {
                unit res = dfs(e[i].dest, min(flow, e[i].flow));
                ret += res;
                e[i].flow -= res;
                e[i ^ 1].flow += res;
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
} *mf;

bool isPoint(int i, int j) {
    return i >= 0 && i < N && j >= 0 && j < N;
}

int in(int x) {
    return 2 * x;
}

int out(int x) {
    return 2 * x + 1;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    FOR(i, 4) c2i[i2c[i]] = i;
    cin >> N;
    mf = new DinicMaxFlow(2 * N * N + 2);
    FOR(i, N) {
        FOR(j, N) {
            do {
                cin.get(G[i][j]);
            } while (isspace(G[i][j]));
        }
    }
    int src = 2 * N * N;
    int sink = 2 * N * N + 1;
    FOR(i, N) {
        FOR(j, N) {
            mf->addEdge(in(i * N + j), out(i * N + j), 1);
            if (G[i][j] == 'I') {
                mf->addEdge(out(i * N + j), sink, 1);
                continue;
            }
            if (G[i][j] == 'C') mf->addEdge(src, in(i * N + j), 1);
            char nxt = i2c[c2i[G[i][j]] + 1];
            FOR(k, 8) {
                if (isPoint(i + dir[k][0], j + dir[k][1]) && G[i + dir[k][0]][j + dir[k][1]] == nxt) {
                    mf->addEdge(out(i * N + j), in((i + dir[k][0]) * N + (j + dir[k][1])), 1);
                }
            }
        }
    }
    cout << mf->getFlow(src, sink) << nl;
    return 0;
}
