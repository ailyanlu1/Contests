// http://www.spoj.com/problems/GSS4/
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

int N, M, PAR[MAXN];
ll A[MAXN], BIT[MAXN];

void update(int i, ll v) {
    for (; i <= N; i += (i & -i)) BIT[i] += v;
}

ll query(int i) {
    ll ret = 0;
    for (; i > 0; i -= (i & -i)) ret += BIT[i];
    return ret;
}

ll query(int l, int r) {
    return query(r) - query(l - 1);
}

int find(int i) {
    while (i != PAR[i]) i = PAR[i] = PAR[PAR[i]];
    return i;
}

void modify(int l, int r) {
    for (int i = find(l); l <= i && i <= r; i = find(i + 1)) {
        if (A[i] != 1) {
            update(i, -A[i]);
            A[i] = (ll) sqrt(A[i]);
            update(i, A[i]);
            if (A[i] == 1) PAR[i] = i + 1;
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    while (cin >> N) {
        FOR(i, N + 1) {
            BIT[i] = 0;
            PAR[i] = i;
        }
        PAR[N + 1] = N + 1;
        cout << "Case #" << t++ << ":" << nl;
        For(i, 1, N + 1) {
            cin >> A[i];
            update(i, A[i]);
        }
        cin >> M;
        int t, l, r;
        FOR(i, M) {
            cin >> t >> l >> r;
            if (l > r) swap(l, r);
            if (t == 0) modify(l, r);
            else cout << query(l, r) << nl;
        }
        cout << nl;
    }
    return 0;
}
