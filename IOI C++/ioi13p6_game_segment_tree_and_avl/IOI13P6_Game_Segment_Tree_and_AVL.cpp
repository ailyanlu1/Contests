/*
 * IOI13P6_Game_Segment_Tree_and_AVL.cpp
 *
 *  Created on: Jul 15, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
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

long long gcd2(long long p, long long q) {
    return q == 0 ? p : gcd2(q, p % q);
}

struct Cell {
    int r, c;

    bool operator < (const Cell &x) const {
        return c < x.c || (c == x.c && r < x.r);
    }

    bool operator > (const Cell &x) const {
        return c > x.c || (c == x.c && r > x.r);
    }

    bool operator <= (const Cell &x) const {
        return c < x.c || (c == x.c && r <= x.r);
    }

    bool operator >= (const Cell &x) const {
        return c > x.c || (c == x.c && r >= x.r);
    }

    bool operator == (const Cell &x) const {
        return c == x.c && r == x.r;
    }

    bool operator != (const Cell &x) const {
        return c != x.c || r != x.r;
    }
};

class no_such_element_exception: public runtime_error {
public:
    no_such_element_exception(): runtime_error("No such element exists"){}
    no_such_element_exception(string message): runtime_error(message){}
};

template <typename Key, typename Value>
struct AVLTree {
    /**
     * Represents an inner node of the AVL tree.
     */
    struct Node {
    public:
        Key key;
        Key maxKey;
        Key minKey;
        Value val;
        Value gcd;
        int height, size;
        Node *left = nullptr, *right = nullptr;
        Node(Key key, Value val, int height, int size) {
            this->key = key;
            this->maxKey = key;
            this->minKey = key;
            this->val = val;
            this->size = size;
            this->height = height;
            this->gcd = val;
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
        x->gcd = gcd2(gcd2(x->left ? x->left->gcd : 0LL, x->right ? x->right->gcd : 0LL), x->val);
        x->minKey = x->left ? x->left->minKey : x->key;
        x->maxKey = x->right ? x->right->maxKey : x->key;
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

    /**
     * Returns value associated with the given key in the subtree.
     *
     * @param x the subtree
     * @param key the key
     * @return value associated with the given key in the subtree or
     *         {@code null} if no such key
     * @throws no_such_element_exception if there is no such key
     */
    Node *get(Node *&x, Key key) {
        if (x == nullptr) return nullptr;
        if (key < x->key) return get(x->left, key);
        else if (key > x->key) return get(x->right, key);
        else return x;
    }

    /**
     * Inserts the key-value pair in the subtree. It overrides the old value
     * with the new value if the symbol table already contains the specified key.
     *
     * @param x the subtree
     * @param key the key
     * @param val the value
     * @return the subtree
     */
    Node *put(Node *&x, Key key, Value val) {
        if (x == nullptr) return new Node(key, val, 0, 1);
        if (key < x->key) x->left = put(x->left, key, val);
        else if (key > x->key) x->right = put(x->right, key, val);
        else {
            x->val = val;
            update(x);
            return x;
        }
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
     * Removes the specified key and its associated value from the given
     * subtree.
     *
     * @param x the subtree
     * @param key the key
     * @return the updated subtree
     */
    Node *remove(Node *&x, Key key) {
        if (key < x->key) x->left = remove(x->left, key);
        else if (key > x->key) x->right = remove(x->right, key);
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
     * Returns the node in the subtree with the largest key less than or equal
     * to the given key.
     *
     * @param x the subtree
     * @param key the key
     * @return the node in the subtree with the largest key less than or equal
     *         to the given key
     */
    Node *floor(Node *&x, Key key) {
        if (x == nullptr) return nullptr;
        if (key == x->key) return x;
        if (key < x->key) return floor(x->left, key);
        Node *y = floor(x->right, key);
        if (y != nullptr) return y;
        else return x;
    }

    /**
     * Returns the node in the subtree with the smallest key greater than or
     * equal to the given key.
     *
     * @param x the subtree
     * @param key the key
     * @return the node in the subtree with the smallest key greater than or
     *         equal to the given key
     */
    Node *ceiling(Node *&x, Key key) {
        if (x == nullptr) return nullptr;
        if (key == x->key) return x;
        if (key > x->key) return ceiling(x->right, key);
        Node *y = ceiling(x->left, key);
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
     * Returns the number of keys in the subtree less than key.
     *
     * @param key the key
     * @param x the subtree
     * @return the number of keys in the subtree less than key
     */
    int rank(Key key, Node *&x) {
        if (x == nullptr) return 0;
        if (key < x->key) return rank(key, x->left);
        else if (key > x->key) return 1 + size(x->left) + rank(key, x->right);
        else return size(x->left);
    }

    /**
     * Adds the key-value pairs in the subtree to queue following an in-order traversal.
     *
     * @param x the subtree
     * @param queue the queue
     */
    void keyValuePairsInOrder(Node *&x, vector<pair<Key, Value>> *queue) {
        if (x == nullptr) return;
        keyValuePairsInOrder(x->left, queue);
        queue->push_back({x->key, x->val});
        keyValuePairsInOrder(x->right, queue);
    }

    /**
     * Adds the key-value pairs between {@code lo} and {@code hi} in the subtree
     * to the {@code queue}.
     *
     * @param x the subtree
     * @param queue the queue
     * @param lo the lowest key
     * @param hi the highest key
     */
    void keyValuePairs(Node *&x, vector<pair<Key, Value>> *queue, Key lo, Key hi) {
        if (x == nullptr) return;
        if (lo < x->key) keyValuePairs(x->left, queue, lo, hi);
        if (lo <= x->key && hi >= x->key) queue->push_back({x->key, x->val});
        if (hi > x->key) keyValuePairs(x->right, queue, lo, hi);
    }

    long long query(Node *&x, Key lo, Key hi) {
        if (x == nullptr) return 0LL;
        if (lo <= x->minKey && hi >= x->maxKey) return x->gcd;
        if (hi < x->key) return query(x->left, lo, hi);
        if (lo > x->key) return query(x->right, lo, hi);
        return gcd2(x->val, gcd2(query(x->left, lo, x->left ? x->left->maxKey : hi), query(x->right, x->right ? x->right->minKey : lo, hi)));
    }

public:
    /**
     * Initializes an empty symbol table.
     */
    AVLTree() {}

    /**
     * Checks if the symbol table is empty.
     *
     * @return {@code true} if the symbol table is empty.
     */
    bool isEmpty() {
        return root == nullptr;
    }

    /**
     * Returns the number key-value pairs in the symbol table.
     *
     * @return the number key-value pairs in the symbol table
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
     * Returns the value associated with the given key.
     *
     * @param key the key
     * @return the value associated with the given key if the key is in the
     *         symbol table
     * @throws no_such_element_exception if no such key is in the symbol table
     */
    Value get(Key key) {
        no_such_element_exception("no such key is in the symbol table");
        Node *x = get(root, key);
        return x->val;
    }

    /**
     * Checks if the symbol table contains the given key.
     *
     * @param key the key
     * @return {@code true} if the symbol table contains {@code key}
     *         and {@code false} otherwise
     */
    bool contains(Key key) {
        return get(root, key) != nullptr;
    }

    /**
     * Inserts the specified key-value pair into the symbol table, overwriting
     * the old value with the new value if the symbol table already contains the
     * specified key.
     *
     * @param key the key
     * @param val the value
     */
    void put(Key key, Value val) {
        root = put(root, key, val);
    }

    /**
     * Removes the specified key and its associated value from the symbol table
     * (if the key is in the symbol table).
     *
     * @param key the key
     */
    void remove(Key key) {
        if (!contains(key)) return;
        root = remove(root, key);
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
     * Returns the smallest key in the symbol table and its associated value.
     *
     * @return the smallest key in the symbol table and its associated value
     * @throws runtime_error if the symbol table is empty
     */
    pair<Key, Value> getMin() {
        if (isEmpty()) throw runtime_error("called getMin() with empty symbol table");
        Node *x = getMin(root);
        return {x->key, x->val};
    }

    /**
     * Returns the largest key in the symbol table and its associated value.
     *
     * @return the largest key in the symbol table and its associated value
     * @throws runtime_error if the symbol table is empty
     */
    pair<Key, Value> getMax() {
        if (isEmpty()) throw runtime_error("called getMax() with empty symbol table");
        Node *x = getMax(root);
        return {x->key, x->val};
    }

    /**
     * Returns the largest key in the symbol table less than or equal to {@code key} and its associated value.
     *
     * @param key the key
     * @return the largest key in the symbol table less than or equal to {@code key} and its associated value
     * @throws runtime_error if the symbol table is empty
     * @throws no_such_element_exception if there is no key in the symbol table less than or equal to {@code key}
     */
    pair<Key, Value> floor(Key key) {
        if (isEmpty()) throw runtime_error("called floor() with empty symbol table");
        Node *x = floor(root, key);
        if (x == nullptr) throw no_such_element_exception("call to floor() resulted in no such value");
        return {x->key, x->val};
    }

    /**
     * Returns the smallest key in the symbol table greater than or equal to {@code key} and its associated value.
     *
     * @param key the key
     * @return a pair containing the smallest key in the symbol table greater than or equal to {@code key} and its associated value
     * @throws runtime_error if the symbol table is empty
     * @throws no_such_element_exception if there is no key in the symbol table greater than or equal to {@code key}
     */
    pair<Key, Value> ceiling(Key key) {
        if (isEmpty()) throw runtime_error("called ceiling() with empty symbol table");
        Node *x = ceiling(root, key);
        if (x == nullptr) throw no_such_element_exception("call to ceiling() resulted in no such value");
        return {x->key, x->val};
    }

    /**
     * Returns the kth smallest key in the symbol table and its associated value.
     *
     * @param k the order statistic
     * @return the kth smallest key in the symbol table and its associated value
     * @throws invalid_argument unless {@code k} is between 0 and
     *             {@code size() -1 }
     */
    pair<Key, Value> select(int k) {
        if (k < 0 || k >= size()) throw invalid_argument("k is not in range 0 to size");
        Node *x = select(root, k);
        return {x->key, x->val};
    }

    /**
     * Returns the number of keys in the symbol table strictly less than
     * {@code key}.
     *
     * @param key the key
     * @return the number of keys in the symbol table strictly less than
     *         {@code key}
     */
    int rank(Key key) {
        return rank(key, root);
    }

    /**
     * Returns all key-value pairs in the symbol table following an in-order traversal.
     *
     * @return all key-value pairs in the symbol table following an in-order traversal
     */
    vector<pair<Key, Value>> keyValuePairs() {
        vector<pair<Key, Value>> queue;
        keyValuePairsInOrder(root, &queue);
        return queue;
    }

    /**
     * Returns all key-value pairs in the symbol table in the given range.
     *
     * @param lo the lowest key
     * @param hi the highest key
     * @return all key-value pairs in the symbol table between {@code lo} (inclusive)
     *         and {@code hi} (exclusive)
     */
    vector<pair<Key, Value>> keyValuePairs(Key lo, Key hi) {
        vector<pair<Key, Value>> queue;
        keyValuePairs(root, &queue, lo, hi);
        return queue;
    }

    long long query(Key lo, Key hi) {
        return query(root, lo, hi);
    }

    /**
     * Returns the number of keys in the symbol table in the given range.
     *
     * @param lo minimum endpoint
     * @param hi maximum endpoint
     * @return the number of keys in the symbol table between {@code lo}
     *         (inclusive) and {@code hi} (exclusive)
     */
    int size(Key lo, Key hi) {
        if (lo > hi) return 0;
        if (contains(hi)) return rank(hi) - rank(lo) + 1;
        else return rank(hi) - rank(lo);
    }
};

struct DynamicSegmentTree {
    struct Node {
    public:
        Node *up = nullptr, *down = nullptr;
        AVLTree<Cell, long long> *rowTree = nullptr;
    };

private:
    Node *root;
    int R; // number of rows
    int C; // number of columns

    void update(Node *cur, int cU, int cD, int rowInd, int colInd, long long val) {
        if (cU > rowInd || cD < rowInd) return;
        if (cur->rowTree == nullptr) cur->rowTree = new AVLTree<Cell, long long>();
        cur->rowTree->put({rowInd, colInd}, val);
        if (cU >= rowInd && cD <= rowInd) return;
        int m = cU + (cD - cU) / 2;
        if (rowInd <= m) {
           if (cur->up == nullptr) cur->up = new Node();
           update(cur->up, cU, m, rowInd, colInd, val);
        } else {
           if (cur->down == nullptr) cur->down = new Node();
           update(cur->down, m + 1, cD, rowInd, colInd, val);
        }
    }

    long long query(Node *cur, int cU, int cD, int u, int l, int d, int r) {
        if (cur == nullptr || cU > d || cD < u) return 0LL;
        if (cU >= u && cD <= d) {
            if (cur->rowTree == nullptr) return 0LL;
            return cur->rowTree->query({u, l}, {d, r});
        }
        int m = cU + (cD - cU) / 2;
        if (d <= m) return query(cur->up, cU, m, u, l, d, r);
        else if (u > m) return query(cur->down, m + 1, cD, u, l, d, r);
        long long up = query(cur->up, cU, m, u, l, m, r);
        long long down = query(cur->down, m + 1, cD, m + 1, l, d, r);
        return gcd2(up, down);
    }

public:
    DynamicSegmentTree(int rows, int cols) {
        root = new Node();
        R = rows;
        C = cols;
    }

    void update(int rowInd, int colInd, long long val) {
        update(root, 1, R, rowInd, colInd, val);
    }

    long long query(int u, int l, int d, int r) {
        return query(root, 1, R, u, l, d, r);
    }

    int rows() {
        return R;
    }

    int cols() {
        return C;
    }
} *st;

void init(int R, int C) {
    st = new DynamicSegmentTree(R, C);
}

void update(int P, int Q, long long K) {
    st->update(P + 1, Q + 1, K);
}

long long calculate(int P, int Q, int U, int V) {
    return st->query(P + 1, Q + 1, U + 1, V + 1);
}

int main() {
    int R, C, N;
    ri(R);
    ri(C);
    ri(N);
    init(R, C);
    for (int i = 0; i < N; i++) {
        int T;
        ri(T);
        if (T == 1) {
            int P, Q;
            ll K;
            ri(P);
            ri(Q);
            rll(K);
            update(P, Q, K);
        } else if (T == 2) {
            int P, Q, U, V;
            ri(P);
            ri(Q);
            ri(U);
            ri(V);
            printf("%lld\n", calculate(P, Q, U, V));
        } else {
            i--;
        }
    }
    return 0;
}
