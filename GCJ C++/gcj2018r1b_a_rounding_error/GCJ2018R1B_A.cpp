// https://codejam.withgoogle.com/2018/challenges/0000000000007764/dashboard
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

#define MAXNL 100005

int T, N, L, C[MAXNL];

void solve(int t) {
    cin >> N >> L;
    FOR(i, N) C[i] = 0;
    set<int> good;
    FOR(i, N + 1) if ((i * 1000 / N) % 10 >= 5) good.insert(i);
    int rem = N;
    minpq<pii> PQ;
    FOR(i, L) {
        cin >> C[i];
        rem -= C[i];
        if (!good.count(C[i])) {
            auto it = good.lower_bound(C[i]);
            if (it != good.end()) PQ.push({(*it) - C[i], i});
        }
    }
    For(i, L, N) {
        C[i] = 0;
        auto it = good.lower_bound(C[i]);
        if (it != good.end()) PQ.push({(*it) - C[i], i});
    }
    while (!PQ.empty()) {
        if (PQ.top().f > rem) break;
        int i = PQ.top().s;
        C[i] += PQ.top().f;
        rem -= PQ.top().f;
        PQ.pop();
        if (!good.count(C[i])) {
            auto it = good.lower_bound(C[i]);
            if (it != good.end()) PQ.push({(*it) - C[i], i});
        }
    }
    if (rem > 0) {
        FOR(i, N) {
            if (!good.count(C[i])) {
                C[i] += rem;
                rem = 0;
                break;
            }
        }
    }
    if (rem > 0) C[0] += rem;
    int ans = 0;
    FOR(i, N) ans += (C[i] * 1000 / N + 5) / 10;
    cout << "Case #" << t << ": " << ans << nl;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(i, T) solve(i + 1);
    return 0;
}
