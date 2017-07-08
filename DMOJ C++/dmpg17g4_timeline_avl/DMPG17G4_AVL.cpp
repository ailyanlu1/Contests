/*
 * DMPG17G4_AVL.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

class no_such_element_exception: public runtime_error {
public:
    no_such_element_exception(): runtime_error("No such element exists"){}
    no_such_element_exception(string message): runtime_error(message){}
};

template <typename Value>
struct AVLTreeSet {
    /**
     * Represents an inner node of the AVL tree.
     */
    struct Node {
    public:
        Value val;
        int height, size;
        Node *left = nullptr, *right = nullptr;
        Node(Value val, int height, int size) {
            this->val = val;
            this->size = size;
            this->height = height;
        }
    };

private:
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
     * Returns the height of the subtree.
     *
     * @param x the subtree
     *
     * @return the height of the subtree.
     */
    int height(Node *&x) {
        if (x == nullptr) return -1;
        return x->height;
    }

    /**
     * Updates the size and height of the subtree.
     *
     * @param x the subtree
     */
    void update(Node *&x) {
        x->size = 1 + size(x->left) + size(x->right);
        x->height = 1 + max(height(x->left), height(x->right));
    }

    /**
     * Returns the balance factor of the subtree. The balance factor is defined
     * as the difference in height of the left subtree and right subtree, in
     * this order. Therefore, a subtree with a balance factor of -1, 0 or 1 has
     * the AVL property since the heights of the two child subtrees differ by at
     * most one.
     *
     * @param x the subtree
     * @return the balance factor of the subtree
     */
    int balanceFactor(Node *&x) {
        return height(x->left) - height(x->right);
    }

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
     * Restores the AVL tree property of the subtree.
     *
     * @param x the subtree
     * @return the subtree with restored AVL property
     */
    Node *balance(Node *&x) {
        if (balanceFactor(x) < -1) {
            if (balanceFactor(x->right) > 0) x->right = rotateRight(x->right);
            x = rotateLeft(x);
        }
        else if (balanceFactor(x) > 1) {
            if (balanceFactor(x->left) < 0) x->left = rotateLeft(x->left);
            x = rotateRight(x);
        }
        update(x);
        return x;
    }

    // auxiliary function for contains
    bool contains(Node *&x, Value val) {
        if (x == nullptr) return false;
        else if (val < x->val) return contains(x->left, val);
        else if (val > x->val) return contains(x->right, val);
        return true;
    }

    /**
     * Inserts the specified value into the symbol table, allowing for duplicates.
     * Deletes the specified value from this symbol table if the specified value is {@code null}.
     *
     * @param x the subtree
     * @param val the value
     * @return the subtree
     */
    Node *add(Node *&x, Value val) {
        if (x == nullptr) return new Node(val, 0, 1);
        if (val < x->val) x->left = add(x->left, val);
        else x->right = add(x->right, val);
        return balance(x);
    }

    /**
     * Removes the smallest value from the given subtree.
     *
     * @param x the subtree
     * @return the updated subtree
     */
    Node *removeMin(Node *&x) {
        if (x->left == nullptr) return x->right;
        x->left = removeMin(x->left);
        return balance(x);
    }

    /**
     * Removes the largest value from the given subtree.
     *
     * @param x the subtree
     * @return the updated subtree
     */
    Node *removeMax(Node *&x) {
        if (x->right == nullptr) return x->left;
        x->right = removeMax(x->right);
        return balance(x);
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
        if (val < x->val) x->left = remove(x->left, val);
        else if (val > x->val) x->right = remove(x->right, val);
        else {
            if (x->left == nullptr) return x->right;
            else if (x->right == nullptr) return x->left;
            else {
                Node *y = x;
                x = getMin(y->right);
                x->right = removeMin(y->right);
                x->left = y->left;
            }
        }
        return balance(x);
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
        if (val == x->val) return x;
        if (val < x->val) return floor(x->left, val);
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
        if (val == x->val) return x;
        if (val > x->val) return ceiling(x->right, val);
        Node *y = ceiling(x->left, val);
        if (y != nullptr) return y;
        else return x;
    }

    // auxiliary function for select
    Node *select(Node *&x, int k) {
        if (x == nullptr) return nullptr;
        int t = size(x->left) + 1;
        if (t == k) return x;
        else if (t > k) return select(x->left, k);
        else return select(x->right, k - t);
    }

    /**
     * Returns the number of values in the subtree less than val.
     *
     * @param val the value
     * @param x the subtree
     * @return the number of values in the subtree less than val
     */
    int rank(Node *&x, Value val) {
        if (x == nullptr) return -1;
        if (val == x->val) {
            int temp = rank(x->left, val);
            if (temp == -1) return size(x->left) + 1;
            else return temp;
        } else if (val < x->val) {
            return rank(x->left, val);
        } else {
            int temp = rank(x->right, val);
            if (temp == -1) return temp;
            else return size(x->left) + 1 + temp;
        }
    }

    /**
     * Adds the values in the subtree to queue following an in-order traversal.
     *
     * @param x the subtree
     * @param queue the queue
     */
    void valuesInOrder(Node *&x, vector<Value> *queue) {
        if (x == nullptr) return;
        valuesInOrder(x->left, queue);
        queue->push_back(x->val);
        valuesInOrder(x->right, queue);
    }

