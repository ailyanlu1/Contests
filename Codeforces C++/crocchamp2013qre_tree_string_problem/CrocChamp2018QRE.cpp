// http://codeforces.com/contest/291/problem/E
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

#define MAXN 100005
#define MAXST 300005

int N, LCP[MAXST];
string S[MAXN], T;
vector<int> adj[MAXN];

int dfs(int v, int j) {
    int ret = 0;
    for (int i = 0; i < sz(S[v]); i++, j++) {
        while (j >= 0 && (j == sz(T) || S[v][i] != T[j])) j = LCP[j];
        if (j == sz(T) - 1) ret++;
    }
    for (int w : adj[v]) ret += dfs(w, j);
    return ret;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    S[0] = "";
    int p;
    For(i, 1, N) {
        cin >> p >> S[i];
        adj[p - 1].pb(i);
    }
    cin >> T;
    LCP[0] = -1;
    for (int i = 0, j = -1; i < sz(T); i++, j++, LCP[i] = (i != sz(T) && T[i] == T[j]) ? LCP[j] : j) {
        while (j >= 0 && T[i] != T[j]) j = LCP[j];
    }
    cout << dfs(0, 0) << nl;
    return 0;
}
