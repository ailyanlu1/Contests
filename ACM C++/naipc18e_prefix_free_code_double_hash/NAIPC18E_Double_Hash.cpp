// https://naipc18.kattis.com/problems/prefixfreecode
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

#define MAXN 1000005

template <typename T>
struct FenwickTree {
private:
    int size;
    T *array;

public:
    FenwickTree(int size) {
        this->size = size;
        array = new T[size + 1];
        for (int i = 0; i <= size; i++) {
            array[i] = 0;
        }
    }

    T rsq(int ind) {
        T sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    T rsq(int a, int b) {
        if (a > b) return 0;
        return rsq(b) - rsq(a - 1);
    }

    void update(int ind, T value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    int getSize() {
        return size;
    }
};

int N, K;
umap<ll, int> h1, h2;
uset<ll> h1dup, h2dup;
string S[MAXN];
string T;
vector<int> ord;
FenwickTree<int> *ft;

#define BASE1 ((ll) 10007)
#define MOD1 ((ll) 1e9 + 7)
#define BASE2 ((ll) 137)
#define MOD2 ((ll) 1e9 + 9)

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    FOR(i, N) cin >> S[i];
    sort(S, S + N);
    FOR(i, N) {
        ll hsh1 = 0, hsh2 = 0;
        FOR(j, sz(S[i])) {
            hsh1 = (hsh1 * BASE1 + (S[i][j] - 'a' + 1)) % MOD1;
            hsh2 = (hsh2 * BASE2 + (S[i][j] - 'a' + 1)) % MOD2;
        }
        if (h1.count(hsh1)) h1dup.insert(hsh1);
        else h1[hsh1] = i;
        if (h2.count(hsh2)) h2dup.insert(hsh2);
        else h2[hsh2] = i;
    }
    cin >> T;
    ll hsh1 = 0, hsh2 = 0;
    FOR(i, sz(T)) {
        hsh1 = (hsh1 * BASE1 + (T[i] - 'a' + 1)) % MOD1;
        hsh2 = (hsh2 * BASE2 + (T[i] - 'a' + 1)) % MOD2;
        if (h1.count(hsh1) && h2.count(hsh2)) {
            if (h2dup.count(hsh2)) ord.pb(h1[hsh1]);
            else ord.pb(h2[hsh2]);
            hsh1 = hsh2 = 0;
        }
    }
    ft = new FenwickTree<int>(N);
    FOR(i, N) ft->update(i + 1, 1);
    FOR(i, sz(ord)) ft->update(ord[i] + 1, -1);
    ll ind = 1LL, fact = 1LL;
    REV(i, sz(ord) - 1) {
        ll r = ft->rsq(1, ord[i]);
        ft->update(ord[i] + 1, 1);
        ind = (ind + r * fact) % MOD1;
        fact = fact * (N - i) % MOD1;
    }
    cout << ind << nl;
    return 0;
}
