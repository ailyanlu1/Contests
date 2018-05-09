// http://codeforces.com/contest/980/problem/E
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

#define MAXN 1000005
#define MAXLGN 22

int N, K, LGN, par[MAXN][MAXLGN];
vector<int> adj[MAXN];
bool keep[MAXN];

void dfs(int v, int prev) {
    par[v][0] = prev;
    for (int w : adj[v]) if (w != prev) dfs(w, v);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    LGN = (int) (ceil(log2(N + 1)) + 1);
    keep[0] = 1;
    For(i, 1, N + 1) {
        keep[i] = 0;
        FOR(j, LGN) par[i][j] = 0;
    }
    int a, b;
    For(i, 1, N) {
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dfs(N, 0);
    For(j, 1, LGN) For(i, 1, N + 1) par[i][j] = par[par[i][j - 1]][j - 1];
    int rem = N - K;
    for (int i = N; rem > 0; i--) {
        if (keep[i]) continue;
        int cnt = 1;
        for (int k = i, j = LGN - 1; j >= 0; j--) {
            if (!keep[par[k][j]]) {
                cnt += 1 << j;
                k = par[k][j];
            }
        }
        if (cnt > rem) continue;
        rem -= cnt;
        for (int k = i; !keep[k]; k = par[k][0]) keep[k] = true;
    }
    For(i, 1, N + 1) if (!keep[i]) cout << i << sp;
    cout << nl;
    return 0;
}
