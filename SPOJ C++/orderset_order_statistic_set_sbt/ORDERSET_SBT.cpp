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

class no_such_element_exception: public runtime_error {
public:
    no_such_element_exception(): runtime_error("No such element exists"){}
    no_such_element_exception(string message): runtime_error(message){}
};

template <typename Value, typename Comparator = less<Value>>
struct SBTSet {
private:
    Comparator cmp;

    /**
     * Represents an inner node of the tree.
     */
    struct Node {
        Value val;
        int size;
        Node *left = nullptr, *right = nullptr;
        Node(Value val, int size) {
            this->val = val;
            this->size = size;
        }
    };

    /**
     * The root node.
     */
    Node *root = nullptr;

    /**
     * Returns the number of nodes in the subtree.
     *
     * @param x the subtree
     *
     * @return the number of nodes in the subtree
     */
    int size(Node *&x) {
        if (x == nullptr) return 0;
        return x->size;
    }


    /**
     * Updates the size and height of the subtree.
     *
     * @param x the subtree
     */
    void update(Node *&x) {
        x->size = 1 + size(x->left) + size(x->right);
    }

    /**
     * Rotates the given subtree to the right.
     *
     * @param x the subtree
     * @return the right rotated subtree
     */
    Node *rotateRight(Node *&x) {
        Node *y = x->left;
        x->left = y->right;
        y->right = x;
        update(x);
        update(y);
        return y;
    }

    /**
     * Rotates the given subtree to the left.
     *
     * @param x the subtree
     * @return the left rotated subtree
     */
    Node *rotateLeft(Node *&x) {
        Node *y = x->right;
        x->right = y->left;
        y->left = x;
        update(x);
        update(y);
        return y;
    }

    /**
     * Balances the tree by size.
     *
     * @param x the subtree
     * @param flag whether the left subtree should be compared or the right subtree:
     *        {@code true} if the tree is right heavy, {@code false} if the tree is left heavy.
     * @return the balanced subtree
     */
    Node *maintain(Node *&x, bool flag) {
        if (flag) {
            if (x->right == nullptr) return x;
            if (size(x->left) < size(x->right->left)) {
                x->right = rotateRight(x->right);
                x = rotateLeft(x);
            } else if (size(x->left) < size(x->right->right)) {
                x = rotateLeft(x);
            } else {
                return x;
            }
        } else {
            if (x->left == nullptr) return x;
            if (size(x->right) < size(x->left->right)) {
                x->left = rotateLeft(x->left);
                x = rotateRight(x);
            } else if (size(x->right) < size(x->left->left)) {
                x = rotateRight(x);
            } else {
                return x;
            }
        }
        x->left = maintain(x->left, false);
        x->right = maintain(x->right, true);
        x = maintain(x, true);
        x = maintain(x, false);
        return x;
    }

    // auxiliary function for contains
    bool contains(Node *&x, Value val) {
        if (x == nullptr) return false;
        else if (cmp(val, x->val)) return contains(x->left, val);
        else if (cmp(x->val, val)) return contains(x->right, val);
        return true;
    }

    /**
     * Inserts the specified value into the set, allowing for duplicates.
     *
     * @param x the subtree
     * @param val the value
     * @return the subtree
     */
    Node *add(Node *&x, Value val) {
        if (x == nullptr) return new Node(val, 1);
        if (cmp(val, x->val)) x->left = add(x->left, val);
        else if (cmp(x->val, val)) x->right = add(x->right, val);
        else return x;
        update(x);
        return maintain(x, !cmp(val, x->val));
    }

    /**
     * Removes the smallest value from the given subtree.
     *
     * @param x the subtree
     * @return the updated subtree
     */
    Node *removeMin(Node *&x, bool freeMemory) {
        if (x->left == nullptr) {
            Node *y = x->right;
            if (freeMemory) delete x;
            return y;
        }
        x->left = removeMin(x->left, freeMemory);
        update(x);
        return x;
    }

    /**
     * Removes the largest value from the given subtree.
     *
     * @param x the subtree
     * @return the updated subtree
     */
    Node *removeMax(Node *&x, bool freeMemory) {
        if (x->right == nullptr) {
            Node *y = x->left;
            if (freeMemory) delete x;
            return y;
        }
        x->right = removeMax(x->right, freeMemory);
        update(x);
        return x;
    }

    /**
     * Returns the node with the smallest value in the subtree.
     *
     * @param x the subtree
     * @return the node with the smallest value in the subtree
     */
    Node *getMin(Node *&x) {
        if (x->left == nullptr) return x;
        return getMin(x->left);
    }

    /**
     * Returns the node with the largest value in the subtree.
     *
     * @param x the subtree
     * @return the node with the largest value in the subtree
     */
    Node *getMax(Node *&x) {
        if (x->right == nullptr) return x;
        return getMax(x->right);
    }

