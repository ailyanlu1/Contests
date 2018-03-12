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

class no_such_element_exception: public runtime_error {
public:
    no_such_element_exception(): runtime_error("No such element exists"){}
    no_such_element_exception(string message): runtime_error(message){}
};

/**
 * Ordered Sqrt Array:
 * Decomposes arary into blocks of size sqrt(n).
 *
 * Usage:
 * OrderedSqrtArray<int> arr;
 *
 * Insert: O(sqrt(N))
 * Erase: O(sqrt(N))
 * At, Accessor: O(log(N))
 * Rank, Contains: O(log(N))
 * Lower Bound, Upper Bound, Floor, Ceiling: O(log(N))
 * Empty, Size: O(1)
 * Values: O(N)
 */
template <typename Value, typename Comparator = less<Value>>
struct OrderedSqrtArray {
private:
    Comparator cmp; // the comparator
    int n; // the size of the array
    vector<vector<Value>> a; // the array
    vector<int> prefixSZ; // the prefix array of the sizes of the blocks

    // returns the 2D index of the smallest value greater than or equal to val
    pair<int, int> lower_bound_ind(const Value val) const {
        int lo = 0, hi = (int) a.size(), mid;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (cmp(a[mid].back(), val)) lo = mid + 1;
            else hi = mid;
        }
        if (lo == (int) a.size()) return {(int) a.size(), 0};
        int i = lo;
        lo = 0, hi = (int) a[i].size();
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (cmp(a[i][mid], val)) lo = mid + 1;
            else hi = mid;
        }
        return {i, lo};
    }

    // returns the 2D index of the smallest value greater than val
    pair<int, int> upper_bound_ind(const Value val) const {
        int lo = 0, hi = (int) a.size(), mid;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (cmp(val, a[mid].back())) hi = mid;
            else lo = mid + 1;
        }
        if (lo == (int) a.size()) return {(int) a.size(), 0};
        int i = lo;
        lo = 0, hi = (int) a[i].size();
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (cmp(val, a[i][mid])) hi = mid;
            else lo = mid + 1;
        }
        return {i, lo};
    }

    // returns the 2D index of the largest value less than or equal to val
    pair<int, int> floor_ind(const Value val) const {
        int lo = 0, hi = ((int) a.size()) - 1, mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (cmp(val, a[mid].front())) hi = mid - 1;
            else lo = mid + 1;
        }
        if (hi == -1) return {-1, 0};
        int i = hi;
        lo = 0, hi = ((int) a[i].size()) - 1;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (cmp(val, a[i][mid])) hi = mid - 1;
            else lo = mid + 1;
        }
        return {i, hi};
    }

