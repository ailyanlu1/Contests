// https://codejam.withgoogle.com/2018/challenges/0000000000007883/dashboard
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

int T, R, C, H, V, rowCnt[105], colCnt[105], tot, cnt[105][105];
pii part[105][105];
char grid[105][105];

bool check() {
    if (tot == 0) return true;
    if (tot % ((V + 1) * (H + 1)) != 0) return false;
    int tar = tot / ((V + 1) * (H + 1));
    int tarRow = tot / (H + 1);
    int tarCol = tot / (V + 1);
    vector<int> hcuts, vcuts;
    int cur = 0;
    int start = 0;
    FOR(i, R) {
        cur += rowCnt[i];
        if (cur == tarRow) {
            cur = 0;
            start = i + 1;
            hcuts.pb(i + 1);
        } else if (cur > tarRow) return false;
    }
    if (start != R) {
        if (cur == 0) hcuts.back() = R;
        else return false;
    }
    assert(sz(hcuts) == H + 1);
    cur = 0;
    start = 0;
    FOR(j, C) {
        cur += colCnt[j];
        if (cur == tarCol) {
            cur = 0;
            start = j + 1;
            vcuts.pb(j + 1);
        } else if (cur > tarCol) return false;
    }
    if (start != C) {
        if (cur == 0) vcuts.back() = C;
        else return false;
    }
    assert(sz(vcuts) == V + 1);
    int k = 0;
    FOR(i, R) {
        FOR(j, C) part[i][j].f = k;
        if (hcuts[k] <= i + 1) k++;
    }
    assert(k == H + 1);
    k = 0;
    FOR(j, C) {
        FOR(i, R) part[i][j].s = k;
        if (vcuts[k] <= j + 1) k++;
    }
    assert(k == V + 1);
    FOR(i, H + 1) FOR(j, V + 1) cnt[i][j] = 0;
    FOR(i, R) FOR(j, C) cnt[part[i][j].f][part[i][j].s] += grid[i][j] == '@';
    FOR(i, H + 1) FOR(j, V + 1) if (cnt[i][j] != tar) return false;
    return true;
}

void solve(int t) {
    cin >> R >> C >> H >> V;
    FOR(i, R) rowCnt[i] = 0;
    FOR(j, C) colCnt[j] = 0;
    tot = 0;
    string s;
    FOR(i, R) {
        cin >> s;
        FOR(j, C) grid[i][j] = s[j];
        FOR(j, C) {
            if (grid[i][j] == '@') {
                rowCnt[i]++;
                colCnt[j]++;
                tot++;
            }
        }
    }
    cout << "Case #" << t << ": ";
    if (check()) cout << "POSSIBLE" << nl;
    else cout << "IMPOSSIBLE" << nl;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(i, T) solve(i + 1);
    return 0;
}
