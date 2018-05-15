// http://www.spoj.com/problems/SHPATH/
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

template<typename T1, typename T2, typename H1 = hash<T1>, typename H2 = hash<T2>>
struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * H1 {}(p.first) + H2 {}(p.second);}};

#define MAXN 10005

int N, R, dist[MAXN];
umap<string, int> ind;
vector<pii> adj[MAXN];

int dijkstra(int s, int t) {
    minpq<pii> PQ;
    FOR(i, N) dist[i] = INT_INF;
    dist[s] = 0;
    PQ.push({dist[s], s});
    while (!PQ.empty()) {
        int v = PQ.top().s;
        if (v == t) return dist[t];
        PQ.pop();
        for (pii e : adj[v]) {
            if (dist[e.f] > dist[v] + e.s) {
                dist[e.f] = dist[v] + e.s;
                PQ.push({dist[e.f], e.f});
            }
        }
    }
    return -1;
}

void solve() {
    cin >> N;
    ind.clear();
    FOR(i, N) adj[i].clear();
    string S, T;
    int p, v, d;
    FOR(i, N) {
        cin >> S;
        ind[S] = i;
        cin >> p;
        FOR(j, p) {
            cin >> v >> d;
            adj[i].pb({v - 1, d});
        }
    }
    cin >> R;
    FOR(i, R) {
        cin >> S >> T;
        cout << dijkstra(ind[S], ind[T]) << nl;
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    FOR(i, T) solve();
    return 0;
}
