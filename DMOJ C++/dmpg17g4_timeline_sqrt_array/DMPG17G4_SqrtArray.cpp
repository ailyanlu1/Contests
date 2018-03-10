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
 * Decomposes into blocks of size sqrt(n).
 *
 * Insert: O(sqrt(N))
 * Erase: O(sqrt(N))
 * Select, Accessor: O(log(N))
 * Rank, Contains: O(log(N))
 * Lower Bound, Upper Bound, Floor, Ceiling: O(log(N))
 * isEmpty, Size: O(1)
 */
template <typename Value, typename Comparator = less<Value>>
struct OrderedSqrtArray {
private:
    Comparator cmp;
    int n;
    vector<vector<Value>> a;
    vector<int> prefixSZ;

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
    OrderedSqrtArray() : n(0) {}

    OrderedSqrtArray(const int n) : n(n) {
        assert(n >= 0);
        int sqrtn = (int) sqrt(n);
        for (int i = n; i > 0; i -= sqrtn) {
            a.push_back(vector<Value>(min(i, sqrtn)));
            prefixSZ.push_back(0);
        }
        for (int i = 1; i < (int) a.size(); i++) {
            prefixSZ[i] = prefixSZ[i - 1] + (int) a[i - 1].size();
        }
    }

    template <typename It>
    OrderedSqrtArray(const It st, const It en) {
        n = en - st;
        assert(n >= 0);
        int sqrtn = (int) sqrt(n);
        for (It i = en; i > st; i -= sqrtn) {
            a.push_back(vector<Value>(i - min((int) (i - st), sqrtn), i));
            prefixSZ.push_back(0);
        }
        reverse(a.begin(), a.end());
        for (int i = 1; i < (int) a.size(); i++) {
            prefixSZ[i] = prefixSZ[i - 1] + (int) a[i - 1].size();
        }
    }

    void insert(const Value val) {
        pair<int, int> i = upper_bound_ind(val);
        if (n++ == 0) {
            a.push_back({});
            prefixSZ.push_back(0);
        }
        if (i.first == (int) a.size()) a[--i.first].push_back(val);
        else a[i.first].insert(a[i.first].begin() + i.second, val);
        int sqrtn = (int) sqrt(n);
        if ((int) a[i.first].size() > 2 * sqrtn) {
            vector<int> y(a[i.first].begin() + sqrtn, a[i.first].end());
            a[i.first].resize(sqrtn);
            a.insert(a.begin() + i.first + 1, y);
            prefixSZ.push_back(0);
        }
        for (int j = i.first + 1; j < (int) a.size(); j++) {
            prefixSZ[j] = prefixSZ[j - 1] + (int) a[j - 1].size();
        }
    }

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

    Value &operator [](int k) {
        assert(0 <= k && k < n);
        int lo = 0, hi = (int) (a.size()) - 1, mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (k < prefixSZ[mid]) hi = mid - 1;
            else lo = mid + 1;
        }
        return a[hi][k - prefixSZ[hi]];
    }

    Value select(int k) const {
        assert(0 <= k && k < n);
        int lo = 0, hi = (int) (a.size()) - 1, mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (k < prefixSZ[mid]) hi = mid - 1;
            else lo = mid + 1;
        }
        return a[hi][k - prefixSZ[hi]];
    }

    Value operator [](int k) const {
        return select(k);
    }

    int getRank(const Value val) const {
        pair<int, int> i = lower_bound_ind(val);
        if (i.first == (int) a.size() || a[i.first][i.second] != val) return -1;
        return prefixSZ[i.first] + i.second;
    }

    bool isEmpty() const {
        return n == 0;
    }

    bool contains(const Value val) const {
        pair<int, int> i = lower_bound_ind(val);
        return i.first != (int) a.size() && a[i.first][i.second] == val;
    }

    pair<int, Value> lower_bound(const Value val) const {
        pair<int, int> i = lower_bound_ind(val);
        if (i.first == (int) a.size()) throw no_such_element_exception("call to lower_bound() resulted in no such value");
        return {prefixSZ[i.first] + i.second, a[i.first][i.second]};
    }

    pair<int, Value> upper_bound(const Value val) const {
        pair<int, int> i = upper_bound_ind(val);
        if (i.first == (int) a.size()) throw no_such_element_exception("call to upper_bound() resulted in no such value");
        return {prefixSZ[i.first] + i.second, a[i.first][i.second]};
    }

    pair<int, Value> floor(const Value val) const {
        pair<int, int> i = floor_ind(val);
        if (i.first == -1) throw no_such_element_exception("call to floor() resulted in no such value");
        return {prefixSZ[i.first] + i.second, a[i.first][i.second]};
    }

    pair<int, Value> ceiling(const Value val) const {
        pair<int, int> i = lower_bound_ind(val);
        if (i.first == (int) a.size()) throw no_such_element_exception("call to ceiling() resulted in no such value");
        return {prefixSZ[i.first] + i.second, a[i.first][i.second]};
    }

    vector<Value> values() const {
        vector<Value> ret;
        for (int i = 0; i < (int) a.size(); i++) {
            for (int j = 0; j < (int) a[i].size(); j++) {
                ret.push_back(a[i][j]);
            }
        }
        return ret;
    }

    int size() const {
        return n;
    }
};

