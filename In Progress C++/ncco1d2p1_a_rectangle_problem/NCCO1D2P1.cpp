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

#define MAXN 105

int N;

struct Rectangle {
    int xmin, ymin, xmax, ymax;
} R[MAXN];

inline bool intersects(const Rectangle &a, const Rectangle &b) {
    return a.xmax > b.xmin && a.ymax > b.ymin && a.xmin < b.ymax && a.ymin < b.ymax;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) cin >> R[i].xmin >> R[i].ymin >> R[i].xmax >> R[i].ymax;
    Rectangle ans = R[0];
    vector<int> in;
    uset<int> check;
    in.pb(0);
    For(i, 1, N) check.insert(i);
    for (int i = 0; i < sz(in); i++) {
        vector<int> toInsert;
        for (int j : check) if (intersects(R[in[i]], R[j])) toInsert.pb(j);
        for (int j : toInsert) {
            check.erase(j);
            in.pb(j);
            MIN(ans.xmin, R[j].xmin);
            MAX(ans.xmax, R[j].xmax);
            MIN(ans.ymin, R[j].ymin);
            MAX(ans.ymax, R[j].ymax);
        }
    }
    cout << (ans.xmax - ans.xmin + ans.ymax - ans.ymin) * 2 << nl;
    return 0;
}
