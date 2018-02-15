// https://csacademy.com/contest/round-68/task/triangular-updates/
#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
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
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXRC 1005

int N, Q;
ll row[MAXRC][MAXRC], col[MAXRC][MAXRC], A[MAXRC][MAXRC];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    int r, c, l;
    ll s;
    FOR(i, N) FOR(j, N) A[i][j] = row[i][j] = col[i][j] = 0LL;
    FOR(i, Q) {
        cin >> r >> c >> l >> s;
        r--; c--;
        row[r][c] += s;
        if (r + l < N) {
            row[r + l][c] -= s;
            if (c + 1 < N) {
                col[r + l][c + 1] -= s;
                if (c + l + 1 < N) {
                    col[r + l][c + l + 1] += s;
                }
            }
        }
    }
    For(i, 1, N) FOR(j, N) row[i][j] += row[i - 1][j];
    FOR(i, N) For(j, 1, N) col[i][j] += col[i][j - 1];
    FOR(i, N) FOR(j, N) A[i][j] = row[i][j] + col[i][j] + (i > 0 && j > 0 ? A[i - 1][j - 1] : 0);
    FOR(i, N) FOR(j, N) cout << A[i][j] << " \n"[j != N - 1];
    return 0;
}
