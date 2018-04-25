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

#define MAXNQV 200010
#define BSZ 10000

int N, Q, A[MAXNQV], cnt[MAXNQV], ans[MAXNQV];
vector<int> factors[MAXNQV];
vector<int> lqs[MAXNQV / BSZ + 10], rqs[MAXNQV / BSZ + 10];

struct Query {
    int t, l, r, x, ind;
} q[MAXNQV];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    For(i, 1, MAXNQV) for (int j = i; j < MAXNQV; j += i) factors[j].pb(i);
    cin >> N >> Q;
    FOR(i, N) cin >> A[i];
    FOR(i, Q) {
        cin >> q[i].t;
        if (q[i].t == 1) {
            cin >> q[i].l >> q[i].r >> q[i].x;
            q[i].ind = i;
            q[i].l -= 2; q[i].r--;
            lqs[q[i].l / BSZ].pb(i);
            rqs[q[i].r / BSZ].pb(i);
        } else {
            cin >> q[i].l >> q[i].x;
            q[i].ind = i;
            q[i].l--;
            q[i].r = q[i].l;
            FOR(j, (N - 1) / BSZ + 1) {
                lqs[j].pb(i);
                rqs[j].pb(i);
            }
        }
    }
    FOR(i, MAXNQV) cnt[i] = 0;
    int r = -1;
    stack<pii> rev;
    FOR(br, (N - 1) / BSZ + 1) {
        for (int i : rqs[br]) {
            if (q[i].t == 1) {
                while (r < q[i].r) {
                    r++;
                    for (int x : factors[A[r]]) cnt[x]++;
                }
                while (r > q[i].r) {
                    for (int x : factors[A[r]]) cnt[x]--;
                    r--;
                }
                ans[q[i].ind] += cnt[q[i].x];
            } else {
                rev.push({q[i].l, A[q[i].l]});
                if (q[i].l <= r) {
                    for (int x : factors[A[q[i].l]]) cnt[x]--;
                    A[q[i].l] = q[i].x;
                    for (int x : factors[q[i].x]) cnt[x]++;
                } else {
                    A[q[i].l] = q[i].x;
                }
            }
        }
        while (!rev.empty()) {
            pii y = rev.top();
            rev.pop();
            if (y.f <= r) {
                for (int x : factors[A[y.f]]) cnt[x]--;
                A[y.f] = y.s;
                for (int x : factors[y.s]) cnt[x]++;
            } else {
                A[y.f] = y.s;
            }
        }
    }
    FOR(i, MAXNQV) cnt[i] = 0;
    int l = -1;
    FOR(bl, (N - 1) / BSZ + 1) {
        for (int i : lqs[bl]) {
            if (q[i].t == 1) {
                while (l < q[i].l) {
                    l++;
                    for (int x : factors[A[l]]) cnt[x]++;
                }
                while (l > q[i].l) {
                    for (int x : factors[A[l]]) cnt[x]--;
                    l--;
                }
                ans[q[i].ind] -= cnt[q[i].x];
            } else {
                rev.push({q[i].l, A[q[i].l]});
                if (q[i].l <= l) {
                    for (int x : factors[A[q[i].l]]) cnt[x]--;
                    A[q[i].l] = q[i].x;
                    for (int x : factors[q[i].x]) cnt[x]++;
                } else {
                    A[q[i].l] = q[i].x;
                }
            }
        }
        while (!rev.empty()) {
            pii y = rev.top();
            rev.pop();
            if (y.f <= l) {
                for (int x : factors[A[y.f]]) cnt[x]--;
                A[y.f] = y.s;
                for (int x : factors[y.s]) cnt[x]++;
            } else {
                A[y.f] = y.s;
            }
        }
    }
    FOR(i, Q) if (q[i].t == 1) cout << ans[i] << nl;
    return 0;
}
