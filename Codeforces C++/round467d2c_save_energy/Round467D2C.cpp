// http://codeforces.com/contest/937/problem/C
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

#define EPS 1e-9

ll k, d, t;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> k >> d >> t;
    ll len = k / d * d;
    if (len < k) len += d;
    ll oncnt = k;
    ll offcnt = len - k;
    double cyc = oncnt / ((double) t) + offcnt / ((double) t * 2.0);
    ll cnt = (ll) floor(1.0 / cyc);
    double cur = cnt * cyc;
    double time = cnt * len;
    if (cur + oncnt / ((double) t) > 1.0) {
        cout << setprecision(9) << fixed << time + (1.0 - cur) * t << nl;
        return 0;
    }
    time += oncnt;
    cur += oncnt / ((double) t);
    cout << setprecision(9) << fixed << time + (1.0 - cur) * t * 2.0 << nl;
    return 0;
}
