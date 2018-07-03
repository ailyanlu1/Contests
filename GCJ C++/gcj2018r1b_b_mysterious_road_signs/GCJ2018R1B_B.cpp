// https://codejam.withgoogle.com/2018/challenges/0000000000007764/dashboard/000000000003675b
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

#define MAXS 100005

int T, S, D[MAXS][2], ans[MAXS];

void divAndConq(int l, int r) {
    if (r - l <= 1) {
        MAX(ans[l], r - l + 1);
        return;
    }
    int m = l + (r - l) / 2;
    divAndConq(l, m - 1);
    divAndConq(m + 1, r);
    FOR(i, 2) {
        FOR(j, 2) {
            int pl = m, pr = m;
            int a = i == 0 ? D[m][0] : INT_INF;
            int b = i == 1 ? D[m][1] : INT_INF;
            while (pl > l && (D[pl - 1][0] == a || D[pl - 1][1] == b)) pl--;
            while (pr < r && (D[pr + 1][0] == a || D[pr + 1][1] == b)) pr++;
            if (j == 0) {
                if (pl > l) {
                    if (i == 0) b = D[pl - 1][1];
                    else a = D[pl - 1][0];
                }
            } else {
                if (pr < r) {
                    if (i == 0) b = D[pr + 1][1];
                    else a = D[pr + 1][0];
                }
            }
            while (pl > l && (D[pl - 1][0] == a || D[pl - 1][1] == b)) pl--;
            while (pr < r && (D[pr + 1][0] == a || D[pr + 1][1] == b)) pr++;
            MAX(ans[pl], pr - pl + 1);
        }
    }
}

void solve(int t) {
    int d, a, b;
    cin >> S;
    FOR(i, S) {
        cin >> d >> a >> b;
        D[i][0] = d + a;
        D[i][1] = d - b;
    }
    FOR(i, S) ans[i] = 0;
    divAndConq(0, S - 1);
    int best = -1, cnt = 0;
    FOR(i, S) {
        if (ans[i] > best) {
            best = ans[i];
            cnt = 1;
        } else if (ans[i] == best) {
            cnt++;
        }
    }
    cout << "Case #" << t << ": " << best << sp << cnt << nl;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(i, T) solve(i + 1);
    return 0;
}
