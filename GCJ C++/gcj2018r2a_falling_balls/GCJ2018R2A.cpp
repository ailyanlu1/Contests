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

#define MAXC 105

int T, C, B[2][MAXC];
char ans[MAXC][MAXC];

void solve(int t) {
    cin >> C;
    cout << "Case #" << t << ": ";
    FOR(i, C) cin >> B[1][i];
    if (B[1][0] == 0 || B[1][C - 1] == 0) {
        cout << "IMPOSSIBLE" << nl;
        return;
    }
    int R = 1;
    FOR(i, C) ans[0][i] = '.';
    while (true) {
        FOR(i, C) {
            if (B[R % 2][i] != 1) break;
            if (i == C - 1) {
                cout << R << nl;
                REV(j, R - 1) {
                    FOR(k, C) cout << ans[j][k];
                    cout << nl;
                }
                return;
            }
        }
        R++;
        int k = 0;
        FOR(i, C) {
            B[R % 2][i] = 0;
            ans[R - 1][i] = '.';
        }
        FOR(i, C) {
            FOR(j, B[1 - R % 2][i]) {
                if (i == k) {
                    ans[R - 1][i] = '.';
                    B[R % 2][i]++;
                } else if (i < k) {
                    ans[R - 1][i + 1] = '/';
                    B[R % 2][i + 1]++;
                } else {
                    ans[R - 1][i - 1] = '\\';
                    B[R % 2][i - 1]++;
                }
                k++;
            }
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(i, T) solve(i + 1);
    return 0;
}
