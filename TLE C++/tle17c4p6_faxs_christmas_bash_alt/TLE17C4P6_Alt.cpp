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

const ld EPS = 1e-4;

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

ld binary_search(ld (*f)(ld), ld lo, ld hi) {
    ld mid;
    do {
        mid = lo + (hi - lo) / 2;
        if (f(mid) < 0) lo = mid;
        else hi = mid;
    } while (hi - lo >= EPS);
    return mid;
}

#define MAXX 15010

FenwickTree<ll> quad(MAXX * 2), lin(MAXX * 2), con(MAXX * 2);

ld f(ld x) {
    int below = (int) floor(x);
    int above = (int) ceil(x);
    ld ret = ((((con.rsq(1, below + MAXX) - con.rsq(above + MAXX, MAXX * 2)) * x + 2 * (lin.rsq(above + MAXX, MAXX * 2) - lin.rsq(1, below + MAXX))))
            * x + (quad.rsq(1, below + MAXX) - quad.rsq(above + MAXX, MAXX * 2)));
    return ret;
}

int N;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int x;
    FOR(i, N) {
        cin >> x;
        quad.update(x + MAXX, (ll) x * (ll) x);
        lin.update(x + MAXX, (ll) x);
        con.update(x + MAXX, 1);
        cout << fixed << setprecision(3) << binary_search(f, -15000.0, 15000.0) << nl;
    }
    return 0;
}
