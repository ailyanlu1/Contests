#include <bits/stdc++.h>
using namespace std;

#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(A, b) ((A) = min((A), (b)))
#define MAX(A, b) ((A) = max((A), (b)))
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define f first
#define s second
#define all(A) (A).begin(), (A).end()
#define For(i, A, b) for (auto i = (A); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, A, b) for (auto i = (A); i > (b); i--)
#define REV(i, A) Rev(i, A, -1)
#define sz(A) ((int) (A).size())
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

vector<int> who_wins(vector<int> A, vector<int> R, vector<int> U, vector<int> V) {
    int N = sz(A), M = sz(U);
    vector<int> W(N), rem(N), indeg(N);
    vector<bool> vis(N);
    vector<vector<int>> adj(N);
    fill(all(W), 1);
    fill(all(indeg), 0);
    fill(all(vis), false);
    FOR(i, M) {
        adj[V[i]].pb(U[i]);
        indeg[U[i]]++;
    }
    bool found;
    do {
        queue<int> q;
        FOR(i, N) {
            if (!W[i]) continue;
            vis[i] = false;
            rem[i] = A[i] ? 1 : indeg[i];
            if (R[i] && W[i]) q.push(i);
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : adj[v]) {
                if (--rem[w] == 0 && !vis[w] && W[w]) {
                    vis[w] = true;
                    if (!R[w]) q.push(w);
                }
            }
        }
        found = false;
        FOR(i, N) {
            if (!vis[i] && W[i]) {
                W[i] = 0;
                found = true;
            }
        }
    } while (found);
    return W;
}

int main() {
//    freopen("in.txt", "R", stdin);
//    freopen("out.txt", "W", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N, M;
    cin >> N >> M;
    vector<int> A(N), R(N), U(M), V(M);
    FOR(i, N) cin >> A[i];
    FOR(i, N) cin >> R[i];
    FOR(i, M) cin >> U[i] >> V[i];
    vector<int> W = who_wins(A, R, U, V);
    FOR(i, N) cout << W[i] << " \n"[i == N - 1];
    return 0;
}
