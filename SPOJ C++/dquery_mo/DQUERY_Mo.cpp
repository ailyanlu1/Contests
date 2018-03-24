// http://www.spoj.com/problems/DQUERY/
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

#define MAXN 30005
#define MAXQ 200005
#define MAXA 1000005

struct Query {
    int l, r, ind, block;

    bool operator < (const Query &q) const {
        if (block != q.block) return block < q.block;
        return r < q.r;
    }
} q[MAXQ];

int N, Q, A[MAXN], cnt[MAXA], res, ans[MAXQ];

inline void add(int a) {
    cnt[a]++;
    if (cnt[a] == 1) res++;
}

inline void remove(int a) {
    cnt[a]--;
    if (cnt[a] == 0) res--;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    FOR(i, MAXA) cnt[i] = 0;
    cin >> N;
    For(i, 1, N + 1) cin >> A[i];
    cin >> Q;
    int sz = sqrt(Q) * 2;
    for (int i = 0; i < Q; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].ind = i;
        q[i].block = q[i].l / sz;
    }
    sort(q, q + Q);
    int l = q[0].l;
    int r = l - 1;
    res = 0;
    for (int i = 0; i < Q; i++) {
        while (l < q[i].l) {
            remove(A[l]);
            l++;
        }
        while (l > q[i].l) {
            l--;
            add(A[l]);
        }
        while (r < q[i].r) {
            r++;
            add(A[r]);
        }
        while (r > q[i].r) {
            remove(A[r]);
            r--;
        }
        ans[q[i].ind] = res;
    }
    FOR(i, Q) cout << ans[i] << nl;
    return 0;
}
