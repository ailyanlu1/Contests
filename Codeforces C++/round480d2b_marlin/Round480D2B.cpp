// http://codeforces.com/contest/980/problem/B
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

#define MAXN 105

int N, K;
char A[4][MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    FOR(i, 4) FOR(j, N) A[i][j] = '.';
    if (K % 2 == 0) {
        for (int j = 1; K > 0; j++, K -= 2) A[1][j] = A[2][j] = '#';
    } else {
        A[1][(N - 1) / 2] = '#';
        K--;
        for (int j = 1; j < (N - 1) / 2 && K > 0; j++, K -= 2) A[1][(N - 1) / 2 + j] = A[1][(N - 1) / 2 - j] = '#';
        for (int j = 1; j < (N - 1) / 2 && K > 0; j++, K -= 2) A[2][(N - 1) / 2 + j] = A[2][(N - 1) / 2 - j] = '#';
    }
    cout << "YES" << nl;
    FOR(i, 4) {
        FOR(j, N) cout << A[i][j];
        cout << nl;
    }
    return 0;
}
