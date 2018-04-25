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

#define MAXNK 1000005

bool done[MAXNK], empty[MAXNK];
int N, K, E[MAXNK], ind[MAXNK];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    FOR(i, N) done[i] = empty[i] = 0;
    FOR(i, K) {
        cin >> E[i];
        E[i]--;
    }
    int p;
    FOR(i, K + 1) {
        cin >> p;
        empty[--p] = 1;
        ind[p] = i + 1;
    }
    sort(E, E + K);
    stack<int> s;
    For(i, E[0] + 1, N) if (empty[i]) s.push(i);
    FOR(i, E[0] + 1) if (empty[i]) s.push(i);
    int cur = E[0];
    FOR(i, K) {
        while (cur < E[i]) {
            cur++;
            if (empty[cur] && !done[cur]) s.push(cur);
        }
        while (done[s.top()]) s.pop();
        done[s.top()] = 1;
        while (done[s.top()]) s.pop();
    }
    cout << ind[s.top()] << nl;
    return 0;
}
