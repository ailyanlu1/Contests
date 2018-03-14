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

#define MOD ((ll) (1e9 + 7))

int N, K;
vector<pii> arcs;

int cnt(vector<pii> &A) {
    int ret = 0;
    for (pii &a : A) for (pii &b : A) if (a < b && ((a.f < b.f && b.f < a.s) ^ (a.f < b.s && b.s < a.s))) ret++;
    return ret;
}

ll solve(vector<pii> &A, uset<int> &in) {
    ll ret = 0;
    for (int i = 0; i < (int) arcs.size(); i++) {
        pii &a = arcs[i];
        if (((int) A.size() == 0 || a > A.back()) && !in.count(a.f) && !in.count(a.s)) {
            A.pb(a);
            in.insert(a.f);
            in.insert(a.s);
            if (cnt(A) == K) ret = (ret + 1) % MOD;
            if ((int) in.size() < N / 2 * 2) ret = (ret + solve(A, in)) % MOD;
            A.pop_back();
            in.erase(a.f);
            in.erase(a.s);
        }
    }
    return ret;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    FOR(i, N) For(j, i + 1, N) arcs.pb({i, j});
    vector<pii> A;
    uset<int> in;
    cout << solve(A, in) << nl;
    return 0;
}
