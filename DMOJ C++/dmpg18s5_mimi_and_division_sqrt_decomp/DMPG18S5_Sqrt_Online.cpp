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

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXNQV 200010
#define BSZ 500

int N, Q, A[MAXNQV], LARGE[MAXNQV / BSZ + 5][MAXNQV];
vector<int> factors[MAXNQV];

int query(int l, int r, int x) {
    int ret = 0;
    while (l % BSZ != 0 && l <= r) {
        ret += A[l] % x == 0;
        l++;
    }
    while (l / BSZ < r / BSZ) {
        ret += LARGE[l / BSZ][x];
        l += BSZ;
    }
    while (l <= r) {
        ret += A[l] % x == 0;
        l++;
    }
    return ret;
}

void update(int ind, int val, int delta) {
    for (int x : factors[val]) LARGE[ind / BSZ][x] += delta;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    For(i, 1, MAXNQV) for (int j = i; j < MAXNQV; j += i) factors[j].pb(i);
    cin >> N >> Q;
    FOR(i, N) {
        cin >> A[i];
        update(i, A[i], 1);
    }
    int t, a, b, c;
    FOR(i, Q) {
        cin >> t;
        if (t == 1) {
            cin >> a >> b >> c;
            a--; b--;
            cout << query(a, b, c) << nl;
        } else if (t == 2) {
            cin >> a >> c;
            a--;
            update(a, A[a], -1);
            A[a] = c;
            update(a, A[a], 1);
        } else {
            i--;
        }
    }
    return 0;
}
