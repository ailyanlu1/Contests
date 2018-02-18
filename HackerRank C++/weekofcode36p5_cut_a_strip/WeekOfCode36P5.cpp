#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) ((x) << 1)
#define r(x) ((x) << 1 | 1)
#define m(x, y) ((x) + ((y) - (x)) / 2)
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rld(x) scanf("%Lf", &x)
#define rc(x) scanf(" %c", &x)
#define sc(x) do { scanf("%c", &x); } while (isspace(x))
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define set0(a) memset((a), 0, sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define Fill2(a, x, n, m) FOR(_, n) FOR(__, m) (a)[_][__] = (x)
#define Fill3(a, x, n, m, p) FOR(_, n) FOR(__, m) FOR(___, p) (a)[_][__][___] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))
#define sz(a) ((int) (a).size())
#define len(a) ((int) (a).length())

typedef long long ll;
typedef unsigned long long llu;
typedef long double ld;
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef map<ll, ll> mll;
typedef umap<int, int> umii;
typedef umap<int, ll> umill;
typedef umap<ll, int> umlli;
typedef umap<ll, ll> umll;
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

#define debug(fmt, x) fprintf(stderr, "%d::%s = " fmt, __LINE__, #x, (x)); fflush(stderr)
#define debug2(x) cerr << __LINE__ << "::" << #x << " = " << (x) << '\n' << flush
#define debugva(fmt, ...) fprintf(stderr, "%d::%s = " fmt, __LINE__, #__VA_ARGS__, __VA_ARGS__); fflush(stderr)
#define debugarr(fmt, x, a, b) fprintf(stderr, "%d::%s = {", __LINE__, #x); For(_, a, b) { if (_ != (a)) { fprintf(stderr, ", "); } fprintf(stderr, fmt, (x)[_]); } fprintf(stderr, "}\n"); fflush(stderr)
#define debugarr2(x, a, b) cerr << __LINE__ << "::" << #x << " = {"; For(_, a, b) { if (_ != (a)) { cerr << ", "; } cerr << (x)[_]; } cerr << "}\n" << flush

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXNM 400

int N, M, K, A[MAXNM][MAXNM], temp[MAXNM], temp2[MAXNM], maxSum[MAXNM], fw[MAXNM], bw[MAXNM], fw2[MAXNM], bw2[MAXNM];

int kadane(int *B, int L) {
    int curMax = 0, maxSum = INT_MIN;
    FOR(i, L) {
        curMax = max(curMax + B[i], 0);
        MAX(maxSum, curMax);
    }
    return maxSum;
}

int kadaneRemove1(int *B, int L, int W) {
    int curMax = B[0], maxSum = INT_MIN;
    fw[0] = B[0];
    For(i, 1, L) {
        curMax = max(B[i], curMax + B[i]);
        MAX(maxSum, curMax);
        fw[i] = curMax;
    }
    curMax = maxSum = bw[L - 1] = B[L - 1];
    REV(i, L - 2) {
        curMax = max(B[i], curMax + B[i]);
        MAX(maxSum, curMax);
        bw[i] = curMax;
    }
    int ans = maxSum;
    if (W <= K) For(i, 1, L - 1) MAX(ans, fw[i - 1] + bw[i + 1]);
    return ans;
}

int kadaneRemoveInterval(int *B, int L, bool single = false) {
    int curMax = B[0], maxSum = INT_MIN;
    fw2[0] = B[0];
    For(i, 1, L) {
        curMax = max(B[i], curMax + B[i]);
        MAX(maxSum, curMax);
        fw2[i] = curMax;
    }
    curMax = maxSum = bw2[L - 1] = B[L - 1];
    REV(i, L - 2) {
        curMax = max(B[i], curMax + B[i]);
        MAX(maxSum, curMax);
        bw2[i] = curMax;
    }
    int ans = single ? INT_MIN : maxSum;
    FOR(i, L) For(j, i, min(i + K, L)) MAX(ans, (i > 0 ? fw2[i - 1] : 0) + (j < L - 1 ? bw2[j + 1] : 0));
    return ans;
}

int kadaneRemoveLine(int *B, int L, int start, int end, bool rows) {
    int curMax = B[0], maxSum = INT_MIN;
    fw[0] = B[0];
    For(i, 1, L) {
        curMax = max(B[i], curMax + B[i]);
        MAX(maxSum, curMax);
        fw[i] = curMax;
    }
    curMax = maxSum = bw[L - 1] = B[L - 1];
    REV(i, L - 2) {
        curMax = max(B[i], curMax + B[i]);
        MAX(maxSum, curMax);
        bw[i] = curMax;
    }
    int ans = maxSum;
    FOR(i, L) {
        if (rows) For(j, start, end + 1) temp2[j - start] = A[i][j];
        else For(j, start, end + 1) temp2[j - start] = A[j][i];
        MAX(ans, (i > 0 ? fw[i - 1] : 0) + (i < L - 1 ? bw[i + 1] : 0) + kadaneRemoveInterval(temp2, end - start + 1));
    }
    return ans;
}

int solveRemoveRow() {
    int maxSum = INT_MIN;
    FOR(j, M) {
        FOR(i, N) temp[i] = 0;
        For(k, j, M) {
            FOR(i, N) temp[i] += A[i][k];
            MAX(maxSum, kadaneRemoveLine(temp, N, j, k, true));
        }
    }
    return maxSum;
}

int solveRemoveCol() {
    int maxSum = INT_MIN;
    FOR(j, N) {
        FOR(i, M) temp[i] = 0;
        For(k, j, N) {
            FOR(i, M) temp[i] += A[k][i];
            MAX(maxSum, kadaneRemoveLine(temp, M, j, k, false));
        }
    }
    return maxSum;
}

int solveRemoveRow1() {
    int maxSum = INT_MIN;
    FOR(j, M) {
        FOR(i, N) temp[i] = 0;
        For(k, j, M) {
            FOR(i, N) temp[i] += A[i][k];
            MAX(maxSum, kadaneRemove1(temp, N, k - j + 1));
        }
    }
    return maxSum;
}

int solveRemoveCol1() {
    int maxSum = INT_MIN;
    FOR(j, N) {
        FOR(i, M) temp[i] = 0;
        For(k, j, N) {
            FOR(i, M) temp[i] += A[k][i];
            MAX(maxSum, kadaneRemove1(temp, M, k - j + 1));
        }
    }
    return maxSum;
}

int solve() {
    int maxSum = INT_MIN;
    FOR(j, M) {
        FOR(i, N) temp2[i] = 0;
        For(k, j, M) {
            FOR(i, N) temp2[i] += A[i][k];
            MAX(maxSum, kadane(temp2, N));
        }
    }
    return maxSum;
}

int main() {
    ri(N);
    ri(M);
    ri(K);
    FOR(i, N) FOR(j, M) ri(A[i][j]);
    int ans = INT_MIN;
    if (N == 1) { // O(N^2)
        FOR(i, M) temp[i] = A[0][i];
        ans = kadaneRemoveInterval(temp, M, true);
    } else if (M == 1) { // O(N^2)
        FOR(i, N) temp[i] = A[i][0];
        ans = kadaneRemoveInterval(temp, N, true);
    } else if (pow(max(N, M), 6) <= 1e8) { // O(N^6)
        FOR(i, N) {
            FOR(j, M) {
                For(k, j, min(j + K, M)) {
                    temp[k] = A[i][k];
                    A[i][k] = 0;
                    MAX(ans, solve());
                }
                For(k, j, min(j + K, M)) A[i][k] = temp[k];
                For(k, i, min(i + K, N)) {
                    temp[k] = A[k][j];
                    A[k][j] = 0;
                    MAX(ans, solve());
                }
                For(k, i, min(i + K, N)) A[k][j] = temp[k];
            }
        }
    } else if (pow(max(N, M), 5) <= 1e8) { // O(N^5), fails when cutting something lowers the sum
        MAX(ans, solveRemoveRow());
        MAX(ans, solveRemoveCol());
    } else { // O(N^3), fails when cutting more than one element is required
        MAX(ans, solveRemoveRow1());
        MAX(ans, solveRemoveCol1());
    }
    printf("%d\n", ans);
    return 0;
}
