// https://codejam.withgoogle.com/2018/challenges/0000000000007764/dashboard/000000000003675c
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

#define MAXM 105

int T, M;
ll G[MAXM], G2[MAXM];
vector<int> adj[MAXM];

bool dfs(int v) {
    if (adj[v].empty()) return false;
    for (int w : adj[v]) {
        if (G2[w] < 0) return false;
        else {
            G2[w] += G2[v];
            if (G2[w] < 0 && !dfs(w)) return false;
        }
    }
    G2[v] = 0;
    return true;
}

void solve(int t) {
    cin >> M;
    FOR(i, M) adj[i].clear();
    int r1, r2;
    FOR(i, M) {
        cin >> r1 >> r2;
        if ((r1 > 1) && (r2 > 1)) {
            adj[i].pb(r1 - 1);
            adj[i].pb(r2 - 1);
        }
    }
    FOR(i, M) cin >> G[i];
    ll lo = G[0], hi = LL_INF, mid;
    while (lo < hi) {
        mid = lo + (hi - lo + 1) / 2;
        for (int i = 0; i < M; i++) G2[i] = G[i];
        G2[0] = G[0] - mid;
        if (dfs(0)) lo = mid;
        else hi = mid - 1;
    }
    cout << "Case #" << t << ": " << lo << nl;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(i, T) solve(i + 1);
    return 0;
}
