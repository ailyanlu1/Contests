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

int N, M, K, pre[MAXN], low[MAXN], cnt, SZ[MAXN * 2], R = INT_INF, B = -1;
vector<int> adj[MAXN];

void dfs(int v, int prev) {
    int children = 0;
    pre[v] = low[v] = cnt++;
    int maxR = 1, sumR = 0;
    SZ[v] = 1;
    bool isArticulation = false;
    for (int w : adj[v]) {
        if (pre[w] == -1) {
            children++;
            dfs(w, v);
            SZ[v] += SZ[w];
            low[v] = min(low[v], low[w]);
            if ((prev == v && children > 1) || (prev != v && low[w] >= pre[v])) {
                isArticulation = true;
                MAX(maxR, SZ[w]);
                sumR += SZ[w];
            }
        } else if (w != prev && pre[w] < low[v]) {
            low[v] = pre[w];
        }
    }
    if (isArticulation) {
        MAX(maxR, N - sumR - 1);
        if (maxR < R) {
            R = maxR;
            B = v;
        } else if (maxR == R) {
            MAX(B, v);
        }
    }
}

void biconnected() {
    cnt = 0;
    FOR(v, N) low[v] = pre[v] = -1;
    FOR(v, N) if (pre[v] == -1) dfs(v, v);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    int a, b;
    FOR(i, M) {
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    biconnected();
    if (R == INT_INF) cout << -1 << sp << -1 << nl;
    else cout << B + 1 << sp << R << nl;
    return 0;
}
