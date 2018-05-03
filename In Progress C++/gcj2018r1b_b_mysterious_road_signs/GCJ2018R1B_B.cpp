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

int T, S, D[MAXS], A[MAXS], B[MAXS], M[MAXS], N[MAXS];

void solve(int t) {
    cin >> S;
    FOR(i, S) {
        cin >> D[i] >> A[i] >> B[i];
        M[i] = D[i] + A[i];
        N[i] = D[i] - B[i];
    }
    int best;
    uset<pii, pair_hash<int, int>> s;
    FOR(i, S) {
        int cnt = 0;
        int start = 0;
        int n;
        bool setN = false;
        FOR(k, S) {
            if (M[k] == M[i]) cnt++;
            else if (!setN || N[n] == N[k]) {
                setN = true;
                n = k;
                cnt++;
            } else {
                if (cnt > best) {
                    best = cnt;
                    s.clear();
                    s.insert({start, k});
                } else if (cnt == best) {
                    if (!s.count({start, k})) s.insert({start, k});
                }
                start = n + 1;
                cnt = k - n;
                n = k;
            }
        }
        if (cnt > best) {
            best = cnt;
            s.clear();
            s.insert({start, S});
        } else if (cnt == best) {
            if (!s.count({start, S})) s.insert({start, S});
        }
    }
    FOR(j, S) {
        int cnt = 0;
        int start = 0;
        int m;
        bool setM = false;
        FOR(k, S) {
            if (N[k] == N[j]) cnt++;
            else if (!setM || M[m] == M[k]) {
                setM = true;
                m = k;
                cnt++;
            } else {
                if (cnt > best) {
                    best = cnt;
                    s.clear();
                    s.insert({start, k});
                } else if (cnt == best) {
                    if (!s.count({start, k})) s.insert({start, k});
                }
                start = m + 1;
                cnt = k - m;
                m = k;
            }
        }
        if (cnt > best) {
            best = cnt;
            s.clear();
            s.insert({start, S});
        } else if (cnt == best) {
            if (!s.count({start, S})) s.insert({start, S});
        }
    }
    cout << "Case #" << t << ":" << sp << best << sp << sz(s) << nl;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    FOR(i, T) solve(i + 1);
    return 0;
}
