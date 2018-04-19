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

class EdmondsKarpMaxFlow {
private:
    struct Edge {
        int to;
        unit cap;
        int next;
        Edge(int to, unit cap, int next) : to(to), cap(cap), next(next) {}
    };

    int N, s = 0, t = 0;
    vector<int> edgeTo;
    vector<bool> marked;
    vector<Edge> e;
    vector<int> last;

    bool bfs() {
        fill(marked.begin(), marked.end(), false);
        fill(edgeTo.begin(), edgeTo.end(), -1);
        queue<int> q;
        q.push(s);
        marked[s] = true;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i = last[v]; i != -1; i = e[i].next) {
                if (e[i].cap > EPS && !marked[e[i].to]) {
                    marked[e[i].to] = true;
                    edgeTo[e[i].to] = i;
                    q.push(e[i].to);
                }
            }
        }
        return marked[t];
    }

public:
    EdmondsKarpMaxFlow(int N) : N(N), edgeTo(N), marked(N), last(N) {
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
        while (bfs()) {
            unit bottle = INF;
            for (int v = t; v != s; v = e[edgeTo[v] ^ 1].to) {
                bottle = min(bottle, e[edgeTo[v]].cap);
            }
            for (int v = t; v != s; v = e[edgeTo[v] ^ 1].to) {
                e[edgeTo[v]].cap -= bottle;
                e[edgeTo[v] ^ 1].cap += bottle;
            }
            res += bottle;
        }
        return res;
    }
};

#define MAXN 255

const int radius = 100;
int N, W, L;
pdd P[MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> L >> W >> N;
    FOR(i, N) cin >> P[i].f >> P[i].s;
    EdmondsKarpMaxFlow mf(N * 2 + 2);
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
