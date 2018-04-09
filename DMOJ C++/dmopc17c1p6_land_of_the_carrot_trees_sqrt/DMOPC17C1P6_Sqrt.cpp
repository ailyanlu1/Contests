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

#define MAXNQ 100005

struct Edge {
    int from, to, val;

    bool operator == (const Edge &e) const {
        return from == e.from && to == e.to;
    }

    bool operator != (const Edge &e) const {
        return from != e.from || to != e.to;
    }
};

struct Edge_hash {
    size_t operator ()(const Edge &e) const {
        return 31 * hash<int> {}(e.from) + hash<int> {}(e.to);
    }
};


int N, Q, XOR[MAXNQ], COMP[MAXNQ];
bool vis[MAXNQ];
uset<Edge, Edge_hash> adj[MAXNQ], adj2[MAXNQ], edgesToRemove;
uset<pii, pair_hash<int, int>> toRemove;

struct Query {
    char op;
    int x, y, z;
};

vector<Query> QQ;

void preDFS(int v, int x, int comp) {
    XOR[v] = x;
    COMP[v] = comp;
    vis[v] = true;
    for (Edge e : adj[v]) {
        if (!vis[e.to]) {
            if (toRemove.count({v, e.to})) edgesToRemove.insert(e);
            else preDFS(e.to, x ^ e.val, comp);
        }
    }
}

int dfs(int v, int t, int prev, int x) {
    if (COMP[v] == COMP[t]) return x ^ XOR[v] ^ XOR[t];
    int ans = -1;
    for (Edge e : adj2[COMP[v]]) if (COMP[e.to] != COMP[prev]) MAX(ans, dfs(e.to, t, e.from, x ^ XOR[e.from] ^ XOR[v] ^ e.val));
    return ans;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    char op;
    int x, y, z;
    FOR(i, N - 1) {
        cin >> x >> y >> z;
        x--; y--;
        adj[x].insert({x, y, z});
        adj[y].insert({y, x, z});
    }
    int blockSZ = Q / (int) sqrt(N) * 12;
    FOR(qq, Q) {
        cin >> op;
        if (op == 'A') {
            cin >> x >> y >> z;
            x--; y--;
        } else if (op == 'R') {
            cin >> x >> y;
            x--; y--;
            toRemove.insert({x, y});
            toRemove.insert({y, x});
        } else if (op == 'Q') {
            cin >> x >> y;
            x--; y--;
        } else {
            qq--;
            continue;
        }
        QQ.pb({op, x, y, z});
        if (sz(QQ) == blockSZ || qq == Q - 1) {
            FOR(i, N) vis[i] = false;
            int cnt = 0;
            FOR(i, N) if (!vis[i]) preDFS(i, 0, cnt++);
            for (Edge e : edgesToRemove) {
                adj2[COMP[e.from]].insert({e.from, e.to, e.val});
                adj2[COMP[e.to]].insert({e.to, e.from, e.val});
            }
            edgesToRemove.clear();
            for (pii e: toRemove) {
                adj[e.f].erase({e.f, e.s, 0});
                adj[e.s].erase({e.s, e.f, 0});
            }
            toRemove.clear();
            for (Query &q : QQ) {
                if (q.op == 'A') {
                    adj2[COMP[q.x]].insert({q.x, q.y, q.z});
                    adj2[COMP[q.y]].insert({q.y, q.x, q.z});
                } else if (q.op == 'R') {
                    adj2[COMP[q.x]].erase({q.x, q.y, 0});
                    adj2[COMP[q.y]].erase({q.y, q.x, 0});
                } else {
                    cout << dfs(q.x, q.y, q.x, 0) << nl;
                }
            }
            FOR(i, N) {
                for (Edge e : adj2[i]) adj[e.from].insert({e.from, e.to, e.val});
                adj2[i].clear();
            }
            QQ.clear();
        }
    }
    return 0;
}
