// http://codeforces.com/problemsets/acmsguru/problem/99999/507
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

#define MAXN 50000

int N, M, V[MAXN], ans[MAXN];
vector<int> adj[MAXN];
set<int> S[MAXN];

void dfs(int v) {
    ans[v] = INT_MAX;
    if (v >= N - M) {
        S[v].insert(V[v]);
        return;
    }
    for (int w : adj[v]) {
        dfs(w);
        MIN(ans[v], ans[w]);
        if (sz(S[v]) < sz(S[w])) S[v].swap(S[w]);
        for (int val : S[w]) {
            auto it = S[v].lower_bound(val);
            if (it != S[v].end()) MIN(ans[v], *it - val);
            if (it != S[v].begin()) MIN(ans[v], val - *(prev(it)));
            S[v].insert(val);
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    int p;
    For(i, 1, N) {
        cin >> p;
        adj[p - 1].pb(i);
    }
    For(i, N - M, N) cin >> V[i];
    dfs(0);
    FOR(i, N - M) cout << ans[i] << " \n"[i == N - M];
    return 0;
}
