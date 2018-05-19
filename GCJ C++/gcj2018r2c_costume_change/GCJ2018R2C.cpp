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

#define MAXN 105

int T, N, A[MAXN][MAXN];

class HopcroftKarpMaxMatchCompact {
private:
    int N;
    vector<vector<int>> adj;
    vector<bool> color;
    vector<int> mate;
    vector<int> dist;
    vector<int> typeA;
    int pathDist = INT_MAX;

    bool hasPath() {
        queue<int> q;
        for (int v : typeA) {
            if (mate[v] == -1) {
                dist[v] = 0;
                q.push(v);
            } else {
                dist[v] = INT_MAX;
            }
        }
        pathDist = INT_MAX;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : adj[v]) {
                if (mate[w] == -1) {
                    if (pathDist == INT_MAX) pathDist = dist[v] + 1;
                } else if (dist[mate[w]] == INT_MAX) {
                    dist[mate[w]] = dist[v] + 1;
                    if (pathDist == INT_MAX) q.push(mate[w]);
                }
            }
        }
        return pathDist != INT_MAX;
    }

    bool dfs(int v) {
        for (int w : adj[v]) {
            if (mate[w] == -1) {
                if (pathDist == dist[v] + 1) {
                    mate[w] = v;
                    mate[v] = w;
                    return true;
                }
            } else if (dist[mate[w]] == dist[v] + 1) {
                if (dfs(mate[w])) {
                    mate[w] = v;
                    mate[v] = w;
                    return true;
                }
            }
        }
        dist[v] = INT_MAX;
        return false;
    }

public:
    HopcroftKarpMaxMatchCompact(int N, vector<bool> &color) : N(N), adj(N), color(color), mate(N), dist(N) {
        fill(mate.begin(), mate.end(), -1);
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    int maxMatch() {
        int cardinality = 0;
        for (int v = 0; v < N; v++) if (color[v]) typeA.push_back(v);
        while (hasPath()) for (int v : typeA) if (mate[v] == -1 && dfs(v)) cardinality++;
        return cardinality;
    }

    int getMate(int v) {
        return mate[v];
    }
};

void solve(int t) {
    cin >> N;
    FOR(i, N) FOR(j, N) cin >> A[i][j];
    vector<bool> color;
    FOR(i, N) color.pb(true);
    FOR(j, N) color.pb(false);
    int ans = 0;
    For(k, -N, N + 1) {
        HopcroftKarpMaxMatchCompact mm(2 * N, color);
        FOR(i, N) FOR(j, N) if (A[i][j] == k) mm.addEdge(i, j + N);
        ans += mm.maxMatch();
    }
    cout << "Case #" << t << ": " << N * N - ans << nl;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(i, T) solve(i + 1);
    return 0;
}
