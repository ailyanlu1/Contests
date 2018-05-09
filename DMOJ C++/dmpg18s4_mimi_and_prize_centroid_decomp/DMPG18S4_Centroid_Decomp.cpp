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

int N;
bool A[MAXN], exclude[MAXN];
vector<int> adj[MAXN];

int getSize(int v, int prev) {
    int size = 1;
    for (int w : adj[v]) if (w != prev && !exclude[w]) size += getSize(w, v);
    return size;
}

int getCentroid(int v, int prev, int treeSize) {
    int n = treeSize;
    int size = 1;
    bool hasCentroid = true;
    for (int w : adj[v]) {
        if (w == prev || exclude[w]) continue;
        int ret = getCentroid(w, v, treeSize);
        if (ret >= 0) return ret;
        hasCentroid &= -ret <= n / 2;
        size += -ret;
    }
    hasCentroid &= n - size <= n / 2;
    return hasCentroid ? v : -size;
}

int getCentroid(int v) {
    int c = getCentroid(v, -1, getSize(v, -1));
    exclude[c] = true;
    return c;
}

ll smallCnt[2][2] = {{0, 0}, {0, 0}}, largeCnt[2][2] = {{0, 0}, {0, 0}};

int dfs(int v, int prev, bool d, bool good, bool start) {
    if (A[v] != d) good = false;
    if (good) smallCnt[start][A[v]]++;
    int ret = good;
    for (int w : adj[v]) if (w != prev && !exclude[w]) ret += dfs(w, v, !d, good, start);
    return ret;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int a, b;
    FOR(i, N) {
        cin >> a;
        A[i] = a % 2;
        exclude[i] = false;
    }
    FOR(i, N - 1) {
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    queue<int> q;
    q.push(0);
    ll ans = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        int c = getCentroid(v, -1, getSize(v, -1));
        largeCnt[0][0] = largeCnt[0][1] = largeCnt[1][0] = largeCnt[1][1] = 0;
        for (int w : adj[c]) {
            if (exclude[w]) continue;
            smallCnt[0][0] = smallCnt[0][1] = smallCnt[1][0] = smallCnt[1][1] = 0;
            dfs(w, c, 1, 1, 1);
            dfs(w, c, 0, 1, 0);
            if (A[c]) {
                ans += smallCnt[0][0] + smallCnt[0][1];
                ans += smallCnt[0][1] * (largeCnt[0][0] + largeCnt[0][1] + 1);
                ans += largeCnt[0][1] * (smallCnt[0][0] + smallCnt[0][1]);
            } else {
                ans += smallCnt[1][1] * (largeCnt[1][0] + largeCnt[1][1] + 1);
                ans += largeCnt[1][1] * (smallCnt[1][0] + smallCnt[1][1]);
            }
            FOR(i, 2) FOR(j, 2) largeCnt[i][j] += smallCnt[i][j];
        }
        if (A[c]) ans++;
        exclude[c] = true;
        for (int w : adj[c]) if (!exclude[w]) q.push(w);
    }
    cout << ans << nl;
    return 0;
}
