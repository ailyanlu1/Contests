// https://codejam.withgoogle.com/2018/challenges/0000000000007765/dashboard/000000000003e0a8
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
#define MAXANS 150

int T, N;
ll W[MAXN], best[MAXANS];

void solve (int t) {
    cin >> N;
    FOR(i, N) cin >> W[i];
    best[0] = 0;
    For(i, 1, MAXANS) best[i] = LL_INF;
    int ind = 0;
    FOR(i, N) {
        Rev(j, ind + 2, 0) {
            if (best[j - 1] <= W[i] * 6 && best[j - 1] + W[i] < best[j]) best[j] = best[j - 1] + W[i];
            if (best[j] < LL_INF && j > ind) ind = j;
        }
    }
    int ans = 0;
    while (best[ans + 1] < LL_INF) ans++;
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
