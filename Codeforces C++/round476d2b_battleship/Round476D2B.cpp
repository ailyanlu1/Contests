// http://codeforces.com/contest/965/problem/B
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

#define MAXN 105

int N, K, cnt[MAXN][MAXN];
char grid[MAXN][MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    string s;
    FOR(i, N) {
        cin >> s;
        FOR(j, N) {
            grid[i][j] = s[j];
            cnt[i][j] = 0;
        }
    }
    FOR(i, N) {
        FOR(j, N - K + 1) {
            bool good = true;
            FOR(k, K) {
                if (grid[i][j + k] == '#') {
                    good = false;
                    break;
                }
            }
            if (good) FOR(k, K) cnt[i][j + k]++;
        }
    }
    FOR(j, N) {
        FOR(i, N - K + 1) {
            bool good = true;
            FOR(k, K) {
                if (grid[i + k][j] == '#') {
                    good = false;
                    break;
                }
            }
            if (good) FOR(k, K) cnt[i + k][j]++;
        }
    }
    pii maxCell = {0, 0};
    int maxCnt = -1;
    FOR(i, N) {
        FOR(j, N) {
            if (cnt[i][j] > maxCnt) {
                maxCnt = cnt[i][j];
                maxCell = {i, j};
            }
        }
    }
    cout << maxCell.f + 1 << sp << maxCell.s + 1 << nl;
    return 0;
}
