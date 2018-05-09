// http://codeforces.com/problemset/problem/570/D
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

#define MAXNM 500005

int N, M, size[MAXNM], depth[MAXNM], cnt[MAXNM];
bool parity[MAXNM][26], isHeavy[MAXNM], ans[MAXNM];
vector<int> adj[MAXNM];
vector<pii> queries[MAXNM];
string S;

void getSize(int v, int d) {
    size[v] = 1;
    depth[v] = d;
    for (int w : adj[v]) {
        getSize(w, d + 1);
        size[v] += size[w];
    }
}

void add(int v, int delta) {
    cnt[depth[v]] -= parity[depth[v]][S[v] - 'a'];
    parity[depth[v]][S[v] - 'a'] ^= 1;
    cnt[depth[v]] += parity[depth[v]][S[v] - 'a'];
    for (int w : adj[v]) if (!isHeavy[w]) add(w, delta);
}

void dfs(int v, bool keep = 0) {
    int maxSize = -1, heavyInd = -1;
    for (int w : adj[v]) {
        if (size[w] > maxSize) {
            maxSize = size[w];
            heavyInd = w;
        }
    }
    for (int w : adj[v]) if (w != heavyInd) dfs(w, 0);
    if (heavyInd != -1) {
        dfs(heavyInd, 1);
        isHeavy[heavyInd] = 1;
    }
    add(v, 1);
    for (pii q : queries[v]) ans[q.s] = cnt[q.f] <= 1;
    if (heavyInd != -1) isHeavy[heavyInd] = 0;
    if (!keep) add(v, -1);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    FOR(i, N) {
        cnt[i] = 0;
        isHeavy[i] = 0;
        FOR(j, 26) parity[i][j] = 0;
    }
    int p;
    For(i, 1, N) {
        cin >> p;
        adj[p - 1].pb(i);
    }
    cin >> S;
    int h, v;
    FOR(i, M) {
        cin >> v >> h;
        queries[v - 1].eb(h - 1, i);
    }
    getSize(0, 0);
    dfs(0);
    FOR(i, M) cout << (ans[i] ? "Yes" : "No") << nl;
    return 0;
}
