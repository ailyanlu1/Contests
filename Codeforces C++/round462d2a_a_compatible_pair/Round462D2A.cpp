// http://codeforces.com/contest/934/problem/A
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

#define MAXNM 50

int N, M;
ll A[MAXNM], B[MAXNM], ans;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    FOR(i, N) cin >> A[i];
    FOR(i, M) cin >> B[i];
    ans = -LL_INF;
    int pos = 0;
    FOR(i, N) {
        FOR(j, M) {
            if (A[i] * B[j] > ans) {
                ans = A[i] * B[j];
                pos = i;
            }
        }
    }
    ans = -LL_INF;
    FOR(i, N) {
        if (i == pos) continue;
        FOR(j, M) {
            if (A[i] * B[j] > ans) {
                ans = A[i] * B[j];
            }
        }
    }
    cout << ans << nl;
    return 0;
}
