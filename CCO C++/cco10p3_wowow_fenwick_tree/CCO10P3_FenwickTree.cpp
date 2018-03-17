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

/**
 * FenwickTree supporting point updates and range queries, as well as
 * support for lower_bound and upper_bound binary searching the cumulative sum.
 * Memory usage:  O(n)
 *
 * @author Wesley Leung
 */
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

#define MAXN 1000005

int N, cnt = 0, A[MAXN], B[MAXN], X[MAXN], rating[MAXN], id[MAXN];
umap<int, int> MAP;
vector<int> R;
char C[MAXN];
FenwickTreeBinarySearch<int> *ft;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) {
        cin >> C[i];
        if (C[i] == 'N' || C[i] == 'M') {
            cin >> X[i] >> A[i];
            R.pb(A[i]);
        } else if (C[i] == 'Q') {
            cin >> X[i];
        } else {
            i--;
        }
    }
    sort(all(R));
    FOR(i, sz(R)) MAP[R[i]] = sz(R) - i;
    ft = new FenwickTreeBinarySearch<int>(sz(R));
    FOR(i, N) {
        if (C[i] == 'N') {
            ft->update(MAP[A[i]], 1);
            rating[X[i]] = MAP[A[i]];
            id[MAP[A[i]]] = X[i];
            cnt++;
        } else if (C[i] == 'M') {
            ft->update(rating[X[i]], -1);
            ft->update(MAP[A[i]], 1);
            rating[X[i]] = MAP[A[i]];
            id[MAP[A[i]]] = X[i];
        } else if (C[i] == 'Q') {
            cout << id[ft->lower_bound(X[i])] << nl;
        } else {
            i--;
        }
    }
    return 0;
}
