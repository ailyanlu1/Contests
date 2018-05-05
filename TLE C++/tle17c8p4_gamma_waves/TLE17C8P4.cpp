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

int N, X, A[MAXN], B[MAXN];
map<int, deque<int>> m;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> X;
    FOR(i, N) cin >> A[i] >> B[i];
    int i = 0;
    ll ans = 0;
    FOR(j, N) {
        while (i < N && A[i] < B[j]) {
            m[A[i] % X].push_back(i);
            i++;
        }
        if (m.empty()) {
            assert(i < N);
            assert(A[i] == B[j]);
            m[A[i] % X].push_back(i);
            i++;
        }
        auto it = m.lower_bound(B[j] % X);
        if (it == m.end()) it = m.begin();
        assert(it != m.end());
        assert(sz(it->s) > 0);
        int diff = B[j] - A[it->s.front()];
        ans += diff / X - (diff % X == 0) + (diff == 0);
        it->s.pop_front();
        if (sz(it->s) == 0) m.erase(it);
    }
    cout << ans << nl;
    return 0;
}
