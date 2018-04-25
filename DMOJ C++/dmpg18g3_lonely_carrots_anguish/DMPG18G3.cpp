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

int N, Q, SZ[MAXN], maxDep[MAXN];
bool heavy[MAXN];
vector<int> adj[MAXN], queries[MAXN];
vector<pii> q;
umap<pii, ll, pair_hash<int, int>> ans;

template <typename T>
struct FenwickTree {
private:
    int size;
    T *array;

public:
    FenwickTree(int size) {
        this->size = size;
        array = new T[size + 1];
        for (int i = 0; i <= size; i++) {
            array[i] = 0;
        }
    }

    T rsq(int ind) {
        T sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    T rsq(int a, int b) {
        return rsq(b) - rsq(a - 1);
    }

    void update(int ind, T value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    int getSize() {
        return size;
    }
};

FenwickTree<ll> *small, *large;

void preDfs(int v, int prev, int dep) {
    maxDep[v] = dep;
    SZ[v] = 1;
    for (int w : adj[v]) {
        if (w == prev) continue;
        preDfs(w, v, dep + 1);
        MAX(maxDep[v], maxDep[w]);
        SZ[v] += SZ[w];
    }
}

void addSmall(int v, int prev, int dep, int delta) {
    small->update(dep, delta);
    for (int w : adj[v]) if (w != prev && !heavy[w]) addSmall(w, v, dep + 1, delta);
}

void addLarge(int v, int prev, int dep, int delta) {
    large->update(dep, delta);
    for (int w : adj[v]) if (w != prev && !heavy[w]) addLarge(w, v, dep + 1, delta);
}

void dfs(int v, int prev, int dep, bool keep = 0) {
    vector<ll> tempAns(sz(queries[v]));
    int maxSZ = -1, heavyInd = -1;
    for (int w : adj[v]) {
        if (w != prev && SZ[w] > maxSZ) {
            maxSZ = SZ[w];
            heavyInd = w;
        }
    }
    for (int w : adj[v]) if (w != prev && w != heavyInd) dfs(w, v, dep + 1, 0);
    if (heavyInd != -1) {
        dfs(heavyInd, v, dep + 1, 1);
        heavy[heavyInd] = 1;
        FOR(i, sz(queries[v])) {
            int d = queries[v][i];
            tempAns[i] = large->rsq(dep, min(dep + d, N));
        }
    }
    for (int w : adj[v]) {
        if (w != prev && !heavy[w]) {
            addSmall(w, v, dep + 1, 1);
            FOR(i, sz(queries[v])) {
                int d = queries[v][i];
                tempAns[i] += (large->rsq(dep, min(dep + d, N)) + 1) * small->rsq(dep, min(dep + d, N));
            }
            addSmall(w, v, dep + 1, -1);
            addLarge(w, v, dep + 1, 1);
        }
    }
    FOR(i, sz(queries[v])) {
        int d = queries[v][i];
        ans[{v, d}] = tempAns[i] + 1;
    }
    large->update(dep, 1);
    if (heavyInd != -1) heavy[heavyInd] = 0;
    if (!keep) {
        large->update(dep, -1);
        for (int w : adj[v]) {
            if (w == prev || heavy[w]) continue;
            addLarge(w, v, dep + 1, -1);
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int a, b;
    FOR(i, N) heavy[i] = false;
    FOR(i, N - 1) {
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    cin >> Q;
    int n, d;
    FOR(i, Q) {
        cin >> n >> d;
        queries[--n].pb(d);
        q.pb({n, d});
    }
    FOR(i, N) {
        sort(all(queries[i]));
        queries[i].erase(unique(all(queries[i])), queries[i].end());
    }
    small = new FenwickTree<ll>(N);
    large = new FenwickTree<ll>(N);
    preDfs(0, -1, 1);
    dfs(0, -1, 1);
    for (pii p : q) cout << ans[{p.f, p.s}] << nl;
    return 0;
}
