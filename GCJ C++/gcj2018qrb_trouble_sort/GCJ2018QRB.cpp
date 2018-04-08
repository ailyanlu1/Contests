// https://codejam.withgoogle.com/2018/challenges/00000000000000cb/dashboard/00000000000079cb
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

int T, N, A[MAXN], B[MAXN];
vector<int> odd, even;
set<pair<pii, int>> s;

void solveSlow(int t) {
    bool done = false;
    while (!done) {
        done = true;
        FOR(i, N - 2) {
            if (A[i] > A[i + 2]) {
                done = false;
                swap(A[i], A[i + 2]);
            }
        }
    }
    FOR(i, N - 1) {
        if (A[i] > A[i + 1]) {
            cout << "Case #" << t << ": " << i << nl;
            return;
        }
    }
    cout << "Case #" << t << ": " << "OK" << nl;
}

void solveFast(int t) {
    s.clear();
    FOR(i, N) B[i] = A[i];
    sort(B, B + N);
    FOR(i, N) {
        s.insert({{B[i], i % 2}, i});
    }
    FOR(i, N) {
        auto it = s.lower_bound({{A[i], i % 2}, 0});
        if (it != s.end() && it->f.f == A[i] && it->f.s == i % 2) s.erase(it);
    }
    if (s.empty()) {
        cout << "Case #" << t << ": " << "OK" << nl;
    } else {
        pair<pii, int> ans = *(s.begin());
        cout << "Case #" << t << ": " << ans.s << nl;
    }
}

void solveFast2(int t) {
    odd.clear();
    even.clear();
    FOR(i, N) {
        if (i % 2) odd.pb(A[i]);
        else even.pb(A[i]);
    }
    sort(all(odd));
    sort(all(even));
    int i = 0, j = 0, last = 0, cur;
    FOR(k, N) {
        cur = k % 2 ? odd[i++] : even[j++];
        if (last > cur) {
            cout << "Case #" << t << ": " << k - 1 << nl;
            return;
        }
        last = cur;
    }
    cout << "Case #" << t << ": " << "OK" << nl;
}

void solve(int t) {
    cin >> N;
    FOR(i, N) cin >> A[i];
    if (N <= 105) solveSlow(t);
    else solveFast2(t);
}

mt19937 rng(time(0));

void gen(int t) {
    N = 100000;
    FOR(i, N) {
        A[i] = rng() % 10000;
        if (N <= 1005) cout << A[i] << sp;
    }
    if (N <= 1005) cout << nl;
    if (N <= 1005) solveSlow(t);
    solveFast2(t);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(i, T) solve(i + 1);
    return 0;
}
