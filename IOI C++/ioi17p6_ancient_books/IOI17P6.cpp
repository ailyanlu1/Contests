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

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

struct WeightedEdge {
private:
    int v, w;
    ll weight;

public:
    WeightedEdge(int v, int w, ll weight) {
        this->v = v;
        this->w = w;
        this->weight = weight;
    }

    ll getWeight() {
        return weight;
    }

    int either() {
        return v;
    }

    int other(int vertex) {
        if (vertex == v) return w;
        else if (vertex == w) return v;
        else throw new invalid_argument("Illegal endpoint");
    }

    bool operator == (const WeightedEdge &e) const {
        return (((v == e.v && w == e.w) || (v == e.w && w == e.v)) && weight == e.weight);
    }

    bool operator != (const WeightedEdge &e) const {
        return !(((v == e.v && w == e.w) || (v == e.w && w == e.v)) && weight == e.weight);
    }

    bool operator < (const WeightedEdge &e) const {
        return (weight < e.weight);
    }

    bool operator <= (const WeightedEdge &e) const {
        return (weight <= e.weight);
    }

    bool operator > (const WeightedEdge &e) const {
        return (weight > e.weight);
    }

    bool operator >= (const WeightedEdge &e) const {
        return (weight >= e.weight);
    }
};

struct WeightedEdge_less {
    const bool operator ()(const WeightedEdge *a, const WeightedEdge *b) const {
        return *a < *b;
    }
};

struct WeightedEdge_greater {
    const bool operator ()(const WeightedEdge *a, const WeightedEdge *b) const {
        return *a > *b;
    }
};

bool WeightedEdge_p_cmp_less (WeightedEdge *a, WeightedEdge *b) {
    return *a < *b;
}

bool WeightedEdge_p_cmp_greater (WeightedEdge *a, WeightedEdge *b) {
    return *a > *b;
}

struct WeightedGraph {
private:
    int V;
    int E;
    vector<WeightedEdge*> *adjList;

public:
    WeightedGraph(int V) {
        this->V = V;
        this->E = 0;
        adjList = new vector<WeightedEdge*>[V];
    }

    int getV() {
        return this->V;
    }

    int getE() {
        return this->E;
    }

    void addEdge(WeightedEdge *e) {
        int v = e->either();
        int w = e->other(v);
        adjList[v].push_back(e);
        adjList[w].push_back(e);
        E++;
    }

    vector<WeightedEdge*> &adj(int v) {
        return adjList[v];
    }

    int degree(int v) {
        return adjList[v].size();
    }

    vector<WeightedEdge*> &edges() {
        vector<WeightedEdge*> *list = new vector<WeightedEdge*>;
        for (int v = 0; v < V; v++) {
            int selfLoops = 0;
            for (WeightedEdge *e : adj(v)) {
                if (e->other(v) > v) {
                    list->push_back(e);
                }
                // only add one copy of each self loop (self loops will be consecutive)
                else if (e->other(v) == v) {
                    if (selfLoops % 2 == 0) list->push_back(e);
                    selfLoops++;
                }
            }
        }
        return *list;
    }
};

const pii MAXPII = mp(INT_INF, INT_INF);
const pii MINPII = mp(-INT_INF, -INT_INF);

struct MaxSegmentTree {
private:
    pii *tree;
    int depth;

public:
    MaxSegmentTree(int size) {
        for (depth = 1; depth <= size; depth <<= 1);
        this->tree = new pii[2 * depth];
        FOR (i, 2 * depth) {
            tree[i] = MINPII;
        }
    }

    void update(int ind, pii val) {
        int cur = ind + depth;
        tree[cur] = val;
        while (cur > 1) {
            cur >>= 1;
            tree[cur] = max(tree[l(cur)], tree[r(cur)]);
        }
    }

    pii query(int l, int r) {
        int cL = l + depth;
        int cR = r + depth;
        pii ret = MINPII;
        while (cL < cR) {
            if (cL % 2 == 1) ret = max(ret, tree[cL++]);
            if (cR % 2 == 0) ret = max(ret, tree[cR--]);
            cL >>= 1;
            cR >>= 1;
        }
        if (cL == cR) ret = max(ret, tree[cL]);
        return ret;
    }
};

struct MinSegmentTree {
private:
    pii *tree;
    int depth;

public:
    MinSegmentTree(int size) {
        for (depth = 1; depth <= size; depth <<= 1);
        this->tree = new pii[2 * depth];
        FOR (i, 2 * depth) {
            tree[i] = MAXPII;
        }
    }

