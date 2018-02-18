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

#define MAXN 105

int N, A[MAXN][MAXN];

void transpose() {
    FOR(i, N) For(j, i + 1, N) swap(A[i][j], A[j][i]);
}

void revRow() {
    FOR(i, N) FOR(j, N / 2) swap(A[i][j], A[i][N - j - 1]);
}

void rotate() {
    transpose();
    revRow();
}

bool check() {
    FOR(i, N) {
        FOR(j, N) {
            if (i > 0 && A[i][j] <= A[i - 1][j]) return false;
            if (j > 0 && A[i][j] <= A[i][j - 1]) return false;
        }
    }
    return true;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) FOR(j, N) cin >> A[i][j];
    FOR(r, 4) {
        rotate();
        if (check()) FOR(i, N) FOR(j, N) cout << A[i][j] << " \n"[j == N - 1];
    }
    return 0;
}