public:
    /**
     * Initializes an empty structure.
     */
    OrderedSqrtArray() : n(0) {}

    /**
     * Initializes the structures with the elements between st and en
     * such that st <= en. The elements between the 2 iterators
     * must be sorted.
     *
     * @param st the starting iterator (inclusive)
     * @param en the ending iterator (exclusive)
     */
    template <typename It>
    OrderedSqrtArray(const It st, const It en) {
        n = en - st;
        assert(n >= 0);
        assert(is_sorted(st, en, cmp));
        int sqrtn = (int) sqrt(n);
        for (It i = en; i > st; i -= sqrtn) {
            a.emplace_back(i - min((int) (i - st), sqrtn), i);
            prefixSZ.push_back(0);
        }
        reverse(a.begin(), a.end());
        for (int i = 1; i < (int) a.size(); i++) {
            prefixSZ[i] = prefixSZ[i - 1] + (int) a[i - 1].size();
        }
    }

    /**
     * Inserts a value into the structure, allowing for duplicates.
     *
     * @param val the value to be inserted
     */
    void insert(const Value val) {
        pair<int, int> i = upper_bound_ind(val);
        if (n++ == 0) {
            a.emplace_back();
            prefixSZ.push_back(0);
        }
        if (i.first == (int) a.size()) a[--i.first].push_back(val);
        else a[i.first].insert(a[i.first].begin() + i.second, val);
        int sqrtn = (int) sqrt(n);
        if ((int) a[i.first].size() > 2 * sqrtn) {
            a.emplace(a.begin() + i.first + 1, a[i.first].begin() + sqrtn, a[i.first].end());
            a[i.first].resize(sqrtn);
            prefixSZ.push_back(0);
        }
        for (int j = i.first + 1; j < (int) a.size(); j++) {
            prefixSZ[j] = prefixSZ[j - 1] + (int) a[j - 1].size();
        }
    }

    /**
     * Erases a value in the structure. If there are multiple, only one is erased.
     * If the value does not exist, then it is not removed.
     *
     * @param val the value to erase
     * @return true if the value was in the structure and removed, false otherwise
     */
    bool erase(const Value val) {
        pair<int, int> i = lower_bound_ind(val);
        if (i.first == (int) a.size() || a[i.first][i.second] != val) return false;
        --n;
        a[i.first].erase(a[i.first].begin() + i.second);
        if (a[i.first].empty()) {
            a.erase(a.begin() + i.first);
            prefixSZ.pop_back();
        }
        for (int j = i.first + 1; j < (int) a.size(); j++) {
            prefixSZ[j] = prefixSZ[j - 1] + (int) a[j - 1].size();
        }
        return true;
    }

    /**
     * Accessor operator.
     *
     * @param k the 0-based index
     * @return a reference to the kth element in the structure
     */
    Value &operator [](int k) {
        assert(0 <= k && k < n);
        int lo = 0, hi = ((int) a.size()) - 1, mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (k < prefixSZ[mid]) hi = mid - 1;
            else lo = mid + 1;
        }
        return a[hi][k - prefixSZ[hi]];
    }

    /**
     * Returns the kth value in the structure.
     *
     * @param k the 0-based index
     * @return the kth value in the structure
     */
    Value at(int k) const {
        assert(0 <= k && k < n);
        int lo = 0, hi = ((int) a.size()) - 1, mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (k < prefixSZ[mid]) hi = mid - 1;
            else lo = mid + 1;
        }
        return a[hi][k - prefixSZ[hi]];
    }

    /**
     * Modification operator.
     * Returns the kth value in the structure.
     *
     * @param k the 0-based index
     * @return the kth value in the structure
     */
    Value operator [](int k) const {
        return at(k);
    }

    /**
     * Checks if the structure is empty.
     *
     * @return true if the structure is empty, false otherwise
     */
    bool empty() const {
        return n == 0;
    }

    /**
     * Returns the number of values in the structure.
     *
     * @return the number of values in the structure
     */
    int size() const {
        return n;
    }

    /**
     * Checks if the structure contains the given key.
     *
     * @param val the value
     * @return true if the structure contains val, false otherwise
     */
    bool contains(const Value val) const {
        pair<int, int> i = lower_bound_ind(val);
        return i.first != (int) a.size() && a[i.first][i.second] == val;
    }

    /**
     * Returns a pair containing the index and value of the smallest value
     * less than or equal to val. Identical to ceiling.
     *
     * @param val the value
     * @return a pair containing the index and value of the smallest value
     * greater than or equal to val
     * @throws no_such_element_exception if val is greater than the largest value
     * in the structure
     */
    pair<int, Value> lower_bound(const Value val) const {
        pair<int, int> i = lower_bound_ind(val);
        if (i.first == (int) a.size()) throw no_such_element_exception("call to lower_bound() resulted in no such value");
        return {prefixSZ[i.first] + i.second, a[i.first][i.second]};
    }

    /**
     * Returns a pair containing the index and value of the smallest value
     * greater than to val.
     *
     * @param val the value
     * @return a pair containing the index and value of the smallest value
     * less than or equal to val
     * @throws no_such_element_exception if val is greater than or equal to
     * the largest value in the structure
     */
    pair<int, Value> upper_bound(const Value val) const {
        pair<int, int> i = upper_bound_ind(val);
        if (i.first == (int) a.size()) throw no_such_element_exception("call to upper_bound() resulted in no such value");
        return {prefixSZ[i.first] + i.second, a[i.first][i.second]};
    }

    /**
     * Returns a pair containing the index and value of the largest value
     * less than or equal to val.
     *
     * @param val the value
     * @return a pair containing the index and value of the largest value
     * less than or equal to val
     * @throws no_such_element_exception if val is less than the smallest value
     * in the structure
     */
    pair<int, Value> floor(const Value val) const {
        pair<int, int> i = floor_ind(val);
        if (i.first == -1) throw no_such_element_exception("call to floor() resulted in no such value");
        return {prefixSZ[i.first] + i.second, a[i.first][i.second]};
    }

    /**
     * Returns a pair containing the index and value of the smallest value
     * less than or equal to val. Identical to lower_bound.
     *
     * @param val the value
     * @return a pair containing the index and value of the smallest value
     * greater than or equal to val
     * @throws no_such_element_exception if val is greater than the largest value
     * in the structure
     */
    pair<int, Value> ceiling(const Value val) const {
        pair<int, int> i = lower_bound_ind(val);
        if (i.first == (int) a.size()) throw no_such_element_exception("call to ceiling() resulted in no such value");
        return {prefixSZ[i.first] + i.second, a[i.first][i.second]};
    }

    /**
     * Returns all values in the structure.
     *
     * @return a vector containing all values in the structure
     */
    vector<Value> values() const {
        vector<Value> ret;
        for (int i = 0; i < (int) a.size(); i++) {
            for (int j = 0; j < (int) a[i].size(); j++) {
                ret.push_back(a[i][j]);
            }
        }
        return ret;
    }
};

int N;
ll sum = 0;
OrderedSqrtArray<int, greater<int>> tree;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int r;
    FOR(i, N) {
        cin >> r;
        tree.insert(r);
        sum += tree.lower_bound(r).f + 1;
    }
    cout << fixed << setprecision(2) << ((double) sum) / ((double) N) << nl;
    return 0;
}
