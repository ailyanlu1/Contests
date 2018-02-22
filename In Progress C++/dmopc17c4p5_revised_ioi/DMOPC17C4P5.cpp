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
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl "\n"

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

#define MAXN 1000005

int N;
bool A[MAXN][4];
string S[4], ans;
ll dp[MAXN][2][5];

pair<ll, string> solve() {
    FOR(i, N) FOR(j, 4) A[i][j] = S[j][i] == 'T';
    FOR(i, N) {
        if (i == 0) {
            FOR(j, 2) {
                FOR(k, 4) dp[i][j][k] = (A[i][k] == j ? 1 : -1);
                dp[i][j][4] = -1;
            }
            continue;
        }
        FOR(j, 2) {
            ll a0 = 0LL, a1 = 0LL;
            FOR(k, 4) a0 += (dp[i - 1][0][k] + (A[i][k] == j ? 1 : -1)) * (dp[i - 1][0][k] + (A[i][k] == j ? 1 : -1));
            FOR(k, 4) a1 += (dp[i - 1][1][k] + (A[i][k] == j ? 1 : -1)) * (dp[i - 1][1][k] + (A[i][k] == j ? 1 : -1));
            int b = a0 > a1 ? 0 : 1;
            FOR(k, 4) dp[i][j][k] = dp[i - 1][b][k] + (A[i][k] == j ? 1 : -1);
            dp[i][j][4] = b;
        }
    }
    ll a0 = 0LL, a1 = 0LL;
    FOR(k, 4) a0 += (dp[N - 1][0][k]) * (dp[N - 1][0][k]);
    FOR(k, 4) a1 += (dp[N - 1][1][k]) * (dp[N - 1][1][k]);
    int b = a0 > a1 ? 0 : 1;
    ans.clear();
    REV(i, N - 1) {
        ans.pb(b == 1 ? 'T' : 'F');
        b = dp[i][b][4];
    }
    reverse(ans.begin(), ans.end());
    return {max(a0, a1), ans};
}

pair<ll, string> checkAll() {
    pair<ll, string> best = {-1, ""};
    ll sum[4];
    FOR(i, (1 << N)) {
        FOR(k, 4) sum[k] = 0LL;
        FOR(j, N) {
            if (i & (1 << j)) FOR(k, 4) sum[k] += (S[k][j] == 'T' ? 1 : -1);
            else FOR(k, 4) sum[k] += (S[k][j] == 'F' ? 1 : -1);
        }
        ll tot = 0LL;
        FOR(k, 4) tot += sum[k] * sum[k];
        if (tot > best.f) {
            best.f = tot;
            best.s.clear();
            FOR(j, N) best.s.pb((i & (1 << j)) ? 'T' : 'F');
        }
    }
    return best;
}

void completeTest(int n) {
    N = n;
    int cntWA = 0;
    FOR(i, (1 << (4 * N))) {
        FOR(j, 4) {
            S[j].clear();
            FOR(k, N) {
                S[j].pb((i & (1 << (j * N + k))) ? 'T' : 'F');
            }
        }
        pair<ll, string> ans = solve();
        pair<ll, string> best = checkAll();
        if (ans.f != best.f) {
            cntWA++;
            cout << "WRONG ANSWER" << nl;
            cout << "INPUT:" << nl;
            cout << N << nl;
            FOR(k, 4) cout << S[k] << nl;
            cout << "OUTPUT:" << nl;
            cout << ans.f << " " << ans.s << nl;
            cout << "EXPECTED:" << nl;
            cout << best.f << " " << best.s << nl;
            cout << nl;
        }
    }
    cout << "N = " << N << " ACCURACY: " << setprecision(2) << fixed << 100.00 * ((1 << (4 * N)) - cntWA) / (1 << (4 * N)) << "%" << nl;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testNum = 1;
    if (testNum == 0) {
        cin >> N >> S[0] >> S[1] >> S[2] >> S[3];
        cout << solve().s << nl;
    } else if (testNum == 1) {
        For(n, 1, 5) completeTest(n);
    }
    return 0;
}
