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

#define MAXN 200005

int N, M;
ll G[MAXN];
vector<int> cur;
vector<ll> moves;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    FOR(i, N) {
        cin >> G[i];
        cur.pb(0);
    }
    moves.reserve(M + 5);
    ll best = 0;
    for (int i = 0, j = 1; j <= M; i++, j++) {
        if (cur[i % N] + j <= G[i % N]) {
            cur[i % N] += j;
            moves.pb(j);
        }
        else break;
        if (i % N == N - 1) {
            vector<ll> tempMoves = moves;
            vector<int> tempCur = cur;
            moves.pb(M + 1);
            REV(i, sz(moves) - 2) {
                ll excess = G[i % N] - cur[i % N];
                cur[i % N] += min(moves[i + 1] - 1 - moves[i], min((ll) M - moves[i], excess));
                moves[i] = min(moves[i + 1] - 1, min((ll) M, moves[i] + excess));
            }
            ll tot = 0;
            FOR(i, N) tot += cur[i];
            MAX(best, tot);
            moves = tempMoves;
            cur = tempCur;
        }
    }
    cout << best << nl;
    return 0;
}