    void update(int ind, pii val) {
        int cur = ind + depth;
        tree[cur] = val;
        while (cur > 1) {
            cur >>= 1;
            tree[cur] = min(tree[l(cur)], tree[r(cur)]);
        }
    }

    pii query(int l, int r) {
        int cL = l + depth;
        int cR = r + depth;
        pii ret = MAXPII;
        while (cL < cR) {
            if (cL % 2 == 1) ret = min(ret, tree[cL++]);
            if (cR % 2 == 0) ret = min(ret, tree[cR--]);
            cL >>= 1;
            cR >>= 1;
        }
        if (cL == cR) ret = min(ret, tree[cL]);
        return ret;
    }
};

#define MAXN 1000005

int N;
WeightedGraph *G;
MaxSegmentTree *maxTree;
MinSegmentTree *minTree;
bool marked[MAXN];
ll dist1[MAXN], dist2[MAXN], ans = 0LL;
vector<pii> all;

void dfs(int i) {
    marked[i] = true;
    maxTree->update(all[i].f, MINPII);
    minTree->update(all[i].s, MAXPII);
    pii q;
    FOR(flag, 2) {
        while (true) {
            q = flag == 0 ? maxTree->query(all[i].f + 1, all[i].s - 1) : minTree->query(all[i].f + 1, all[i].s - 1);
            if (flag == 0 ? q.f <= all[i].s : q.f >= all[i].f) break;
            G->addEdge(new WeightedEdge(q.f, all[i].s, 0));
            dfs(q.s);
        }
    }
}

ll dijkstraSP(int s, int t) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>> , greater<pair<ll, int>>> pq;
    for (int v = 0; v < G->getV(); v++) {
        dist2[v] = LL_INF;
    }
    dist2[s] = 0LL;
    pq.push({dist2[s], s});
    while (!pq.empty()) {
        int v = pq.top().second;
        if (v == t) return dist2[t];
        pq.pop();
        for (WeightedEdge *e : G->adj(v)) {
            int w = e->other(v);
            if (dist2[w] > dist2[v] + e->getWeight()) {
                dist2[w] = dist2[v] + e->getWeight();
                pq.push({dist2[w], w});
            }
        }
    }
    return -1;
}

ll minimum_walk(vector<int> p, int s) {
    N = p.size();
    G = new WeightedGraph(N);
    maxTree = new MaxSegmentTree(N);
    minTree = new MinSegmentTree(N);
    vector<int> temp;
    FOR(i, N) {
        if (!marked[i] && p[i] != i) {
            int x = i;
            while (true) {
                marked[x] = true;
                temp.pb(x);
                ans += abs(x - p[x]);
                if (!marked[p[x]]) G->addEdge(new WeightedEdge(x, p[x], 0));
                else break;
                x = p[x];
            }
            sort(temp.begin(), temp.end());
            FOR(j, (int) temp.size() - 1) {
                all.pb({temp[j], temp[j + 1]});
            }
            dist1[temp.front()]++;
            dist1[temp.back()]--;
            temp.clear();
        }
    }
    marked[s] = true;
    FOR(i, N - 1) {
        dist1[i + 1] += dist1[i];
    }
    int l = s, r = s;
    FOR(i, N) {
        if (dist1[i] != 0) {
            MIN(l, i);
            MAX(r, i + 1);
        }
    }
    For(i, l, r) {
        if (dist1[i] == 0) ans += 2;
    }
    FOR(i, (int) all.size()) {
        maxTree->update(all[i].f, {all[i].s, i});
        minTree->update(all[i].s, {all[i].f, i});
    }
    int lastInd = -1;
    FOR(i, N) {
        if (marked[i]) {
            if (lastInd != -1) G->addEdge(new WeightedEdge(lastInd, i, i - lastInd));
            lastInd = i;
            marked[i] = false;
        }
    }
    FOR(i, (int) all.size()) {
        if (!marked[i]) dfs(i);
    }
    int t = s;
    while (t > 0 && dist1[t - 1] != 0) t--;
    ans += 2 * dijkstraSP(s, t);
    return ans;
}

int main() {
    int n, pi, s;
    vector<int> p;
    ri(n);
    FOR(i, n) {
        ri(pi);
        p.pb(pi);
    }
    ri(s);
    printf("%lld\n", minimum_walk(p, s));
    return 0;
}