public:
    /**
     * Initializes an empty symbol table.
     */
    AVLTreeSet() {}

    /**
     * Checks if the symbol table is empty.
     *
     * @return {@code true} if the symbol table is empty.
     */
    bool isEmpty() {
        return root == nullptr;
    }

    /**
     * Returns the number values in the symbol table.
     *
     * @return the number values pairs in the symbol table
     */
    int size() {
        return size(root);
    }

    /**
     * Returns the height of the internal AVL tree. It is assumed that the
     * height of an empty tree is -1 and the height of a tree with just one node
     * is 0.
     *
     * @return the height of the internal AVL tree
     */
    int height() {
        return height(root);
    }

    /**
     * Checks if the symbol table contains the given value.
     *
     * @param val the value
     * @return {@code true} if the symbol table contains {@code val}
     *         and {@code false} otherwise
     */
    bool contains(Value val) {
        return contains(root, val);
    }

    /**
     * Inserts the specified value into the symbol table, allowing for duplicates.
     *
     * @param val the value
     */
    void add(Value val) {
        root = add(root, val);
    }

    /**
     * Removes the specified value from the symbol table
     *
     * @param val the value
     */
    void remove(Value val) {
        if (!contains(val)) return;
        root = remove(root, val);
    }

    /**
     * Removes the smallest value from the symbol table.
     *
     * @throws runtime_error if the symbol table is empty
     */
    void removeMin() {
        if (isEmpty()) throw runtime_error("called removeMin() with empty symbol table");
        root = removeMin(root);
    }

    /**
     * Removes the largest value from the symbol table.
     *
     * @throws runtime_error if the symbol table is empty
     */
    void removeMax() {
        if (isEmpty()) throw runtime_error("called removeMax() with empty symbol table");
        root = deleteMax(root);
    }

    /**
     * Returns the smallest value in the symbol table.
     *
     * @return the smallest value in the symbol table
     * @throws runtime_error if the symbol table is empty
     */
    Value getMin() {
        if (isEmpty()) throw runtime_error("called getMin() with empty symbol table");
        return getMin(root).val;
    }

    /**
     * Returns the largest value in the symbol table.
     *
     * @return the largest value in the symbol table
     * @throws runtime_error if the symbol table is empty
     */
    Value getMax() {
        if (isEmpty()) throw runtime_error("called getMax() with empty symbol table");
        return getMax(root).val;
    }

    /**
     * Returns the largest value in the symbol table less than or equal to {@code val}.
     *
     * @param val the value
     * @return the largest value in the symbol table less than or equal to {@code val}
     * @throws runtime_error if the symbol table is empty
     * @throws no_such_element_exception if there is no value in the symbol table less than or equal to {@code val}
     */
    Value floor(Value val) {
        if (isEmpty()) throw runtime_error("called floor() with empty symbol table");
        Node *x = floor(root, val);
        if (x == nullptr) throw no_such_element_exception("call to floor() resulted in no such value");
        else return x->val;
    }

    /**
     * Returns the smallest value in the symbol table greater than or equal to {@code val}.
     *
     * @param val the value
     * @return a pair containing the smallest value in the symbol table greater than or equal to {@code val}
     * @throws runtime_error if the symbol table is empty
     * @throws no_such_element_exception if there is no value in the symbol table greater than or equal to {@code val}
     */
    Value ceiling(Value val) {
        if (isEmpty()) throw runtime_error("called ceiling() with empty symbol table");
        Node *x = ceiling(root, val);
        if (x == nullptr) throw no_such_element_exception("call to ceiling() resulted in no such value");
        else return x->val;
    }

    /**
     * Returns the kth smallest value in the symbol table.
     *
     * @param k the order statistic
     * @return the kth smallest value in the symbol table
     * @throws invalid_argument unless {@code k} is between 0 and
     *             {@code size() -1 }
     */
    Value select(int k) {
        if (k < 0 || k >= size()) throw invalid_argument("k is not in range 0 to size");
        return select(root, k + 1)->val;
    }

    /**
     * Returns the number of values in the symbol table strictly less than
     * {@code val}.
     *
     * @param val the value
     * @return the number of values in the symbol table strictly less than
     *         {@code val}
     */
    int rank(Value val) {
        return (rank(root, val)) - 1;
    }

    /**
     * Returns all values in the symbol table following an in-order traversal.
     *
     * @return all values in the symbol table following an in-order traversal
     */
    vector<Value> values() {
        vector<Value> queue;
        valuesInOrder(root, &queue);
        return queue;
    }

    /**
     * Returns the number of values in the symbol table in the given range.
     *
     * @param lo minimum endpoint
     * @param hi maximum endpoint
     * @return the number of values in the symbol table between {@code lo}
     *         (inclusive) and {@code hi} (exclusive)
     */
    int size(Value lo, Value hi) {
        if (lo > hi) return 0;
        if (contains(hi)) return rank(hi) - rank(lo) + 1;
        else return rank(hi) - rank(lo);
    }
};

