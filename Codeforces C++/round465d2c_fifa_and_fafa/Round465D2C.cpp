// http://codeforces.com/contest/935/problem/C
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

#define EPS 1e-9

pdd F, L;
double R;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> R >> F.f >> F.s >> L.f >> L.s;
    if (sqrt((L.f - F.f) * (L.f - F.f) + (L.s - F.s) * (L.s - F.s)) >= R) {
        cout << setprecision(6) << fixed << F.f << " " << F.s << " " << R << nl;
    } else if (abs(L.f - F.f) <= EPS && abs(L.s - F.s) <= EPS) {
        cout << setprecision(6) << fixed << F.f + R / 2 << " " << F.s << " " << R / 2 << nl;
    } else {
        double angle = atan2((F.s - L.s), (F.f - L.f));
        double newR = (sqrt((L.f - F.f) * (L.f - F.f) + (L.s - F.s) * (L.s - F.s)) + R) / 2;
        pdd C = {L.f + newR * cos(angle), L.s + newR * sin(angle)};
        cout << setprecision(6) << fixed << C.f << " " << C.s << " " << newR << nl;
    }
    return 0;
}
