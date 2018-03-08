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

#define ll __int128
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

ll ternary_search(ll (*f)(ll), ll lo, ll hi) {
    ll mid;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (f(mid) < f(mid + 1)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

#define MAXX 15010

FenwickTree<ll> cube(MAXX * 2), quad(MAXX * 2), lin(MAXX * 2), con(MAXX * 2);

ll f(ll x) {
    int below = (int) (x / 1000 - (x < 0 && x % 1000 ? 1 : 0));
    int above = (int) (x / 1000 + (x > 0 && x % 1000 ? 1 : 0));
    ll ret = ((((con.rsq(1, below + MAXX) - con.rsq(above + MAXX, MAXX * 2)) * x + (lin.rsq(above + MAXX, MAXX * 2) - lin.rsq(1, below + MAXX))))
            * x + (quad.rsq(1, below + MAXX) - quad.rsq(above + MAXX, MAXX * 2))) * x + (cube.rsq(above + MAXX, MAXX * 2) - cube.rsq(1, below + MAXX));
    return ret;
}

int N;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int xx;
    ll x;
    FOR(i, N) {
        cin >> xx;
        x = (ll) xx * 1000;
        cube.update(xx + MAXX, (ll) 1 * (ll) x * (ll) x * (ll) x);
        quad.update(xx + MAXX, (ll) 3 * (ll) x * (ll) x);
        lin.update(xx + MAXX, (ll) 3 * (ll) x);
        con.update(xx + MAXX, (ll) 1);
        cout << fixed << setprecision(3) << ((ld) (ternary_search(f, -15000000, 15000000))) / 1000 << nl;
    }
    return 0;
}
