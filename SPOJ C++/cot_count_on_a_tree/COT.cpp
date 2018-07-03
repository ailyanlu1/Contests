// http://www.spoj.com/problems/COT/
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
#define MAXLGN 20

int N, M, LGN, A[MAXN], oriVal[MAXN], L[20 * MAXN], R[20 * MAXN], VAL[20 * MAXN], nodes[MAXN], rmq[MAXLGN][MAXN * 2], dep[MAXN], head[MAXN], par[MAXN], ind = 0, curNode = 0;
pii B[MAXN];
vector<int> adj[MAXN];

int build(int cL, int cR) {
    if (cL == cR) {
        VAL[++curNode] = 0;
        return curNode;
    }
    int m = cL + (cR - cL) / 2;
    int k = ++curNode;
    L[k] = build(cL, m);
    R[k] = build(m + 1, cR);
    VAL[k] = VAL[L[k]] + VAL[R[k]];
    return k;
}

int update(int cur, int cL, int cR, int ind, int val) {
    if (cL > ind || cR < ind) return cur;
    if (cL == cR) {
        VAL[++curNode] = VAL[cur] + val;
        return curNode;
    }
    int m = cL + (cR - cL) / 2;
    int k = ++curNode;
    L[k] = update(L[cur], cL, m, ind, val);
    R[k] = update(R[cur], m + 1, cR, ind, val);
    VAL[k] = VAL[L[k]] + VAL[R[k]];
    return k;
}

int query(int curA, int curB, int curLCA, int curParLCA, int cL, int cR, int k) {
    if (cL == cR) return cL;
    int m = cL + (cR - cL) / 2;
    int x = VAL[L[curA]] + VAL[L[curB]] - VAL[L[curLCA]] - VAL[L[curParLCA]];
    if (k <= x) return query(L[curA], L[curB], L[curLCA], L[curParLCA], cL, m, k);
    else return query(R[curA], R[curB], R[curLCA], R[curParLCA], m + 1, cR, k - x);
}

void dfs(int v, int prev, int d) {
    dep[v] = d;
    par[v] = prev;
    nodes[v] = update(nodes[prev], 1, N, A[v], 1);
    head[v] = ind;
    rmq[0][ind++] = v;
    for (int w : adj[v]) {
        if (w == prev) continue;
        dfs(w, v, d + 1);
        rmq[0][ind++] = v;
    }
}

inline int minDepth(int v, int w) {
    return dep[v] < dep[w] ? v : w;
}

inline int RMQ(int l, int r) {
    int i = 31 - __builtin_clz(r - l + 1);
    return minDepth(rmq[i][l], rmq[i][r - (1 << i) + 1]);
}

inline int lca(int v, int w) {
    return head[v] < head[w] ? RMQ(head[v], head[w]) : RMQ(head[w], head[v]);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    LGN = 32 - __builtin_clz(N * 2 - 1);
    For(i, 1, N + 1) {
        cin >> A[i];
        B[i] = {A[i], i};
        head[i] = -1;
    }
    sort(B + 1, B + N + 1);
    For(i, 1, N + 1) {
        A[B[i].s] = i;
        oriVal[i] = B[i].f;
    }
    int a, b, k, LCA;
    FOR(i, N - 1) {
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    nodes[0] = build(1, N);
    dfs(1, 0, 0);
    FOR(i, LGN - 1) FOR(j, ind) rmq[i + 1][j] = minDepth(rmq[i][j], rmq[i][min(j + (1 << i), ind - 1)]);
    FOR(i, M) {
        cin >> a >> b >> k;
        LCA = lca(a, b);
        cout << oriVal[query(nodes[a], nodes[b], nodes[LCA], nodes[par[LCA]], 1, N, k)] << nl;
    }
    return 0;
}
