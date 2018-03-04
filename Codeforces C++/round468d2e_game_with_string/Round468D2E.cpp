// http://codeforces.com/contest/931/problem/E
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

string S;
int freq[26], mm[26], mc[26];
vector<int> L[26];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> S;
    FOR(i, 26) freq[i] = 0;
    FOR(i, sz(S)) {
        freq[S[i] - 'a']++;
        L[S[i] - 'a'].pb(i);
    }
    FOR(i, 26) {
        mc[i] = 0;
        if (freq[i] == 0) continue;
        if (sz(L[i]) == 1) {
            mc[i] = 1;
            continue;
        }
        For(j, 1, sz(S)) {
            FOR(k, 26) mm[k] = 0;
            FOR(k, sz(L[i])) mm[S[(L[i][k] + j) % sz(S)] - 'a']++;
            int cnt = 0;
            FOR(k, 26) cnt += (mm[k] == 1);
            MAX(mc[i], cnt);
            if (mc[i] == sz(L[i])) break;
        }
    }
    int cnt = 0;
    FOR(i, 26) cnt += mc[i];
    cout << setprecision(9) << fixed << ((double) cnt) / ((double) sz(S)) << nl;
    return 0;
}
