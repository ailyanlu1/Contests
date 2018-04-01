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

#define MAXN 100005

int N, M;
vector<pii> nxt[MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    int a, b, c;
    FOR(i, M) {
        cin >> a >> b >> c;
        a--;
        nxt[a].pb({b, c});
    }
    int curTime = 0;
    FOR(i, N - 1) {
        curTime += 20;
        int bestTime = INT_INF;
        for (pii p : nxt[i]) {
            int curMin = curTime % (24 * 60);
            if (curMin <= p.f * 60) MIN(bestTime, curTime + (p.f * 60 - curMin) + p.s * 60);
            else MIN(bestTime, curTime + (24 * 60 - curMin) + p.f * 60 + p.s * 60);
        }
        curTime = bestTime + 20;
    }
    if (curTime % 60 > 0) curTime += (60 - curTime % 60);
    cout << "Day " << curTime / (24 * 60);
    curTime %= (24 * 60);
    cout << " Hour " << curTime / 60 << nl;
    return 0;
}
