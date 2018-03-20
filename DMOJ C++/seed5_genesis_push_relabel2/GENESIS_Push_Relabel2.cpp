#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
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
#define randi(a, b) rand() % (b - a + 1) + a

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

typedef int unit;
const unit INF = (1 << 30);
const unit EPS = 0;

class PushRelabelMaxFlowCompact {
private:
    struct Edge {
        int dest;
        unit cap;
        int next;
        Edge(int dest, unit cost, int next) : dest(dest), cap(cost), next(next) {}
    };

    int V;
    vector<int> last;
    vector<Edge> e;
    vector<int> height;
    vector<unit> excess;
    vector<bool> done;

public:
    PushRelabelMaxFlowCompact(int V) : V(V), last(V), height(V), excess(V), done(V) {
        fill(last.begin(), last.end(), -1);
        fill(height.begin(), height.end(), 0);
        fill(excess.begin(), excess.end(), 0);
        fill(done.begin(), done.end(), false);
    }

    void addEdge(int v, int w, unit vw, unit wv = 0) {
        e.emplace_back(w, vw, last[v]);
        last[v] = ((int) e.size()) - 1;
        e.emplace_back(v, wv, last[w]);
        last[w] = ((int) e.size()) - 1;
    }

    unit getFlow(int s, int t)  {
        if (s == t) throw invalid_argument("Source equals sink");
        queue<int> q;
        height[s] = V;
        for (int i = last[s]; i != -1; i = e[i].next) {
            int v = e[i].dest;
            excess[s] -= e[i].cap;
            excess[v] += e[i].cap;
            e[i ^ 1].cap = e[i].cap;
            e[i].cap = 0;
            if (v != t) {
                done[v] = true;
                q.push(v);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            int tempHeight = 2 * V;
            for (int i = last[v]; i != -1; i = e[i].next) {
                if (abs(excess[v]) <= EPS) break;
                int w = e[i].dest;
                if (e[i].cap > EPS) {
                    if (height[v] > height[w]) {
                        unit tempFlow = min(excess[v], e[i].cap);
                        e[i].cap -= tempFlow;
                        e[i ^ 1].cap += tempFlow;
                        excess[v] -= tempFlow;
                        excess[w] += tempFlow;
                        if (!done[w] && w != s && w != t) {
                            done[w] = true;
                            q.push(w);
                        }
                    } else if (height[w] < tempHeight) {
                        tempHeight = height[w];
                    }
                }
            }
            if (excess[v] > EPS) height[v] = tempHeight + 1;
            else {
                done[v] = false;
                q.pop();
            }
        }
        return excess[t];
    }
};

inline int in(int i) {
    return (i - 1) * 2;
}

inline int out(int i) {
    return i * 2 - 1;
}

int N, M, E, v, w;
PushRelabelMaxFlowCompact *mf;

int main() {
    ri(N);
    mf = new PushRelabelMaxFlowCompact(out(N));
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
    printf("%d\n", (int) mf->getFlow(in(1), in(N)));
    return 0;
}
