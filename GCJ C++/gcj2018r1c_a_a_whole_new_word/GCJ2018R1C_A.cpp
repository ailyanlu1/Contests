// https://codejam.withgoogle.com/2018/challenges/0000000000007765/dashboard
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

#define MAXN 2005
#define MAXL 12

int T, N, L;
vector<char> adj[MAXL];
umap<char, int> m[MAXL];
string S[MAXN];
uset<ll> hsh;

void solve(int t) {
    cin >> N >> L;
    hsh.clear();
    FOR(j, L) {
        adj[j].clear();
        m[j].clear();
    }
    FOR(i, N) {
        cin >> S[i];
        FOR(j, L) adj[j].pb(S[i][j]);
    }
    FOR(j, L) {
        sort(all(adj[j]));
        adj[j].erase(unique(all(adj[j])), adj[j].end());
        FOR(k, sz(adj[j])) m[j][adj[j][k]] = k;
    }
    FOR(i, N) {
        ll curhsh = 0;
        FOR(j, L) {
            curhsh *= sz(adj[j]);
            curhsh += m[j][S[i][j]];
        }
        hsh.insert(curhsh);
    }
    ll end = 1;
    FOR(j, L) end *= sz(adj[j]);
    ll ans = 0;
    while (hsh.count(ans)) ans++;
    cout << "Case #" << t << ": ";
    if (ans >= end) cout << "-" << nl;
    else {
        string ANS;
        REV(j, L - 1) {
            ANS.pb(adj[j][ans % sz(adj[j])]);
            ans /= sz(adj[j]);
        }
        reverse(all(ANS));
        cout << ANS << nl;
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(i, T) solve(i + 1);
    return 0;
}
