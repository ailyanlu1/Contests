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

int N, ind[MAXN], cnt[1 << 4];
bool A[MAXN][4];
string S[4], ans;

pair<ll, string> solve() {
    ans.clear();
    FOR(i, N) FOR(j, 4) A[i][j] = S[j][i] == 'T';
    FOR(i, 1 << 4) cnt[i] = 0;
    FOR(i, N) {
        ind[i] = 0;
        FOR(j, 4) ind[i] = (ind[i] << 1) | A[i][j];
        cnt[ind[i]]++;
    }
    ll sum[4], tot;
    plli best = {-1, -1};
    FOR(i, 1 << (1 << 4)) {
        FOR(k, 4) sum[k] = 0;
        FOR(j, 1 << 4) FOR(k, 4) sum[k] += (i & (1 << j) ? 1 : 0) == (j & (1 << k) ? 1 : 0) ? cnt[j] : -cnt[j];
        tot = 0;
        FOR(k, 4) tot += sum[k] * sum[k];
        MAX(best, mp(tot, i));
    }
    FOR(i, N) ans.pb((best.s & (1 << ind[i])) ? 'T' : 'F');
    return {best.f, ans};
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> S[0] >> S[1] >> S[2] >> S[3];
    cout << solve().s << nl;
    return 0;
}
