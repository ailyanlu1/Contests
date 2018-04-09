// http://codeforces.com/contest/948/problem/B
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

bool *isPrime;
vector<int> primes;
int *SPF;
vector<int> factors;

// Linear Time Sieve
void sieve(int N) {
    isPrime = new bool[N + 1];
    for (int i = 0; i <= N; i++) isPrime[i] = true;
    SPF = new int[N + 1];
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= N; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            SPF[i] = i;
        }
        for (int j = 0; j < (int) primes.size() && i * primes[j] <= N && primes[j] <= SPF[i]; j++) {
            isPrime[i * primes[j]] = false;
            SPF[i * primes[j]] = primes[j];
        }
    }
}

void factor(int N) {
    factors.clear();
    while (N != 1) {
        factors.pb(SPF[N]);
        N /= SPF[N];
    }
}

int x2;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> x2;
    sieve(x2);
    factor(x2);
    int lb = x2 - factors.back();
    int ans = INT_INF;
    Rev(i, x2, lb) {
        factor(i);
        if (sz(factors) > 1) ans = MIN(ans, i - factors.back() + 1);
    }
    cout << ans << nl;
    return 0;
}
