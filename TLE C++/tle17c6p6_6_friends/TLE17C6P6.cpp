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

#define MAXNMQ 3005

int N, M, Q, checkSz;
ll A[MAXNMQ];
bool check[MAXNMQ];
pill upd[MAXNMQ];

int query(int l, int r, ll x) {
    checkSz = 0;
    For(i, l, r + 1) checkSz += (check[i] = A[i] % x != 0);
    if (checkSz == 0) return 0;
    For(i, 1, M + 1) {
        if (upd[i].f < l || upd[i].f > r) continue;
        if (upd[i].s % x == 0) {
            if (check[upd[i].f]) {
                checkSz--;
                check[upd[i].f] = false;
            }
        } else {
            if (!check[upd[i].f]) {
                checkSz++;
                check[upd[i].f] = true;
            }
        }
        if (checkSz == 0) return i;
    }
    return -1;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> Q;
    For(i, 1, N + 1) cin >> A[i];
    For(i, 1, M + 1) cin >> upd[i].f >> upd[i].s;
    int l, r;
    ll x;
    FOR(i, Q) {
        cin >> l >> r >> x;
        cout << query(l, r, x) << nl;
    }
    return 0;
}
