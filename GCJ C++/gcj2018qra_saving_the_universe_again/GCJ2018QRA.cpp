// https://codejam.withgoogle.com/2018/challenges/00000000000000cb/dashboard
#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
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

#define MAXS 35

int T, D, N;
string P;
ll c[MAXS];

void solve(int t) {
    cin >> D >> P;
    N = sz(P);
    ll damage = 0, cur = 1;
    FOR(i, N) {
        if (P[i] == 'S') damage += cur;
        else cur *= 2;
        c[i] = cur;
    }
    int cnt = 0;
    while (damage > D) {
        bool possible = false;
        REV(i, N - 2) {
            if (P[i] == 'C' && P[i + 1] == 'S') {
                swap(P[i], P[i + 1]);
                damage -= c[i + 1] / 2;
                c[i] = c[i + 1] / 2;
                cnt++;
                possible = true;
                break;
            }
        }
        if (!possible) {
            cout << "Case #" << t << ": IMPOSSIBLE" << nl;
            return;
        }
    }
    cout << "Case #" << t << ": " << cnt << nl;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(i, T) solve(i + 1);
    return 0;
}
