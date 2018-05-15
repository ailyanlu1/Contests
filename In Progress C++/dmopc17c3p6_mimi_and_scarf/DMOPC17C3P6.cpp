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

#define MAXN 200005

int N, K, ans, C[MAXN], ALL[MAXN], maxKey[MAXN], maxKey2[MAXN];
bool exclude[MAXN];
vector<int> adj[MAXN];
umap<int, pii> large[MAXN], large2[MAXN];
umap<int, int> small;
uset<int> adjColors;

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

int dfs(int v, int prev, int even, int odd, bool hasEven, bool hasOdd, int len, int run, int startRun, bool hasStartRun) {
    if (len % 2 == 0) {
        if (hasEven && C[v] == even) run++;
        else {
            hasEven = true;
            even = C[v];
            run = hasOdd ? 2 : 1;
        }
    } else {
        if (hasOdd && C[v] == odd) run++;
        else {
            hasOdd = true;
            odd = C[v];
            run = hasEven ? 2 : 1;
        }
    }
    if (run >= K) return len - 1;
    if (!hasStartRun && startRun < run) startRun = run;
    else hasStartRun = true;
    MAX(small[startRun], len);
    int ret = len;
    for (int w : adj[v]) {
        if (w == prev || exclude[w]) continue;
        MAX(ret, dfs(w, v, even, odd, hasEven, hasOdd, len + 1, run, startRun, hasStartRun));
    }
    return ret;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    ans = 1;
    FOR(i, N) {
        cin >> C[i];
        C[i]--;
    }
    int a, b;
    FOR(i, N - 1) {
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        int c = getCentroid(v, -1, getSize(v, -1));
        q.pop();
        for (int w : adj[c]) {
            if (exclude[w]) continue;
            large[C[w]].clear();
            large2[C[w]].clear();
            ALL[C[w]] = 0;
            maxKey[C[w]] = maxKey2[C[w]] = 0;
            large[C[w]][0] = large2[C[w]][0] = {0, -1};
        }
        adjColors.clear();
        for (int w : adj[c]) {
            if (exclude[w]) continue;
            small.clear();
            small[1] = 1;
            MAX(ALL[C[w]], dfs(w, c, -1, C[c], false, true, 2, 1, 1, false));
            MAX(ans, ALL[C[w]]);
            adjColors.insert(C[w]);
            for (pii T : small) {
                if (!large[C[w]].count(T.f - 1) || T.s - 1 >= large[C[w]][T.f - 1].f) {
                    if (large[C[w]].count(T.f - 1)) {
                        large2[C[w]][T.f - 1] = mp(large[C[w]][T.f - 1].f, large[C[w]][T.f - 1].s);
                        MAX(maxKey2[C[w]], T.f - 1);
                    }
                    large[C[w]][T.f - 1] = mp(T.s - 1, w);
                    MAX(maxKey[C[w]], T.f - 1);
                } else if (!large2[C[w]].count(T.f - 1) || T.s - 1 > large2[C[w]][T.f - 1].f) {
                    large2[C[w]][T.f - 1] = mp(T.s - 1, w);
                    MAX(maxKey2[C[w]], T.f - 1);
                }
            }
        }
        for (int w : adj[c]) {
            if (exclude[w]) continue;
            small.clear();
            small[1] = 1;
            MAX(ALL[C[w]], dfs(w, c, -1, C[c], false, true, 2, 1, 1, false));
            MAX(ans, ALL[C[w]]);
            for (pii T : small) {
                if (large[C[w]][min(maxKey[C[w]], K - T.f - 1)].s == w) {
                    assert(large2[C[w]][min(maxKey2[C[w]], K - T.f - 1)].s != w);
                    MAX(ans, T.s + (large2[C[w]][min(maxKey2[C[w]], K - T.f - 1)].f));
                } else {
                    MAX(ans, T.s + (large[C[w]][min(maxKey[C[w]], K - T.f - 1)].f));
                }
            }
        }
        int best1 = 1, best2 = 1;
        for (int cc : adjColors) {
            if (ALL[cc] >= best1) {
                best2 = best1;
                best1 = ALL[cc];
            } else if (ALL[cc] > best2) {
                best2 = ALL[cc];
            }
        }
        MAX(ans, best1 + best2 - 1);
        exclude[c] = true;
        for (int w : adj[c]) if (!exclude[w]) q.push(w);
    }
    cout << ans << nl;
    return 0;
}