struct DynamicSegmentTree {
    struct Node {
    public:
        Node *left = nullptr, *right = nullptr;
        OrderedSqrtArray<int> times;
    };

private:
    int N;
    Node *root;

    void update(Node *cur, int cL, int cR, int ind, int val, bool ins) {
        if (cL > ind || cR < ind) return;
        if (ins) cur->times.insert(val);
        else cur->times.erase(val);
        if (cL >= ind && cR <= ind) return;
        int m = cL + (cR - cL) / 2;
        if (cur->left == nullptr) cur->left = new Node();
        update(cur->left, cL, m, ind, val, ins);
        if (cur->right == nullptr) cur->right = new Node();
        update(cur->right, m + 1, cR, ind, val, ins);
    }

    int query(Node *cur, int cL, int cR, int l, int r, int val) {
        if (cur == nullptr || cL > r || cR < l || cur->times.size() == 0) return INT_MIN;
        if (cL >= l && cR <= r) {
            int below, above;
            try {
                below = cur->times.floor(val).s;
            } catch (no_such_element_exception &e) {
                return cur->times.ceiling(val).s;
            }
            try {
                above = cur->times.ceiling(val).s;
            } catch (no_such_element_exception &e) {
                return below;
            }
            return (abs(above - val) <= abs(below - val)) ? above : below;
        }
        int m = cL + (cR - cL) / 2;
        int left = query(cur->left, cL, m, l, r, val);
        int right = query(cur->right, m + 1, cR, l, r, val);
        if (left == INT_MIN) return right;
        if (right == INT_MIN) return left;
        if (left < right) swap(left, right);
        return (abs(left - val) <= abs(right - val)) ? left : right;
    }

public:
    DynamicSegmentTree(int size) {
        root = new Node();
        N = size;
    }

    void update(int ind, int val, bool ins) {
        update(root, 1, N, ind, val, ins);
    }

    int query(int l, int r, int val) {
        return query(root, 1, N, l, r, val);
    }

    int size() {
        return N;
    }
} *st;

#define MAXN (int) (1e5)
#define MAXT (int) (1e8)
#define MAXL (int) (1e9)

struct Query {
    char c, s;
    int a, b, v, filter;
} queries[MAXN];

int T[MAXN], L[MAXN], N, Q, filter, a, b, v, l, ans, numLabels, labels[MAXN * 2];
umap<int, int> tToL, lToInd;
char c, s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        T[i] = a;
        L[i] = b;
        labels[i] = b;
    }
    numLabels = N;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> c;
        queries[i].c = c;
        if (c == 'T') {
            cin >> a >> b;
            queries[i].a = a;
            queries[i].b = b;
        } else if (c == 'L') {
            cin >> a >> b;
            labels[numLabels++] = b;
            queries[i].a = a;
            queries[i].b = b;
        } else if (c == 'F') {
            cin >> s >> filter;
            queries[i].s = s;
            queries[i].filter = filter;
            labels[numLabels++] = filter;
        } else if (c == 'S') {
            cin >> v;
            queries[i].v = v;
        } else {
            i--;
        }
    }
    st = new DynamicSegmentTree(numLabels);
    sort(labels, labels + numLabels);
    for (int i = 1; i <= numLabels; i++) {
        lToInd[labels[i - 1]] = i;
    }
    for (int i = 0; i < N; i++) {
        st->update(lToInd[L[i]], T[i], true);
        tToL[T[i]] = lToInd[L[i]];
    }
    s = '.';
    for (int i = 0; i < Q; i++) {
        c = queries[i].c;
        if (c == 'T') {
            a = queries[i].a;
            b = queries[i].b;
            l = tToL[a];
            st->update(l, a, false);
            st->update(l, b, true);
            tToL[b] = l; // no need to remove old reference
        } else if (c == 'L') {
            a = queries[i].a;
            b = lToInd[queries[i].b];
            l = tToL[a];
            st->update(l, a, false);
            st->update(b, a, true);
            tToL[a] = b;
        } else if (c == 'F') {
            s = queries[i].s;
            filter = queries[i].filter;
        } else if (c == 'S') {
            v = queries[i].v;
            if (s == '<') ans = st->query(1, lToInd[filter] - 1, v);
            else if (s == '>') ans = st->query(lToInd[filter] + 1, numLabels, v);
            else ans = st->query(1, numLabels, v);
            if (ans != INT_MIN) cout << ans << nl;
            else cout << -1 << nl;
        } else {
            i--;
        }
    }
    return 0;
}
