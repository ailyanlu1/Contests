#include <bits/stdc++.h>
using namespace std;

#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define f first
#define s second
#define all(a) (a).begin(), (a).end()
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pill pair<int, ll>
#define plli pair<ll, int>
#define pdd pair<double, double>
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

typedef int unit;
const unit INF = (1 << 30);
const unit EPS = 0;

// O(V ^ 2 * E) in the worst case, O(min(V ^ (2 / 3), E ^ (1 / 2)) * E) for unit values
class DinicMaxFlow {
private:
    struct Edge {
        int to;
        unit cap;
        int next;
        Edge(int to, unit cap, int next) : to(to), cap(cap), next(next) {}
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
                if (e[i].cap > EPS && level[e[i].to] == -1) {
                    level[e[i].to] = level[v] + 1;
                    q.push(e[i].to);
                }
            }
        }
        return level[t] != -1;
    }

    unit dfs(int v, unit flow) {
        if (v == t) return flow;
        unit ret = 0;
        for (int i = last[v]; i != -1; i = e[i].next) {
            if (e[i].cap > EPS && level[e[i].to] == level[v] + 1) {
                unit res = dfs(e[i].to, min(flow, e[i].cap));
                ret += res;
                e[i].cap -= res;
                e[i ^ 1].cap += res;
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

    void addEdge(int v, int w, unit vw, unit wv = 0) {
        e.emplace_back(w, vw, last[v]);
        last[v] = ((int) e.size()) - 1;
        e.emplace_back(v, wv, last[w]);
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

#define MAXN 255

const int radius = 100;
int N, W, L;
pll P[MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> L >> W >> N;
    FOR(i, N) cin >> P[i].f >> P[i].s;
    DinicMaxFlow mf(N * 2 + 2);
    int s = N * 2, t = N * 2 + 1;
    FOR(i, N) mf.addEdge(i * 2, i * 2 + 1, 1);
    FOR(i, N) {
        if (P[i].s <= radius) mf.addEdge(s, i * 2, 1);
        if (P[i].s >= W - radius) mf.addEdge(i * 2 + 1, t, 1);
    }
    FOR(i, N) {
        FOR(j, N) {
            if (i == j) continue;
            if ((P[i].f - P[j].f) * (P[i].f - P[j].f) + (P[i].s - P[j].s) * (P[i].s - P[j].s) <= 4 * radius * radius) mf.addEdge(i * 2 + 1, j * 2, 1);
        }
    }
    cout << mf.getFlow(s, t) << endl;
    return 0;
}
