#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
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

#define MAXN 10005
#define MAXP 1005
#define MAXC 205

struct provEdge {
    int from, fromID, to, toID;
    ll weight;
};

int N, M, Q, id[MAXN], low[MAXN], pre, cnt, ind[MAXN], in[MAXP][MAXP], root[MAXP][MAXP];
bool marked[MAXN];
ll smallDist[MAXP][MAXC][MAXC], largeDist[MAXP][MAXP];
vector<pill> G[MAXN];
vector<pill> G2[MAXP][MAXC];
vector<provEdge> prov[MAXP];
vector<vector<int>> component;
stack<int> s;

void dfs(int v) {
    marked[v] = true;
    low[v] = pre++;
    int minV = low[v];
    s.push(v);
    for (pill e : G[v]) {
        if (!marked[e.f]) dfs(e.f);
        MIN(minV, low[e.f]);
    }
    if (minV < low[v]) {
        low[v] = minV;
        return;
    }
    int w;
    component.pb({});
    do {
        w = s.top();
        s.pop();
        id[w] = cnt;
        component[cnt].pb(w);
        low[w] = N;
    } while (w != v);
    cnt++;
}

void scc() {
    FOR(v, N) marked[v] = false;
    pre = 0;
    cnt = 0;
    FOR(v, N) if (!marked[v]) dfs(v);
}

void buildSmall() {
    FOR(i, cnt) FOR(j, sz(component[i])) ind[component[i][j]] = j;
    FOR(v, N) for (pill e : G[v]) if (id[v] == id[e.f]) G2[id[v]][ind[v]].pb({ind[e.f], e.s});
}

void dijkstraSmall() {
    FOR(i, cnt) {
        FOR(s, sz(component[i])) {
            minpq<plli> PQ;
            FOR(v, sz(component[i])) smallDist[i][s][v] = LL_INF;
            smallDist[i][s][s] = 0;
            PQ.push({smallDist[i][s][s], s});
            while (!PQ.empty()) {
                int v = PQ.top().s;
                PQ.pop();
                for (pill e : G2[i][v]) {
                    if (smallDist[i][s][e.f] > smallDist[i][s][v] + e.s) {
                        smallDist[i][s][e.f] = smallDist[i][s][v] + e.s;
                        PQ.push({smallDist[i][s][e.f], e.f});
                    }
                }
            }
        }
    }
}

void buildLarge() {
    FOR(v, N) {
        for (pill e : G[v]) {
            if (id[v] != id[e.f]) {
                prov[id[v]].pb({v, id[v], e.f, id[e.f], e.s});
                prov[id[e.f]].pb({e.f, id[e.f], v, id[v], e.s});
            }
        }
    }
}

void bfsLarge() {
    FOR(s, cnt) {
        queue<pair<int, pii>> q;
        FOR(v, cnt) {
            marked[v] = false;
            largeDist[s][v] = LL_INF;
        }
        largeDist[s][s] = 0;
        in[s][s] = -1;
        root[s][s] = -1;
        marked[s] = true;
        q.push({s, {-1, -1}});
        while (!q.empty()) {
            pair<int, pii> v = q.front();
            q.pop();
            for (provEdge &e : prov[v.f]) {
                if (marked[e.toID]) continue;
                largeDist[s][e.toID] = largeDist[s][v.f] + e.weight + (v.s.f == -1 ? 0 : smallDist[v.f][ind[v.s.f]][ind[e.from]]);
                in[s][e.toID] = e.to;
                root[s][e.toID] = v.s.s == -1 ? e.from : v.s.s;
                marked[e.toID] = true;
                q.push({e.toID, {e.to, root[s][e.toID]}});
            }
        }
    }
}

ll query(int a, int b) {
    if (id[a] == id[b]) return smallDist[id[a]][ind[a]][ind[b]];
    return largeDist[id[a]][id[b]] + smallDist[id[a]][ind[a]][ind[root[id[a]][id[b]]]] + smallDist[id[b]][ind[in[id[a]][id[b]]]][ind[b]];
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> Q;
    int a, b;
    ll d;
    FOR(i, M) {
        cin >> a >> b >> d;
        a--; b--;
        G[a].pb({b, d});
    }
    scc();
    buildSmall();
    dijkstraSmall();
    buildLarge();
    bfsLarge();
    FOR(i, Q) {
        cin >> a >> b;
        a--; b--;
        cout << query(a, b) << nl;
    }
    return 0;
}
