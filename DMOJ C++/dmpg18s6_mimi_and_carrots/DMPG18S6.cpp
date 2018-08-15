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

int N, M, K, pre[MAXN], low[MAXN], cnt, SZ[MAXN * 2], par[MAXN * 2], ind[MAXN];
bool articulation[MAXN];
vector<int> adj[MAXN], adj2[MAXN * 2];
uset<int> inComponent[MAXN];
vector<uset<int>> components;
stack<pii> s;

void dfs(int v, int prev) {
    int children = 0;
    pre[v] = low[v] = cnt++;
    for (int w : adj[v]) {
        if (pre[w] == -1) {
            children++;
            s.push({v, w});
            dfs(w, v);
            low[v] = min(low[v], low[w]);
            if ((prev == v && children > 1) || (prev != v && low[w] >= pre[v])) {
                articulation[v] = true;
                components.eb();
                while (s.top().f != v || s.top().s != w) {
                    components.back().insert(s.top().f);
                    components.back().insert(s.top().s);
                    inComponent[s.top().f].insert(components.size() - 1);
                    inComponent[s.top().s].insert(components.size() - 1);
                    s.pop();
                }
                components.back().insert(s.top().f);
                components.back().insert(s.top().s);
                inComponent[s.top().f].insert(components.size() - 1);
                inComponent[s.top().s].insert(components.size() - 1);
                s.pop();
            }
        } else if (w != prev && pre[w] < low[v]) {
            low[v] = pre[w];
            s.push({v, w});
        }
    }
}

void biconnected() {
    cnt = 0;
    FOR(v, N) {
        low[v] = pre[v] = -1;
        articulation[v] = false;
    }
    FOR(v, N) {
        if (pre[v] == -1) dfs(v, v);
        if (!s.empty()) {
            components.eb();
            while (!s.empty()) {
                components.back().insert(s.top().f);
                components.back().insert(s.top().s);
                inComponent[s.top().f].insert(components.size() - 1);
                inComponent[s.top().s].insert(components.size() - 1);
                s.pop();
            }
        }
    }
}

void rebuild() {
    K = sz(components);
    FOR(i, N) {
        if (articulation[i]) {
            ind[i] = K;
            for (int c : inComponent[i]) {
                adj2[K].pb(c);
                adj2[c].pb(K);
            }
            K++;
        }
    }
}

void dfs2(int v, int prev) {
    par[v] = prev;
    SZ[v] = v < sz(components) ? sz(components[v]) - sz(adj2[v]) : 1;
    for (int w : adj2[v]) {
        if (w == prev) continue;
        dfs2(w, v);
        SZ[v] += SZ[w];
    }
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
    FOR(i, N) {
        if (articulation[i]) break;
        if (i == N - 1) {
            cout << -1 << sp << -1 << nl;
            return 0;
        }
    }
    rebuild();
    dfs2(0, -1);
    int R = INT_INF, B = -1;
    REV(i, N - 1) {
        if (articulation[i]) {
            int r = 1;
            for (int w : adj2[ind[i]]) {
                if (w == par[ind[i]]) MAX(r, SZ[0] - SZ[ind[i]]);
                else MAX(r, SZ[w]);
            }
            if (r < R) {
                R = r;
                B = i;
            }
        }
    }
    cout << B + 1 << sp << R << nl;
    return 0;
}
