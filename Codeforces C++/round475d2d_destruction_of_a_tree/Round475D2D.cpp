// http://codeforces.com/contest/964/problem/D
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

int N, dep[MAXN], root;
uset<int> adj[MAXN];
vector<int> ord;
set<pii, greater<pii>> even;

void dfs(int v, int prev, int d) {
    dep[v] = d;
    for (int w : adj[v]) if (w != prev) dfs(w, v, d + 1);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int p;
    For(i, 1, N + 1) {
        cin >> p;
        if (p == 0) root = i;
        else {
            adj[p].insert(i);
            adj[i].insert(p);
        }
    }
    dfs(root, -1, 0);
    For(i, 1, N + 1) if (sz(adj[i]) % 2 == 0) even.insert({dep[i], i});
    int done = 0;
    while (!even.empty()) {
        int v = even.begin()->s;
        even.erase(even.begin());
        ord.push_back(v);
        done++;
        for (int w : adj[v]) {
            adj[w].erase(v);
            if (sz(adj[w]) % 2 == 0) even.insert({dep[w], w});
            else even.erase({dep[w], w});
        }
        adj[v].clear();
    }
    if (done == N) {
        cout << "YES" << nl;
        for (int v : ord) cout << v << nl;
    } else {
        cout << "NO" << nl;
    }
    return 0;
}
