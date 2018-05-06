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

struct Node {
public:
    int vertex, val, subtreeVal, size;
    Node *left = nullptr, *right = nullptr, *parent = nullptr;

    Node (int vertex, int val) : vertex(vertex), val(val), subtreeVal(val), size(1) {};
};

map<int, Node*> nodes;
umap<int, int> cnt;

int NN, LL, *XX;

int merge(int l, int r) {
    return l + r;
}

bool isRoot(Node *x) {
    return nullptr == x->parent || (x != x->parent->left && x != x->parent->right);
}

int getSize(Node *x) {
    return nullptr == x ? 0 : x->size;
}

int getSubtreeVal(Node *x) {
    return nullptr == x ? 0 : x->subtreeVal;
}

void update(Node *x) {
    x->subtreeVal = merge(merge(getSubtreeVal(x->left), x->val), getSubtreeVal(x->right));
    x->size = 1 + getSize(x->left) + getSize(x->right);
}

void connect(Node *child, Node *parent, bool hasChild, bool isLeft) {
    if (nullptr != child) child->parent = parent;
    if (hasChild) {
        if (isLeft) parent->left = child;
        else parent->right = child;
    }
}

void rotate(Node *x) {
    Node *p = x->parent;
    Node *g = p->parent;
    bool isRootP = isRoot(p);
    bool isLeft = (x == p->left);
    connect(isLeft ? x->right : x->left, p, true, isLeft);
    connect(p, x, true, !isLeft);
    connect(x, g, !isRootP, isRootP ? false : p == g->left);
    update(p);
}

void splay(Node *x) {
    while (!isRoot(x)) {
        Node *p = x->parent;
        Node *g = p->parent;
        if (!isRoot(p)) rotate((x == p->left) == (p == g->left) ? p : x);
        rotate(x);
    }
    update(x);
}

Node *expose(Node *x) {
    Node *last = nullptr;
    for (Node *y = x; nullptr != y; y = y->parent) {
        splay(y);
        y->left = last;
        last = y;
    }
    splay(x);
    return last;
}

Node *findRoot(Node *x) {
    expose(x);
    while (nullptr != x->right) x = x->right;
    splay(x);
    return x;
}

bool link(Node *x, Node *y) {
    if (findRoot(x) == findRoot(y)) return false;
    expose(x);
    if (nullptr != x->right) return false;
    x->parent = y;
    return true;
}

void cutParent(Node *x) {
    expose(x);
    if (nullptr == x->right) return;
    x->right->parent = nullptr;
    x->right = nullptr;
}

bool modify(Node *x, int val) {
    splay(x);
    x->val = val;
    update(x);
    return true;
}

int queryPathFromRoot(Node *x) {
    expose(x);
    return getSubtreeVal(x);
}

void joinNeighbours(int x) {
    nodes[x] = new Node(x, 0);
    link(nodes[x], nodes.upper_bound(x)->s);
    if (x == 0) return;
    auto it = prev(nodes.lower_bound(x));
    if (cnt[it->f] == 0) {
        cutParent(it->s);
        link(it->s, nodes[x]);
    }
}

void add(int x) {
    if (!nodes.count(x + LL + 1)) joinNeighbours(x + LL + 1);
    if (!nodes.count(x)) joinNeighbours(x);
    if (++cnt[x] == 1) {
        cutParent(nodes[x]);
        link(nodes[x], nodes[x + LL + 1]);
        modify(nodes[x], 1);
    }
}

void remove(int x) {
    if (--cnt[x] == 0) {
        cutParent(nodes[x]);
        link(nodes[x], nodes.upper_bound(x)->s);
        modify(nodes[x], 0);
    }
}

void init(int N, int L, int *X) {
    NN = N;
    LL = L;
    XX = X;
    nodes[0] = new Node(0, 0);
    nodes[1e9 + 15e4] = new Node(1e9 + 15e4, 0);
    FOR(i, N) add(X[i]);
}

int update(int i, int y) {
    remove(XX[i]);
    XX[i] = y;
    add(XX[i]);
    return queryPathFromRoot(nodes[0]);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N, L, M, *X;
    cin >> N >> L >> M;
    X = new int[N];
    FOR(i, N) cin >> X[i];
    init(N, L, X);
    int ii, y;
    FOR(i, M) {
        cin >> ii >> y;
        cout << update(ii, y) << nl;
    }
    return 0;
}
