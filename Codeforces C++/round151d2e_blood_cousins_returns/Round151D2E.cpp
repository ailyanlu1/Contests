// http://codeforces.com/contest/246/problem/E
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

int N, M, nodeCnt, size[MAXNM], dep[MAXNM], val[MAXNM], ans[MAXNM];
umap<int, int> cnt[MAXNM];
bool isHeavy[MAXNM];
vector<int> adj[MAXNM];
vector<pii> queries[MAXNM];

struct Node {
    Node *child[26] = {nullptr};
    int id = -1;
} *root;

int contains(Node *root, string s) {
    Node *cur = root;
    for (char c : s) {
        if (cur->child[c - 'a'] != nullptr) cur = cur->child[c - 'a'];
        else return -1;
    }
    return cur->id;
}

void insert(Node *root, string s, int id) {
    Node *cur = root;
    for (char c : s) {
        if (cur->child[c - 'a'] != nullptr) cur = cur->child[c - 'a'];
        else cur = cur->child[c - 'a'] = new Node();
    }
    cur->id = id;
}

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
    if (delta > 0) cnt[dep[v]][val[v]]++;
    else if (--cnt[dep[v]][val[v]] == 0) cnt[dep[v]].erase(val[v]);
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
    for (pii q : queries[v]) ans[q.s] = dep[v] + q.f >= N ? 0 : sz(cnt[dep[v] + q.f]);
    if (heavyInd != -1) isHeavy[heavyInd] = false;
    if (!keep) add(v, prev, -1);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    N++;
    root = new Node();
    nodeCnt = 0;
    FOR(i, N) isHeavy[i] = false;
    val[0] = -1;
    string s;
    int v, p;
    For(i, 1, N) {
        cin >> s >> p;
        int id = contains(root, s);
        if (id == -1) {
            insert(root, s, nodeCnt);
            id = nodeCnt++;
        }
        val[i] = id;
        adj[p].pb(i);
    }
    getSize(0, -1, 0);
    cin >> M;
    FOR(i, M) {
        cin >> v >> p;
        queries[v].pb({p, i});
    }
    dfs(0, -1, false);
    FOR(i, M) cout << ans[i] << nl;
    return 0;
}
