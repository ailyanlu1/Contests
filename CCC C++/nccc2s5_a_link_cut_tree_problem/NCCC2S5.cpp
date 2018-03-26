#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
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

#define MAXN 1005

struct Edge {
    int v, w, weight;

    Edge(int v, int w, int weight) : v(v), w(w), weight(weight) {}

    int other(int u) {
        return u == v ? w : v;
    }
};

bool Edge_cmp_lt (Edge *a, Edge *b) {
    return a->weight < b->weight;
}

bool Edge_cmp_gt (Edge *a, Edge *b) {
    return a->weight > b->weight;
}

int N, M, Q, PAR[MAXN], CNT;
char RNK[MAXN];
vector<Edge*> adj[MAXN];
vector<Edge*> edges;

void initUF() {
    CNT = N;
    FOR(i, N) {
        PAR[i] = i;
        RNK[i] = 0;
    }
}

int find(int p) {
    while (p != PAR[p]) p = PAR[p] = PAR[PAR[p]];
    return p;
}

bool join(int p, int q) {
    p = find(p);
    q = find(q);
    if (p == q) return false;
    if (RNK[p] < RNK[q]) PAR[p] = q;
    else if (RNK[p] > RNK[q]) PAR[q] = p;
    else {
        PAR[q] = p;
        RNK[p]++;
    }
    CNT--;
    return true;
}

void mst() {
    vector<Edge*> edges2 = edges;
    sort(all(edges2), Edge_cmp_gt);
    initUF();
    FOR(v, N) adj[v].clear();
    for (Edge *e : edges2) {
        if (join(e->v, e->w)) {
            adj[e->v].pb(e);
            adj[e->w].pb(e);
            if (CNT == 1) break;
        }
    }
}

bool dfs(int v, int prev, int t, int m) {
    if (v == t) return true;
    for (Edge *e : adj[v]) {
        int w = e->other(v);
        if (w == prev || e->weight < m) continue;
        if (dfs(w, v, t, m)) return true;
    }
    return false;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    int t, x, y, z;
    FOR(i, M) {
        cin >> x >> y >> z;
        x--; y--;
        Edge *e = new Edge(x, y, z);
        edges.pb(e);
    }
    mst();
    cin >> Q;
    FOR(i, Q) {
        cin >> t;
        if (t == 1) {
            cin >> x >> z;
            x--;
            edges[x]->weight = z;
            mst();
        } else if (t == 2) {
            cin >> x >> y >> z;
            x--; y--;
            cout << dfs(x, -1, y, z) << nl;
        } else {
            i--;
        }
    }
    return 0;
}
