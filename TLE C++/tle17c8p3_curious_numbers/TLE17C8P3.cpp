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

#define MAXMNK ((ll) (1e10 + 5))

int Q;
ll K;
vector<ll> palindromes;

ll create(ll i, bool isOdd) {
    ll ret = i;
    if (isOdd) i /= 10;
    while (i > 0) {
        ret = ret * 10 + (i % 10);
        i /= 10;
    }
    return ret;
}

void generate() {
    ll x;
    FOR(i, 2) {
        ll j = 1;
        while ((x = create(j, i % 2)) <= MAXMNK) {
            if (x % K == 0) palindromes.pb(x);
            j++;
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> Q >> K;
    generate();
    sort(all(palindromes));
    ll M, N;
    FOR(i, Q) {
        cin >> M >> N;
        cout << upper_bound(all(palindromes), N) - lower_bound(all(palindromes), M) << nl;
    }
    return 0;
}
