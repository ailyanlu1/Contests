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

class no_such_element_exception: public runtime_error {
public:
    no_such_element_exception(): runtime_error("No such element exists"){}
    no_such_element_exception(string message): runtime_error(message){}
};

/**
 * Ordered Sqrt Array:
 * Decomposes the array into blocks of size sqrt(n) multiplied by a factor.
 * The factor should be between 1 and 10, and should be smaller for large N.
 *
 * Usage:
 * OrderedSqrtArray<int> arr;
 * OrderedSqrtArray<int, greater<int>> arr;
 *
 * Insert: O(sqrt(N) + log(N))
 * Erase: O(sqrt(N) + log(N))
 * Pop Front: O(sqrt(N))
 * Pop Back: O(1) ammortized
 * At, Accessor: O(log(N))
 * Front, Back: O(1)
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
    const int SCALE_FACTOR; // the scale factor of sqrt(n)
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
     * @param SCALE_FACTOR scales the value of sqrt(n) by this value
     */
    OrderedSqrtArray(const int SCALE_FACTOR = 1) : n(0), SCALE_FACTOR(SCALE_FACTOR) {}

    /**
     * Initializes the structures with the elements between st and en
     * such that st <= en. The elements between the 2 iterators
     * must be sorted.
     *
     * @param st the starting iterator (inclusive)
     * @param en the ending iterator (exclusive)
     * @param SCALE_FACTOR scales the value of sqrt(n) by this value
     */
    template <typename It>
    OrderedSqrtArray(const It st, const It en, const int SCALE_FACTOR = 1) : n(en - st), SCALE_FACTOR(SCALE_FACTOR) {
        assert(n >= 0);
        assert(is_sorted(st, en, cmp));
        int sqrtn = (int) sqrt(n) * SCALE_FACTOR;
        for (It i = st; i < en; i += sqrtn) {
            a.emplace_back(i, min(i + sqrtn, en));
            prefixSZ.push_back(0);
        }
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
        int sqrtn = (int) sqrt(n) * SCALE_FACTOR;
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
     * Erases the first element in the structure.
     */
    void pop_front() {
        assert(n > 0);
        --n;
        a.front().erase(a.front().begin());
        if (a.front().empty()) {
            a.erase(a.begin());
            prefixSZ.pop_back();
        }
        for (int i = 1; i < (int) a.size(); i++) {
            prefixSZ[i] = prefixSZ[i - 1] + (int) a[i - 1].size();
        }
    }

    /**
     * Erases the last element in the structure.
     */
    void pop_back() {
        assert(n > 0);
        --n;
        a.back().pop_back();
        if (a.back().empty()) {
            a.pop_back();
            prefixSZ.pop_back();
        }
    }

    /**
     * Returns a constant reference to the kth value in the structure.
     *
     * @param k the 0-based index
     * @return a constant reference to the kth value in the structure
     */
    const Value &at(const int k) const {
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
     * Accessor operator.
     * Returns a constant reference to the kth value in the structure.
     *
     * @param k the 0-based index
     * @return a constant reference to the kth value in the structure
     */
    const Value &operator [](const int k) const {
        return at(k);
    }

    /**
     * Returns a constant reference to the first element.
     * @return a constant reference to the first element
     */
    const Value &front() const {
        assert(n > 0);
        return a.front().front();
    }

    /**
     * Returns a constant reference to the last element.
     * @return a constant reference to the last element
     */
    const Value &back() const {
        assert(n > 0);
        return a.back().back();
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

/**
 * Ordered Sqrt Array:
 * Decomposes the array into blocks of size sqrt(n) multiplied by a factor.
 * The factor should be between 1 and 10, and should be smaller for large N.
 *
 * Usage:
 * OrderedSqrtArray<int> arr;
 * OrderedSqrtArray<int, greater<int>> arr;
 *
 * Insert: O(sqrt(N) + log(N))
 * Erase: O(sqrt(N) + log(N))
 * Pop Front: O(sqrt(N))
 * Pop Back: O(1) ammortized
 * At, Accessor: O(log(N))
 * Front, Back: O(1)
 * Rank, Contains: O(log(N))
 * Lower Bound, Upper Bound, Floor, Ceiling: O(log(N))
 * Empty, Size: O(1)
 * Values: O(N)
 */
template <const int R, typename Value, typename Container, typename Comparator = less<Value>>
struct OrderedRootArray {
private:
    Comparator cmp; // the comparator
    int n; // the size of the array
    const int SCALE_FACTOR; // the scale factor
    vector<Container*> a; // the array
    vector<int> prefixSZ; // the prefix array of the sizes of the blocks

    // returns the index of the container with the smallest value greater than or equal to val
    int lower_bound_ind(const Value val) const {
        int lo = 0, hi = (int) a.size(), mid;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (cmp(a[mid]->back(), val)) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }

    // returns the index of the container with the smallest value greater than val
    int upper_bound_ind(const Value val) const {
        int lo = 0, hi = (int) a.size(), mid;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (cmp(val, a[mid]->back())) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    // returns the index of the container with largest value less than or equal to val
    int floor_ind(const Value val) const {
        int lo = 0, hi = ((int) a.size()) - 1, mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (cmp(a[mid]->front(), val)) hi = mid - 1;
            else lo = mid + 1;
        }
        return hi;
    }

public:
    /**
     * Initializes an empty structure.
     * @param SCALE_FACTOR scales the value of N ^ (1 / R) by this value
     */
    OrderedRootArray(const int SCALE_FACTOR = 1) : n(0), SCALE_FACTOR(SCALE_FACTOR) {}

    /**
     * Initializes the structures with the elements between st and en
     * such that st <= en. The elements between the 2 iterators
     * must be sorted.
     *
     * @param st the starting iterator (inclusive)
     * @param en the ending iterator (exclusive)
     * @param SCALE_FACTOR scales the value of N ^ (1 / R) by this value
     */
    template <typename It>
    OrderedRootArray(const It st, const It en, const int SCALE_FACTOR = 1) : n(en - st), SCALE_FACTOR(SCALE_FACTOR) {
        assert(n >= 0);
        assert(is_sorted(st, en, cmp));
        int rootn = (int) pow(n, (double) (R - 1) / R) * SCALE_FACTOR;
        for (It i = st; i < en; i += rootn) {
            a.push_back(new Container(i, min(i + rootn, st + n), SCALE_FACTOR));
            prefixSZ.push_back(0);
        }
        for (int i = 1; i < (int) a.size(); i++) {
            prefixSZ[i] = prefixSZ[i - 1] + (int) a[i - 1]->size();
        }
    }

    /**
     * Deletes the structure and all nested containers.
     */
    ~OrderedRootArray() {
        for (int i = 0; i < (int) a.size(); i++) {
            delete a[i];
        }
        a.clear();
    }

    /**
     * Inserts a value into the structure, allowing for duplicates.
     *
     * @param val the value to be inserted
     */
    void insert(const Value val) {
        int i = upper_bound_ind(val);
        if (n++ == 0) {
            a.push_back(new Container());
            prefixSZ.push_back(0);
        }
        if (i == (int) a.size()) a[--i]->insert(val);
        else a[i]->insert(val);
        int rootn = (int) pow(n, (double) (R - 1) / R) * SCALE_FACTOR;
        if ((int) a[i]->size() > 2 * rootn) {
            vector<Value> b;
            while (a[i]->size() > rootn) {
                b.push_back(a[i]->back());
                a[i]->pop_back();
            }
            reverse(b.begin(), b.end());
            a.insert(a.begin() + i + 1, new Container(b.begin(), b.end()));
            prefixSZ.push_back(0);
        }
        for (int j = i + 1; j < (int) a.size(); j++) {
            prefixSZ[j] = prefixSZ[j - 1] + (int) a[j - 1]->size();
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
        int i = lower_bound_ind(val);
        if (i == (int) a.size()) return false;
        if (!a[i]->erase(val)) return false;
        --n;
        if (a[i]->empty()) {
            delete a[i];
            a.erase(a.begin() + i);
            prefixSZ.pop_back();
        }
        for (int j = i + 1; j < (int) a.size(); j++) {
            prefixSZ[j] = prefixSZ[j - 1] + (int) a[j - 1]->size();
        }
        return true;
    }

    /**
     * Erases the first element in the structure.
     */
    void pop_front() {
        assert(n > 0);
        --n;
        a.front()->pop_front();
        if (a.front()->empty()) {
            a.erase(a.begin());
            prefixSZ.pop_back();
        }
        for (int i = 1; i < (int) a.size(); i++) {
            prefixSZ[i] = prefixSZ[i - 1] + (int) a[i - 1]->size();
        }
    }

    /**
     * Erases the last element in the structure.
     */
    void pop_back() {
        assert(n > 0);
        --n;
        a.back()->pop_back();
        if (a.back()->empty()) {
            a.pop_back();
            prefixSZ.pop_back();
        }
    }

    /**
     * Returns a constant reference to the kth value in the structure.
     *
     * @param k the 0-based index
     * @return a constant reference to the kth value in the structure
     */
    const Value &at(const int k) const {
        assert(0 <= k && k < n);
        int lo = 0, hi = ((int) a.size()) - 1, mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (k < prefixSZ[mid]) hi = mid - 1;
            else lo = mid + 1;
        }
        return a[hi]->at(k - prefixSZ[hi]);
    }

    /**
     * Accessor operator.
     * Returns a constant reference to the kth value in the structure.
     *
     * @param k the 0-based index
     * @return a constant reference to the kth value in the structure
     */
    const Value &operator [](const int k) const {
        return at(k);
    }

    /**
     * Returns a constant reference to the first element.
     * @return a constant reference to the first element
     */
    const Value &front() const {
        assert(n > 0);
        return a.front()->front();
    }

    /**
     * Returns a constant reference to the last element.
     * @return a constant reference to the last element
     */
    const Value &back() const {
        assert(n > 0);
        return a.back()->back();
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
        int i = lower_bound_ind(val);
        return i != (int) a.size() && a[i]->contains(val);
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
        int i = lower_bound_ind(val);
        if (i == (int) a.size()) throw no_such_element_exception("call to lower_bound() resulted in no such value");
        pair<int, Value> j = a[i]->lower_bound(val);
        return {prefixSZ[i] + j.first, j.second};
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
        int i = upper_bound_ind(val);
        if (i == (int) a.size()) throw no_such_element_exception("call to upper_bound() resulted in no such value");
        pair<int, Value> j = a[i]->upper_bound(val);
        return {prefixSZ[i] + j.first, j.second};
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
        int i = floor_ind(val);
        if (i == (int) a.size()) throw no_such_element_exception("call to floor() resulted in no such value");
        pair<int, Value> j = a[i]->floor(val);
        return {prefixSZ[i] + j.first, j.second};
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
        int i = lower_bound_ind(val);
        if (i == (int) a.size()) throw no_such_element_exception("call to ceiling() resulted in no such value");
        pair<int, Value> j = a[i]->ceiling(val);
        return {prefixSZ[i] + j.first, j.second};
    }

    /**
     * Returns all values in the structure.
     *
     * @return a vector containing all values in the structure
     */
    vector<Value> values() const {
        vector<Value> ret;
        for (int i = 0; i < (int) a.size(); i++) {
            for (Value x : a[i]->values()) {
                ret.push_back(x);
            }
        }
        return ret;
    }
};

#define MAXN 100005

int N, M, A[MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    FOR(i, N) cin >> A[i];
    sort(A, A + N);
    OrderedRootArray<4, int, OrderedRootArray<3, int, OrderedSqrtArray<int>>> arr(A, A + N, 4);
    //OrderedRootArray<3, int, OrderedSqrtArray<int>> arr(A, A + N, 4);
    int lastAns = 0;
    FOR(i, M) {
        char op;
        int x;
        cin >> op >> x;
        x = x ^ lastAns;
        if (op == 'I') {
            arr.insert(x);
        } else if (op == 'R') {
            arr.erase(x);
        } else if (op == 'S') {
            lastAns = arr.at(x - 1);
            cout << lastAns << nl;
        } else if (op == 'L') {
            try {
                pii k = arr.lower_bound(x);
                lastAns = k.s == x ? k.f + 1 : -1;
            } catch (exception &e) {
                lastAns = -1;
            }
            cout << lastAns << nl;
        } else {
            i--;
        }
    }
    for (int x : arr.values()) cout << x << sp;
    cout << nl;
    return 0;
}
