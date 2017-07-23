/*
 * CCOPrep1P3.cpp
 *
 *  Created on: Jul 23, 2017
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

#define MAXN 100000

struct Node {
    int rank;
    int id;
    int size;
    Node *left = nullptr, *right = nullptr;
    Node(int rank, int id) {
        this->rank = rank;
        this->id = id;
        this->size = 1;
    }
} *tree[MAXN + 1];

int size(Node *&x) {
    if (x == nullptr) return 0;
    return x->size;
}


void update(Node *&x) {
    x->size = 1 + size(x->left) + size(x->right);
}

Node *rotateRight(Node *&x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    update(x);
    update(y);
    return y;
}

Node *rotateLeft(Node *&x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    update(x);
    update(y);
    return y;
}

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

Node *put(Node *&x, Node *y) {
    if (x == nullptr) return y;
    if (y->rank < x->rank) x->left = put(x->left, y);
    else x->right = put(x->right, y);
    update(x);
    return maintain(x, y->rank > x->rank);
}

void merge(Node *&x, Node *&y) {
    if (x == nullptr) return;
    merge(x->left, y);
    merge(x->right, y);
    y = put(y, x);
}

int select(Node *&x, int k) {
    if (x == nullptr) return -1;
    int t = size(x->left) + 1;
    if (t > k) return select(x->left, k);
    else if (t < k) return select(x->right, k - t);
    return x->id;
}

struct UF {
private:
    int* parent;

public:
    /**
     * Initializes an empty union–find data structure with {@code n} sites
     * {@code 0} through {@code n-1}. Each site is initially in its own
     * component.
     *
     * @param  n the number of sites
     */
    UF(int n) {
        parent = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }
    /**
     * Returns the component identifier for the component containing site {@code p}.
     *
     * @param  p the integer representing one site
     * @return the component identifier for the component containing site {@code p}
     */
    int find(int p) {
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];    // path compression by halving
            p = parent[p];
        }
        return p;
    }

    /**
     * Merges the component containing site {@code p} with the
     * the component containing site {@code q}.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     */
    void join(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return;
        parent[rootP] = rootQ;
        merge(tree[rootP], tree[rootQ]);
    }
};

int N, M, n, x, y, q;
char c;

UF *uf;

int main() {
    ri(N);
    ri(M);
    uf = new UF(N);
    for (int i = 1; i <= N; i++) {
        ri(n);
        tree[i] = put(tree[i], new Node(n, i));
    }
    for (int i = 0; i < M; i++) {
        ri(x);
        ri(y);
        uf->join(x, y);
    }
    ri(q);
    for (int i = 0; i < q; i++) {
        rc(c);
        if (c == 'B') {
            ri(x);
            ri(y);
            uf->join(x, y);
        } else if (c == 'Q') {
            ri(x);
            ri(y);
            printf("%d\n", select(tree[uf->find(x)], y));
        } else {
            i--;
        }
    }
    return 0;
}
