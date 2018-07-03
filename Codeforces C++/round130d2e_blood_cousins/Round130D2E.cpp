// http://codeforces.com/contest/208/problem/E
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

#define MAXNM 100005
#define MAXLGN 18

int N, LGN, M, size[MAXNM], dep[MAXNM], cnt[MAXNM], ans[MAXNM], par[MAXNM][MAXLGN];
bool isHeavy[MAXNM];
vector<int> adj[MAXNM];
vector<pii> queries[MAXNM];

void getSize(int v, int prev, int d) {
    size[v] = 1;
    dep[v] = d;
    for (int w : adj[v]) {
        if (w == prev) continue;
        getSize(w, v, d + 1);
        size[v] += size[w];
    }
}

void add(int v, int prev, int delta) {
    cnt[dep[v]] += delta;
    for (int w : adj[v]) if (w != prev && !isHeavy[w]) add(w, v, delta);
}

void dfs(int v, int prev, bool keep = false) {
    int maxSize = -1, heavyInd = -1;
    for (int w : adj[v]) {
        if (w != prev && size[w] > maxSize) {
            maxSize = size[w];
            heavyInd = w;
        }
    }
    for (int w : adj[v]) if (w != prev && w != heavyInd) dfs(w, v, false);
    if (heavyInd != -1) {
        dfs(heavyInd, v, true);
        isHeavy[heavyInd] = true;
    }
    add(v, prev, 1);
    for (pii q : queries[v]) ans[q.s] = dep[v] + q.f >= N ? 0 : max(cnt[dep[v] + q.f] - 1, 0);
    if (heavyInd != -1) isHeavy[heavyInd] = false;
    if (!keep) add(v, prev, -1);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    N++;
    LGN = (int) (ceil(log2(N)) + 1);
    FOR(i, N) {
        isHeavy[i] = false;
        cnt[i] = 0;
    }
    par[0][0] = -1;
    For(i, 1, N) {
        cin >> par[i][0];
        adj[par[i][0]].pb(i);
    }
    getSize(0, -1, 0);
    For(j, 1, LGN) FOR(i, N) if (par[i][j - 1] != -1) par[i][j] = par[par[i][j - 1]][j - 1];
    cin >> M;
    int v, p;
    FOR(i, M) {
        cin >> v >> p;
        if (dep[v] <= p) {
            ans[i] = 0;
        } else {
            int target = dep[v] - p;
            REV(j, LGN - 1) if (par[v][j] != -1 && dep[par[v][j]] >= target) v = par[v][j];
            queries[v].pb({p, i});
        }
    }
    dfs(0, -1, false);
    FOR(i, M) cout << ans[i] << sp;
    cout << nl;
    return 0;
}