    /**
     * Removes the specified value and its associated value from the given
     * subtree.
     *
     * @param x the subtree
     * @param val the value
     * @return the updated subtree
     */
    Node *remove(Node *&x, Value val) {
        if (cmp(val, x->val)) x->left = remove(x->left, val);
        else if (cmp(x->val, val)) x->right = remove(x->right, val);
        else {
            if (x->left == nullptr) {
                Node *y = x->right;
                delete x;
                return y;
            } else if (x->right == nullptr) {
                Node *y = x->left;
                delete x;
                return y;
            } else {
                Node *y = x;
                x = getMin(y->right);
                x->right = removeMin(y->right, false);
                x->left = y->left;
                delete y;
            }
        }
        update(x);
        return x;
    }

    /**
     * Returns the node in the subtree with the largest value less than or equal
     * to the given value.
     *
     * @param x the subtree
     * @param val the value
     * @return the node in the subtree with the largest value less than or equal
     *         to the given value
     */
    Node *floor(Node *&x, Value val) {
        if (x == nullptr) return nullptr;
        if (!cmp(val, x->val) && !cmp(x->val, val)) return x;
        if (cmp(val, x->val)) return floor(x->left, val);
        Node *y = floor(x->right, val);
        if (y != nullptr) return y;
        else return x;
    }

    /**
     * Returns the node in the subtree with the smallest value greater than or
     * equal to the given value.
     *
     * @param x the subtree
     * @param val the value
     * @return the node in the subtree with the smallest value greater than or
     *         equal to the given value
     */
    Node *ceiling(Node *&x, Value val) {
        if (x == nullptr) return nullptr;
        if (!cmp(val, x->val) && !cmp(x->val, val)) return x;
        if (cmp(x->val, val)) return ceiling(x->right, val);
        Node *y = ceiling(x->left, val);
        if (y != nullptr) return y;
        else return x;
    }

    /**
     * Returns the node with value the kth smallest value in the subtree.
     *
     * @param x the subtree
     * @param k the kth smallest value in the subtree
     * @return the node with value the kth smallest value in the subtree
     */
    Node *select(Node *&x, int k) {
        if (x == nullptr) return nullptr;
        int t = size(x->left);
        if (t > k) return select(x->left, k);
        else if (t < k) return select(x->right, k - t - 1);
        return x;
    }

    /**
     * Returns the number of values in the subtree less than val.
     *
     * @param val the value
     * @param x the subtree
     * @return the number of values in the subtree less than val
     */
    int getRank(Node *&x, Value val) {
        if (x == nullptr) return 0;
        if (!cmp(x->val, val)) return getRank(x->left, val);
        else return 1 + size(x->left) + getRank(x->right, val);
    }

    /**
     * Adds the values in the subtree to queue following an in-order traversal.
     *
     * @param x the subtree
     * @param queue the queue
     */
    void valuesInOrder(Node *&x, vector<Value> &queue) {
        if (x == nullptr) return;
        valuesInOrder(x->left, queue);
        queue.push_back(x->val);
        valuesInOrder(x->right, queue);
    }

    /**
     * Adds the values between {@code lo} and {@code hi} in the subtree
     * to the {@code queue}.
     *
     * @param x the subtree
     * @param queue the queue
     * @param lo the lowest value
     * @param hi the highest value
     */
    void values(Node *&x, vector<Value> &queue, Value lo, Value hi) {
        if (x == nullptr) return;
        if (cmp(lo, x->val)) values(x->left, queue, lo, hi);
        if (!cmp(x->val, lo) && !cmp(hi, x->val)) queue.push_back(x->val);
        if (cmp(x->val, hi)) values(x->right, queue, lo, hi);
    }

    /**
     * Clears the symbol table.
     * @param x the subtree
     */
    void clear(Node *x) {
        if (x == nullptr) return;
        clear(x->left);
        clear(x->right);
        delete x;
        x = nullptr;
    }

public:
    /**
     * Initializes an empty set.
     */
    SBTSet() {}

    /**
     * Deletes the symbol table.
     */
    ~SBTSet() {
        clear(root);
    }

    /**
     * Clears the symbol table.
     */
    void clear() {
        clear(root);
        root = nullptr;
    }

    /**
     * Checks if the set is empty.
     *
     * @return {@code true} if the set is empty.
     */
    bool isEmpty() {
        return root == nullptr;
    }

    /**
     * Returns the number values in the set.
     *
     * @return the number values pairs in the set
     */
    int size() {
        return size(root);
    }

    /**
     * Checks if the set contains the given value.
     *
     * @param val the value
     * @return {@code true} if the set contains {@code val}
     *         and {@code false} otherwise
     */
    bool contains(Value val) {
        return contains(root, val);
    }

