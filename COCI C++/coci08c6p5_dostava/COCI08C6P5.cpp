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

#define MAXR 2010
#define MAXC 210

int R, C, D, grid[MAXR][MAXC], dist[MAXR * 2][MAXR * 2];
bool marked[MAXR * 2];
vector<pii> adj[MAXR * 2];

void spfa() {
    For(s, 2, (R + 1) * 2) {
        deque<int> q;
        q.clear();
        For(v, 2, (R + 1) * 2) {
            dist[s][v] = INT_INF;
            marked[v] = false;
        }
        dist[s][s] = 0;
        marked[s] = true;
        q.push_back(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            marked[v] = false;
            for (pii &e : adj[v]) {
                if (dist[s][e.first] > dist[s][v] + e.second) {
                    dist[s][e.first] = dist[s][v] + e.second;
                    if (!marked[e.first]) {
                        if (!q.empty() && dist[s][e.first] <= dist[s][q.front()]) q.push_front(e.first);
                        else q.push_back(e.first);
                        marked[e.first] = true;
                    }
                }
            }
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> R >> C;
    For(i, 1, R + 1) {
        grid[i][0] = 0;
        For(j, 1, C + 1) {
            cin >> grid[i][j];
            grid[i][j] = grid[i][j - 1] + grid[i][j];
        }
        if (i > 1) {
            adj[2 * i].pb({2 * (i - 1), grid[i - 1][1]});
            adj[2 * i + 1].pb({2 * (i - 1) + 1, grid[i - 1][C] - grid[i - 1][C - 1]});
            adj[2 * (i - 1)].pb({2 * i, grid[i][1]});
            adj[2 * (i - 1) + 1].pb({2 * i + 1, grid[i][C] - grid[i][C - 1]});
        }
        adj[2 * i].pb({2 * i + 1, grid[i][C] - grid[i][1]});
        adj[2 * i + 1].pb({2 * i, grid[i][C - 1]});
    }
    spfa();
    cin >> D;
    pii cur = {1, 1};
    int r, c;
    ll ans = grid[1][1];
    FOR(i, D) {
        cin >> r >> c;
        ll d0 = LL_INF;
        if (r == cur.f) {
            if (c > cur.s) d0 = grid[r][c] - grid[r][cur.s];
            else if (c < cur.s) d0 = grid[r][cur.s - 1] - grid[r][c - 1];
        }
        ll d1 = grid[cur.f][cur.s - 1] + dist[cur.f * 2][r * 2] + grid[r][c] - grid[r][1];
        ll d2 = grid[cur.f][cur.s - 1] + dist[cur.f * 2][r * 2 + 1] + grid[r][C - 1] - grid[r][c - 1];
        ll d3 = grid[cur.f][C] - grid[cur.f][cur.s] + dist[cur.f * 2 + 1][r * 2] + grid[r][c] - grid[r][1];
        ll d4 = grid[cur.f][C] - grid[cur.f][cur.s] + dist[cur.f * 2 + 1][r * 2 + 1] + grid[r][C - 1] - grid[r][c - 1];
        ans += min(d0, min(min(d1, d2), min(d3, d4)));
        cur = {r, c};
    }
    cout << ans << nl;
    return 0;
}
