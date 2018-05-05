// https://codejam.withgoogle.com/2018/challenges/0000000000007765/dashboard/000000000003e068
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

#define MAXD 205

int T, N, D, cnt[MAXD];
bool sold[MAXD];

void solve (int t) {
    cin >> N;
    mt19937 rng(time(0));
    FOR(i, N) {
        cnt[i] = 0;
        sold[i] = false;
    }
    FOR(i, N) {
        cin >> D;
        if (D == -1) assert(false);
        int di;
        int bestCnt = INT_MAX;
        vector<int> good;
        FOR(i, D) {
            cin >> di;
            cnt[di]++;
            if (cnt[di] < bestCnt && !sold[di]) {
                bestCnt = cnt[di];
                good.clear();
                good.pb(di);
            } else if (cnt[di] == bestCnt && !sold[di]) {
                good.pb(di);
            }
        }
        if (sz(good) == 0) {
            cout << -1 << endl;
            cout.flush();
        } else {
            int flavour = good[rng() % sz(good)];
            sold[flavour] = 1;
            cout << flavour << endl;
            cout.flush();
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(i, T) solve(i + 1);
    return 0;
}
