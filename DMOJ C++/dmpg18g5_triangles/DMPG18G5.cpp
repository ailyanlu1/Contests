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

#define x first
#define y second

#define MAXN 4005

int N;
pll P[MAXN];
vector<pll> hull;

ll area2(pll a, pll b, pll c) {
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}

int ccw(pll a, pll b, pll c) {
    ll a2 = area2(a, b, c);
    if (a2 < 0) return -1;
    else if (a2 > 0) return +1;
    else return 0;
}

void convexHull() {
    if (N < 3) return;
    int l = 0;
    For(i, 1, N) if (P[i].x < P[l].x) l = i;
    int p = l, q;
    do {
        hull.pb(P[p]);
        q = (p + 1) % N;
        FOR(i, N) if (ccw(P[p], P[i], P[q]) == -1) q = i;
        p = q;
    } while (p != l);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) cin >> P[i].x >> P[i].y;
    convexHull();
    int H = sz(hull);
    if (H < 3) {
        cout << fixed << setprecision(6) << 0.0 << nl;
        return 0;
    }
    int a = 0, b = 1, c = 2;
    ll ans = 0;
    while (true) {
        ll A = abs(area2(hull[a], hull[b], hull[c]));
        MAX(ans, A);
        int d = (c + 1) % H;
        ll B = abs(area2(hull[a], hull[b], hull[d]));
        if (B >= A) {
            c = d;
            continue;
        }
        int e = (b + 1) % H;
        B = abs(area2(hull[a], hull[e], hull[c]));
        if (B >= A) {
            b = e;
            continue;
        }
        if (++a == H) break;
        if (a == b) b = (b + 1) % H;
        if (b == c) c = (c + 1) % H;
    }
    cout << fixed << setprecision(6) << ans / 2.0 << nl;
    return 0;
}