struct DynamicSegmentTree {
    struct Node {
    public:
        Node *left = nullptr, *right = nullptr;
        AVLTreeSet<int> times;
    };

private:
    int N;
    Node *root;

    void update(Node *cur, int cL, int cR, int ind, int val, bool ins) {
        if (cL > ind || cR < ind) return;
        if (ins) cur->times.add(val);
        else cur->times.remove(val);
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
                below = cur->times.floor(val);
            } catch (no_such_element_exception &e) {
                return cur->times.ceiling(val);
            }
            try {
                above = cur->times.ceiling(val);
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
umii tToL;
umii lToInd;
char c, s;

int main() {
    ri(N);
    for (int i = 0; i < N; i++) {
        ri(a);
        ri(b);
        T[i] = a;
        L[i] = b;
        labels[i] = b;
    }
    numLabels = N;
    ri(Q);
    for (int i = 0; i < Q; i++) {
        rc(c);
        queries[i].c = c;
        if (c == 'T') {
            ri(a);
            ri(b);
            queries[i].a = a;
            queries[i].b = b;
        } else if (c == 'L') {
            ri(a);
            ri(b);
            labels[numLabels++] = b;
            queries[i].a = a;
            queries[i].b = b;
        } else if (c == 'F') {
            rc(s);
            ri(filter);
            queries[i].s = s;
            queries[i].filter = filter;
            labels[numLabels++] = filter;
        } else if (c == 'S') {
            ri(v);
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
            if (ans != INT_MIN) printf("%d\n", ans);
            else printf("-1\n");
        } else {
            i--;
        }
    }
    return 0;
}
