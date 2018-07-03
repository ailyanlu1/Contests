// http://codeforces.com/contest/620/problem/E
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

#define MAXN 400005

int N, H, M, cur, pre[MAXN], post[MAXN], vert[MAXN], color[MAXN];
ll T[MAXN * 2], L[MAXN];
vector<int> adj[MAXN];

static void apply(int i, ll v) {
    T[i] = v;
    if (i < N) L[i] = v;
}

void pushup(int i) {
    while (i > 1) {
        i >>= 1;
        T[i] = L[i] == 0 ? T[i << 1] | T[i << 1 | 1] : L[i];
    }
}

void propagate(int i) {
    for (int h = H; h > 0; h--) {
        int ii = i >> h;
        if (L[ii] != 0) {
            apply(ii << 1, L[ii]);
            apply(ii << 1 | 1, L[ii]);
            L[ii] = 0;
        }
    }
}

void build() {
    H = 0;
    for (int i = 1; i <= N; H++) i <<= 1;
    for (int i = 0; i < N; i++) {
        T[N + i] = 1LL << color[vert[i + 1]];
        L[i] = 0;
    }
    for (int i = N - 1; i > 0; i--) T[i] = T[i << 1] | T[i << 1 | 1];
}

void update(int l, int r, ll v) {
    l += N - 1;
    r += N - 1;
    propagate(l);
    propagate(r);
    int l0 = l, r0 = r;
    for (; l <= r; l >>= 1, r >>= 1) {
        if ((l & 1) == 1) apply(l++, v);
        if ((r & 1) == 0) apply(r--, v);
    }
    pushup(l0);
    pushup(r0);
}

ll query(int l, int r) {
    l += (N - 1);
    r += (N - 1);
    propagate(l);
    propagate(r);
    ll q = 0;
    for (; l <= r; l >>= 1, r >>= 1) {
        if ((l & 1) == 1) q |= T[l++];
        if ((r & 1) == 0) q |= T[r--];
    }
    return q;
}

void dfs(int v, int prev) {
    pre[v] = ++cur;
    vert[cur] = v;
    for (int w : adj[v]) if (w != prev) dfs(w, v);
    post[v] = cur;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    FOR(i, N) {
        cin >> color[i];
        color[i]--;
    }
    int t, a, b;
    FOR(i, N - 1) {
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    cur = 0;
    dfs(0, -1);
    build();
    FOR(i, M) {
        cin >> t;
        if (t == 1) {
            cin >> a >> b;
            a--; b--;
            update(pre[a], post[a], 1LL << b);
        } else {
            cin >> a;
            a--;
            cout << __builtin_popcountll(query(pre[a], post[a])) << nl;
        }
    }
    return 0;
}
