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

#define MAXN 200005
#define MAXK 1000005

bool exclude[MAXN];
vector<pii> adj[MAXN];

int getSize(int v, int prev) {
    int size = 1;
    for (pii e : adj[v]) if (e.f != prev && !exclude[e.f]) size += getSize(e.f, v);
    return size;
}

int getCentroid(int v, int prev, int treeSize) {
    int n = treeSize;
    int size = 1;
    bool hasCentroid = true;
    for (pii e : adj[v]) {
        if (e.f == prev || exclude[e.f]) continue;
        int ret = getCentroid(e.f, v, treeSize);
        if (ret >= 0) return ret;
        hasCentroid &= -ret <= n / 2;
        size += -ret;
    }
    hasCentroid &= n - size <= n / 2;
    return hasCentroid ? v : -size;
}

int k, ans = INT_INF, m[MAXK];
vector<pii> toInsert;
vector<int> toErase;

void dfs(int v, int prev, int depth, int dist) {
    if (dist > k) return;
    if (m[k - dist] != -1) MIN(ans, depth + m[k - dist]);
    for (pii e : adj[v]) if (e.f != prev && !exclude[e.f]) dfs(e.f, v, depth + 1, dist + e.s);
    toInsert.pb({dist, depth});
}

int best_path(int N, int K, int H[][2], int L[]) {
    k = K;
    FOR(i, K + 1) m[i] = -1;
    FOR(i, N - 1) {
        adj[H[i][0]].pb({H[i][1], L[i]});
        adj[H[i][1]].pb({H[i][0], L[i]});
    }
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        int c = getCentroid(v, -1, getSize(v, -1));
        toErase.clear();
        m[0] = 0;
        toErase.pb(0);
        for (pii e : adj[c]) {
            if (exclude[e.f]) continue;
            toInsert.clear();
            dfs(e.f, c, 1, e.s);
            for (pii p : toInsert) {
                if (m[p.f] == -1) {
                    m[p.f] = p.s;
                    toErase.pb(p.f);
                } else {
                    MIN(m[p.f], p.s);
                }
            }
        }
        for (int dist : toErase) m[dist] = -1;
        exclude[c] = true;
        for (pii e : adj[c]) if (!exclude[e.f]) q.push(e.f);
    }
    return ans == INT_INF ? -1 : ans;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N, K;
    cin >> N >> K;
    int H[N - 1][2], L[N - 1];
    FOR(i, N - 1) cin >> H[i][0] >> H[i][1] >> L[i];
    cout << best_path(N, K, H, L) << nl;
    return 0;
}
