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

#define MAXN 22

int N, M, K, D, dist[MAXN], dp[1 << MAXN], MST[1 << MAXN];
bool vis[MAXN];
vector<pii> adj[MAXN];
vector<int> adj2[MAXN];

int mst(int ii) {
    MST[ii] = 0;
    FOR(i, N) {
        vis[i] = 0;
        dist[i] = INT_INF;
    }
    dist[31 - __builtin_clz(ii)] = 0;
    For(i, 1, D) {
        int minV = -1;
        FOR(j, N) if (ii & (1 << j) && !vis[j] && (minV == -1 || dist[j] < dist[minV])) minV = j;
        if (minV == -1) break;
        vis[minV] = 1;
        for (pii e : adj[minV]) if (ii & (1 << e.f) && !vis[e.f]) MIN(dist[e.f], e.s);
    }
    FOR(i, N) if (ii & (1 << i)) MST[ii] = min(MST[ii] + dist[i], INT_INF);
    return MST[ii];
}

int solve(int ii) {
    if (dp[ii] != -1) return dp[ii];
    int pc = __builtin_popcount(ii);
    if (pc == D) return dp[ii] = MST[ii];
    if (pc < D) return dp[ii] = INT_INF;
    dp[ii] = INT_INF;
    int msb = 31 - __builtin_clz(ii);
    for (int i : adj2[msb]) if ((ii & i) == i) MIN(dp[ii], MST[i] + solve(ii ^ i));
    return dp[ii];
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;
    int a, b, c;
    FOR(i, M) {
        cin >> a >> b >> c;
        a--; b--;
        adj[a].eb(b, c);
        adj[b].eb(a, c);
    }
    if (N % K != 0) {
        cout << -1 << nl;
        return 0;
    }
    D = N / K;
    For(i, (1 << D) - 1, 1 << N) if (__builtin_popcount(i) == D && mst(i) != INT_INF) adj2[31 - __builtin_clz(i)].pb(i);
    FOR(i, 1 << N) dp[i] = -1;
    cout << (solve((1 << N) - 1) == INT_INF ? -1 : solve((1 << N) - 1)) << nl;
    return 0;
}
