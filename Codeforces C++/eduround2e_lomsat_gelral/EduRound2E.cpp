// http://codeforces.com/contest/600/problem/E
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

#define MAXN 100005

int N, maxCnt, color[MAXN], cnt[MAXN], size[MAXN], cntValsCnt[MAXN];
ll ans[MAXN], cntSum[MAXN];
bool isHeavy[MAXN];
vector<int> adj[MAXN];

void getSize(int v, int prev) {
    size[v] = 1;
    for (int w : adj[v]) {
        if (w == prev) continue;
        getSize(w, v);
        size[v] += size[w];
    }
}

void add(int v, int prev, int delta) {
    cntSum[cnt[color[v]]] -= color[v];
    if (--cntValsCnt[cnt[color[v]]] == 0 && delta == -1 && maxCnt == cnt[color[v]]) maxCnt--;
    cnt[color[v]] += delta;
    cntSum[cnt[color[v]]] += color[v];
    if (++cntValsCnt[cnt[color[v]]] == 1 && delta == 1 && maxCnt == cnt[color[v]] - 1) maxCnt++;
    for (int w : adj[v]) if (w != prev && !isHeavy[w]) add(w, v, delta);
}

void dfs(int v, int prev, bool keep = 0) {
    int maxSize = -1, heavyInd = -1;
    for (int w : adj[v]) {
        if (w != prev && size[w] > maxSize) {
            maxSize = size[w];
            heavyInd = w;
        }
    }
    for (int w : adj[v]) if (w != prev && w != heavyInd) dfs(w, v, 0);
    if (heavyInd != -1) {
        dfs(heavyInd, v, 1);
        isHeavy[heavyInd] = 1;
    }
    add(v, prev, 1);
    ans[v] = cntSum[maxCnt];
    if (heavyInd != -1) isHeavy[heavyInd] = 0;
    if (!keep) add(v, prev, -1);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) {
        cin >> color[i];
        cnt[i] = 0;
        cntSum[0] += color[i];
        isHeavy[i] = 0;
    }
    maxCnt = 0;
    cntValsCnt[0] = N;
    int a, b;
    FOR(i, N - 1) {
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    getSize(0, -1);
    dfs(0, -1);
    FOR(i, N) cout << ans[i] << sp;
    cout << nl;
    return 0;
}
