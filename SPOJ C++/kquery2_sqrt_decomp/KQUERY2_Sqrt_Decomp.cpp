// http://www.spoj.com/problems/KQUERY2/
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

#define MAXN 30005
#define MAXA 10005
#define BSZ 300

int N, Q, A[MAXN], BIT[MAXN / BSZ + 5][MAXA];

void update(int bl, int i, int v) {
    for (; i < MAXA; i += i & -i) BIT[bl][i] += v;
}

int query(int bl, int i) {
    int ret = 0;
    for (; i > 0; i -= i & -i) ret += BIT[bl][i];
    return ret;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) {
        cin >> A[i];
        update(i / BSZ, A[i], 1);
    }
    cin >> Q;
    int t, a, b, c;
    FOR(i, Q) {
        cin >> t;
        if (t == 0) {
            cin >> a >> b;
            a--;
            update(a / BSZ, A[a], -1);
            A[a] = b;
            update(a / BSZ, A[a], 1);
        } else {
            cin >> a >> b >> c;
            a--; b--;
            int ans = 0;
            while (a % BSZ && a <= b) {
                ans += A[a] > c;
                a++;
            }
            while (a + BSZ <= b) {
                ans += (BSZ - query(a / BSZ, c));
                a += BSZ;
            }
            while (a <= b) {
                ans += A[a] > c;
                a++;
            }
            cout << ans << nl;
        }
    }
    return 0;
}
