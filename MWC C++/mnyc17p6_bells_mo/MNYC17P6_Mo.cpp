// 10/100 TLE
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
#define MAXQ 50005
#define MAXB 400

int N, Q, A[MAXN], ans[MAXQ];
bool isQuery[MAXQ];
pii queries[MAXQ];
vector<int> q[MAXB][MAXB];
umap<int, int> cnt;
stack<pii> revert;
int res;

inline void add(int a) {
    cnt[a]++;
    if (cnt[a] == 1) res++;
}

inline void remove(int a) {
    cnt[a]--;
    if (cnt[a] == 0) res--;
}

inline void update(int i, int a) {
    remove(A[i]);
    A[i] = a;
    add(A[i]);
}

void solve() {
    res = 0;
    int sz = (int) cbrt(N); sz *= sz;
    for (int i = 0; i < Q; i++) {
        if (isQuery[i]) q[queries[i].f / sz][queries[i].s / sz].pb(i);
        else {
            for (int bl = 0; bl <= queries[i].f / sz; bl++) {
                for (int br = queries[i].f / sz; br <= (N - 1) / sz; br++) {
                    q[bl][br].pb(i);
                }
            }
        }
    }
    int l = 0, r = l - 1;
    for (int bl = 0; bl <= (N - 1) / sz; bl++) {
        for (int br = bl; br <= (N - 1) / sz; br++) {
            for (int i : q[bl][br]) {
                if (isQuery[i]) {
                    while (l < queries[i].f) {
                        remove(A[l]);
                        l++;
                    }
                    while (l > queries[i].f) {
                        l--;
                        add(A[l]);
                    }
                    while (r < queries[i].s) {
                        r++;
                        add(A[r]);
                    }
                    while (r > queries[i].s) {
                        remove(A[r]);
                        r--;
                    }
                    ans[i] = res;
                } else {
                    revert.push({queries[i].f, A[queries[i].f]});
                    if (l <= queries[i].f && queries[i].f <= r) {
                        update(queries[i].f, queries[i].s);
                    } else {
                        A[queries[i].f] = queries[i].s;
                    }
                }
            }
            while (!revert.empty()) {
                pii x = revert.top();
                revert.pop();
                if (l <= x.f && x.f <= r) {
                    update(x.f, x.s);
                } else {
                    A[x.f] = x.s;
                }
            }
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    FOR(i, N) cin >> A[i];
    int t;
    FOR(i, Q) {
        cin >> t;
        isQuery[i] = t == 2;
        cin >> queries[i].f >> queries[i].s;
        queries[i].f--;
        if (t == 2) queries[i].s--;
        ans[i] = -1;
    }
    solve();
    FOR(i, Q) if (ans[i] != -1) cout << ans[i] << nl;
    return 0;
}
