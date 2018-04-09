// http://codeforces.com/contest/959/problem/B
#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
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

#define MAXN 100005

int N, K, M;
ll cost[MAXN];
vector<int> adj[MAXN];
string W[MAXN];
umap<string, int> smap;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K >> M;
    FOR(i, N) {
        cin >> W[i];
        smap[W[i]] = i;
    }
    FOR(i, N) cin >> cost[i];
    int x, xi;
    FOR(i, K) {
        cin >> x;
        ll minCost = LL_INF;
        FOR(j, x) {
            cin >> xi;
            xi--;
            MIN(minCost, cost[xi]);
            adj[i].pb(xi);
        }
        for (int j : adj[i]) cost[j] = minCost;
    }
    string MM;
    ll ans = 0;
    FOR(i, M) {
        cin >> MM;
        ans += cost[smap[MM]];
    }
    cout << ans << nl;
    return 0;
}
