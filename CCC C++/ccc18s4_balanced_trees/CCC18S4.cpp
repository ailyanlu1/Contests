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

#define MAXN ((int) 1e9 + 5)

int N, sqrtN;
ll dp1[(int) sqrt(MAXN) + 5], dp2[(int) sqrt(MAXN) + 5];

ll solve(int i) {
    if (i == 1) return 1LL;
    ll &x = i <= sqrtN ? dp1[i] : dp2[N / i];
    if (x) return x;
    int sqrtI = (int) sqrt(i);
    for (int j = 1; j <= sqrtI; j++) {
        x += solve(j) * (i / j - i / (j + 1));
        if (j >= 2 && sqrtI < i / j) x += solve(i / j);
    }
    return x;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    sqrtN = (int) sqrt(N);
    memset(dp1, 0, sizeof(dp1));
    memset(dp2, 0, sizeof(dp2));
    cout << solve(N) << nl;
    return 0;
}
