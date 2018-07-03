// http://www.spoj.com/problems/STABLEMP/
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

#define MAXN 505

int T, N, aPrefs[MAXN][MAXN], bRanks[MAXN][MAXN], curA[MAXN], mateB[MAXN];

void solve () {
    cin >> N;
    FOR(i, N) {
        int B, ind;
        cin >> B;
        B--;
        FOR(j, N) {
            cin >> ind;
            ind--;
            bRanks[B][ind] = j;
        }
    }
    FOR(i, N) {
        int A;
        cin >> A;
        A--;
        FOR(j, N) {
            cin >> aPrefs[A][j];
            aPrefs[A][j]--;
        }
    }
    queue<int> q;
    FOR(i, N) {
        curA[i] = -1;
        mateB[i] = -1;
        q.push(i);
    }
    while (!q.empty()) {
        int A = q.front();
        q.pop();
        while (true) {
            int B = aPrefs[A][++curA[A]];
            if (mateB[B] == -1) {
                mateB[B] = A;
                break;
            } else if (bRanks[B][A] < bRanks[B][mateB[B]]) {
                q.push(mateB[B]);
                mateB[B] = A;
                break;
            }
        }
    }
    FOR(i, N) cout << mateB[i] + 1 << sp << i + 1 << nl;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(i, T) solve();
    return 0;
}
