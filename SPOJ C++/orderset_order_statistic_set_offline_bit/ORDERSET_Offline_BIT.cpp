// http://www.spoj.com/problems/ORDERSET/
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

template <typename T>
struct FenwickTreeBinarySearch {
private:
    int size;
    int logSize;
    T *array;

public:
    FenwickTreeBinarySearch(int size) {
        this->size = size;
        this->logSize = 31 - __builtin_clz(size);
        array = new T[size + 1];
        for (int i = 0; i <= size; i++) {
            array[i] = 0;
        }
    }

    ~FenwickTreeBinarySearch() {
        delete[](array);
    }

    /**
     * Range Sum query from 1 to ind
     * ind is 1-indexed
     *
     * Time-Complexity:    O(log(n))
     *
     * @param  ind index
     * @return sum
     */
    T rsq(int ind) {
        T sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    /**
     * Range Sum Query from a to b.
     * Search for the sum from array index from a to b
     * a and b are 1-indexed
     *
     * Time-Complexity:    O(log(n))
     *
     * @param  a left index
     * @param  b right index
     * @return sum
     */
    T rsq(int a, int b) {
        return rsq(b) - rsq(a - 1);
    }

    /**
     * Update the array at ind and all the affected regions above ind.
     * ind is 1-indexed
     *
     * Time-Complexity:    O(log(n))
     *
     * @param  ind   index
     * @param  value value
     */
    void update(int ind, T value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    /**
     * Returns the smallest index with a cumulative sum that is greater than or equal to value.
     *
     * @param value value
     * @return the smallest index with a cumulative sum that is greater than or equal to value
     */
    int lower_bound(T value) {
        int ind = 0, i = 0;
        T sum = 0;
        for (int x = logSize; x >= 0; x--) {
            i = ind | (1 << x);
            if (i > size) continue;
            if (sum + array[i] < value) {
                ind = i;
                sum += array[i];
            }
        }
        return ind + 1;
    }

    /**
     * Returns the smallest index with a cumulative sum that is greater than value.
     *
     * @param value value
     * @return the smallest index with a cumulative sum that is greater than value
     */
    int upper_bound(T value) {
        int ind = 0, i = 0;
        T sum = 0;
        for (int x = logSize; x >= 0; x--) {
            i = ind | (1 << x);
            if (i > size) continue;
            if (sum + array[i] <= value) {
                ind = i;
                sum += array[i];
            }
        }
        return ind + 1;
    }

    int getSize() {
        return size;
    }
};

#define MAXQ 200005

int Q, q[MAXQ];
char op[MAXQ];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> Q;
    vector<int> v;
    FOR(i, Q) {
        cin >> op[i] >> q[i];
        switch (op[i]) {
        case 'I':
            v.pb(q[i]);
            break;
        case 'D':
            v.pb(q[i]);
            break;
        case 'K':
            break;
        case 'C':
            v.pb(q[i]);
            break;
        default:
            i--;
            break;
        }
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    umap<int, int> MAP;
    FenwickTreeBinarySearch<int> ft(v.size());
    vector<int> cnt(v.size() + 1);
    FOR(i, sz(v)) MAP[v[i]] = i + 1;
    int sz = 0;
    int x;
    FOR(i, Q) {
        switch (op[i]) {
        case 'I':
            x = MAP[q[i]];
            if (cnt[x] == 0) {
                ft.update(x, 1);
                cnt[x]++;
                sz++;
            }
            break;
        case 'D':
            x = MAP[q[i]];
            if (cnt[x] > 0) {
                ft.update(x, -1);
                cnt[x]--;
                sz--;
            }
            break;
        case 'K':
            if (q[i] > sz) cout << "invalid" << nl;
            else cout << v[ft.lower_bound(q[i]) - 1] << nl;
            break;
        case 'C':
            x = MAP[q[i]];
            cout << ft.rsq(x - 1) << nl;
            break;
        default:
            i--;
            break;
        }
    }
    return 0;
}
