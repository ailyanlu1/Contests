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

int N, C, numNodes;
ll K;
vector<ll> V, dist;
umap<int, vector<int>> Classes;
vector<vector<pill>> adj;

bool valCmp(const int &i, const int &j) {
    return V[i] < V[j];
}

void connect(vector<int> &s, int st, int en) {
    if (st >= en) return;
    int mid = st + (en - st) / 2;
    ll midVal = V[s[mid]] + (V[s[mid + 1]] - V[s[mid]]) / 2;
    numNodes++;
    adj.eb();
    for (int i = st; i <= en; i++) {
        adj[s[i]].pb({numNodes - 1, 2 * abs(V[s[i]] - midVal) + K});
        adj[numNodes - 1].pb({s[i], 2 * abs(V[s[i]] - midVal) + K});
    }
    connect(s, st, mid);
    connect(s, mid + 1, en);
}

void dijkstraSP(int s) {
    minpq<plli> PQ;
    FOR(i, numNodes) dist.pb(LL_INF);
    dist[s] = 0;
    PQ.push({dist[s], s});
    while (!PQ.empty()) {
        int v = PQ.top().s;
        PQ.pop();
        for (pill e : adj[v]) {
            if (dist[e.f] > dist[v] + e.s) {
                dist[e.f] = dist[v] + e.s;
                PQ.push({dist[e.f], e.f});
            }
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> C >> K;
    ll v;
    FOR(i, N) {
        cin >> v;
        V.pb(v);
        adj.eb();
    }
    numNodes = N;
    int ci, c;
    FOR(i, N) {
        cin >> ci;
        FOR(j, ci) {
            cin >> c;
            Classes[c].pb(i);
        }
    }
    for (pair<int, vector<int>> p : Classes) {
        sort(all(p.s), valCmp);
        connect(p.s, 0, sz(p.s) - 1);
    }
    dijkstraSP(0);
    FOR(i, N) cout << (dist[i] == LL_INF ? -1 : dist[i] / 2) << nl;
    return 0;
}
