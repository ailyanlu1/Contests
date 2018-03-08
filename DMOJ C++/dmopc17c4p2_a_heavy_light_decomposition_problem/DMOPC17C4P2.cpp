#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl "\n"

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

#define MAXN 1005

int N, Q, V[MAXN], edgeTo[MAXN], sum, cnt;
vector<int> adj[MAXN], vv;
umap<int, int> freq;
pii ans;

void dfs(int v, int prev) {
    for (int w : adj[v]) {
        if (w == prev) continue;
        edgeTo[w] = v;
        dfs(w, v);
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    FOR(i, N) cin >> V[i];
    int a, b, c;
    FOR(i, N - 1) {
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    FOR(q, Q) {
        cin >> c >> a >> b;
        a--; b--;
        edgeTo[a] = -1;
        dfs(a, -1);
        if (c == 1) {
            sum = 0;
            cnt = 0;
            for (int v = b; v != -1; v = edgeTo[v]) {
                sum += V[v];
                cnt++;
            }
            cout << (int) round(sum / (double) cnt) << nl;
        } else if (c == 2) {
            vv.clear();
            for (int v = b; v != -1; v = edgeTo[v]) {
                vv.pb(V[v]);
            }
            sort(vv.begin(), vv.end());
            if (sz(vv) % 2 == 0) cout << (int) round((vv[(sz(vv) - 1) / 2] + vv[sz(vv) / 2]) / 2.0) << nl;
            else cout << vv[sz(vv) / 2] << nl;
        } else if (c == 3) {
            freq.clear();
            for (int v = b; v != -1; v = edgeTo[v]) {
                freq[V[v]]++;
            }
            ans = {-1, -1};
            for (pii x: freq) {
                MAX(ans, mp(x.s, -x.f));
            }
            cout << -ans.s << nl;
        } else {
            q--;
        }
    }
    return 0;
}