    /**
     * Inserts the specified value into the set, allowing for duplicates.
     *
     * @param val the value
     */
    void add(Value val) {
        root = add(root, val);
    }

    /**
     * Removes the specified value from the set
     *
     * @param val the value
     */
    void remove(Value val) {
        if (!contains(val)) return;
        root = remove(root, val);
    }

    /**
     * Removes the smallest value from the set.
     *
     * @throws runtime_error if the set is empty
     */
    void removeMin() {
        if (isEmpty()) throw runtime_error("called removeMin() with empty set");
        root = removeMin(root, true);
    }

    /**
     * Removes the largest value from the set.
     *
     * @throws runtime_error if the set is empty
     */
    void removeMax() {
        if (isEmpty()) throw runtime_error("called removeMax() with empty set");
        root = removeMax(root, true);
    }

    /**
     * Returns the smallest value in the set.
     *
     * @return the smallest value in the set
     * @throws runtime_error if the set is empty
     */
    Value getMin() {
        if (isEmpty()) throw runtime_error("called getMin() with empty set");
        return getMin(root)->val;
    }

    /**
     * Returns the largest value in the set.
     *
     * @return the largest value in the set
     * @throws runtime_error if the set is empty
     */
    Value getMax() {
        if (isEmpty()) throw runtime_error("called getMax() with empty set");
        return getMax(root)->val;
    }

    /**
     * Returns the largest value in the set less than or equal to {@code val}.
     *
     * @param val the value
     * @return the largest value in the set less than or equal to {@code val}
     * @throws runtime_error if the set is empty
     * @throws no_such_element_exception if there is no value in the set less than or equal to {@code val}
     */
    Value floor(Value val) {
        if (isEmpty()) throw runtime_error("called floor() with empty set");
        Node *x = floor(root, val);
        if (x == nullptr) throw no_such_element_exception("call to floor() resulted in no such value");
        return x->val;
    }

    /**
     * Returns the smallest value in the set greater than or equal to {@code val}.
     *
     * @param val the value
     * @return a pair containing the smallest value in the set greater than or equal to {@code val}
     * @throws runtime_error if the set is empty
     * @throws no_such_element_exception if there is no value in the set greater than or equal to {@code val}
     */
    Value ceiling(Value val) {
        if (isEmpty()) throw runtime_error("called ceiling() with empty set");
        Node *x = ceiling(root, val);
        if (x == nullptr) throw no_such_element_exception("call to ceiling() resulted in no such value");
        return x->val;
    }

    /**
     * Returns the kth smallest value in the set.
     *
     * @param k the order statistic
     * @return the kth smallest value in the set
     * @throws invalid_argument unless {@code k} is between 0 and
     *             {@code size() -1 }
     */
    Value select(int k) {
        if (k < 0 || k >= size()) throw invalid_argument("k is not in range 0 to size");
        return select(root, k)->val;
    }

    /**
     * Returns the number of values in the set strictly less than
     * {@code val}.
     *
     * @param val the value
     * @return the number of values in the set strictly less than
     *         {@code val}
     */
    int getRank(Value val) {
        return getRank(root, val);
    }

    /**
     * Returns all values in the set following an in-order traversal.
     *
     * @return all values in the set following an in-order traversal
     */
    vector<Value> values() {
        vector<Value> queue;
        valuesInOrder(root, queue);
        return queue;
    }

    /**
     * Returns all values in the set in the given range.
     *
     * @param lo the lowest value
     * @param hi the highest value
     * @return all value in the set between {@code lo} (inclusive)
     *         and {@code hi} (exclusive)
     */
    vector<Value> values(Value lo, Value hi) {
        vector<Value> queue;
        values(root, queue, lo, hi);
        return queue;
    }

    /**
     * Returns the number of values in the set in the given range.
     *
     * @param lo minimum endpoint
     * @param hi maximum endpoint
     * @return the number of values in the set between {@code lo}
     *         (inclusive) and {@code hi} (exclusive)
     */
    int size(Value lo, Value hi) {
        if (cmp(hi, lo)) return 0;
        if (contains(hi)) return getRank(hi) - getRank(lo) + 1;
        else return getRank(hi) - getRank(lo);
    }
};

int Q;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> Q;
    SBTSet<int> T;
    char op;
    int x;
    FOR(i, Q) {
        cin >> op >> x;
        switch (op) {
        case 'I':
            T.add(x);
            break;
        case 'D':
            T.remove(x);
            break;
        case 'K':
            if (x > sz(T)) cout << "invalid" << nl;
            else cout << T.select(x - 1) << nl;
            break;
        case 'C':
            cout << T.getRank(x) << nl;
            break;
        default:
            i--;
            break;
        }
    }
    return 0;
}
