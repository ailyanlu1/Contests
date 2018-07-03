// https://www.codechef.com/problems/SBSWAP
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

mt19937 rng(time(0));
uniform_real_distribution<double> dis(0.0, 1.0);

struct Node {
public:
    int vertex;
    ll val;
    ll subtreeVal = 0;
    ll delta = 0;
    double priority;
    int size;
    Node *left = nullptr, *right = nullptr, *parent = nullptr;
    Node (int vertex, ll val, double priority, int size = 1) : vertex(vertex), val(val), priority(priority), size(size) {}
};

int size(Node *x) {
    return x ? x->size : 0;
}

Node *root(Node *x) {
    if (!x) return nullptr;
    while (x->parent) x = x->parent;
    return x;
}

Node *min(Node *x) {
    if (!x) return nullptr;
    while (x->left) x = x->left;
    return x;
}

Node *max(Node *x) {
    if (!x) return nullptr;
    while (x->right) x = x->right;
    return x;
}

void update(Node *x) {
    if (x) {
        x->size = 1;
        x->subtreeVal = x->val;
        if (x->left) {
            x->left->parent = x;
            x->size += x->left->size;
            x->subtreeVal += x->left->subtreeVal;
        }
        if (x->right) {
            x->right->parent = x;
            x->size += x->right->size;
            x->subtreeVal += x->right->subtreeVal;
        }
    }
}

void propagate(Node *x) {
    if (x && x->delta) {
        if (x->left) {
            x->left->subtreeVal += x->delta * x->left->size;
            x->left->val += x->delta;
            x->left->delta += x->delta;
        }
        if (x->right) {
            x->right->subtreeVal += x->delta * x->right->size;
            x->right->val += x->delta;
            x->right->delta += x->delta;
        }
        x->delta = 0;
    }
}

int index(Node *x) {
    int ind = size(x->left);
    for (; x->parent; x = x->parent) if (x->parent->left != x) ind += 1 + size(x->parent->left);
    return ind;
}

void merge(Node *&x, Node *l, Node *r) {
    propagate(l);
    propagate(r);
    if (!l || !r) {
        x = l ? l : r;
    } else if (l->priority > r->priority) {
        merge(l->right, l->right, r);
        x = l;
    } else {
        merge(r->left, l, r->left);
        x = r;
    }
    update(x);
}

void split(Node *x, Node *&l, Node *&r, int ind) {
    if (!x) {
        l = r = nullptr;
        return;
    }
    propagate(x);
    x->parent = nullptr;
    if (ind <= size(x->left)) {
        split(x->left, l, x->left, ind);
        r = x;
    } else {
        split(x->right, x->right, r, ind - size(x->left) - 1);
        l = x;
    }
    update(x);
}

int N, Q;
vector<Node*> pre, post;
vector<vector<int>> adj;

void init(int N) {
    pre.reserve(N);
    post.reserve(N);
    adj.reserve(N);
    Node *dummy = nullptr;
    for (int i = 0; i < N; i++) {
        pre.push_back(new Node(i, 0, dis(rng)));
        post.push_back(new Node(i, 0, dis(rng)));
        adj.emplace_back();
        merge(dummy, pre.back(), post.back());
    }
}

// adds an edge from v to w
void addEdge(int v, int w) {
    Node *l = nullptr, *r = nullptr;
    split(root(pre[v]), l, r, index(pre[v]) + 1);
    merge(l, l, root(pre[w]));
    merge(l, l, r);
}

// cut a vertex from its parent
void cutParent(int v) {
    Node *l = nullptr, *mid = nullptr, *r = nullptr;
    split(root(pre[v]), l, mid, index(pre[v]));
    split(mid, mid, r, index(post[v]) + 1);
    merge(l, l, r);
}

bool swapSubtrees(int v, int w) {
    Node *rootV = root(pre[v]), *rootW = root(pre[w]);
    if (rootV == rootW) {
        Node *l = nullptr, *vv = nullptr, *mid = nullptr, *ww = nullptr, *r = nullptr;
        int preIndV = index(pre[v]), preIndW = index(pre[w]), postIndV = index(post[v]), postIndW = index(post[w]);
        if (preIndV > preIndW) {
            swap(v, w);
            swap(preIndV, preIndW);
            swap(postIndV, postIndW);
        }
        if (preIndV <= preIndW && postIndV >= postIndW) return false;
        split(rootV, l, vv, preIndV);
        split(vv, vv, mid, postIndV - preIndV + 1);
        split(mid, mid, ww, preIndW - postIndV - 1);
        split(ww, ww, r, postIndW - preIndW + 1);
        merge(l, l, ww);
        merge(l, l, mid);
        merge(l, l, vv);
        merge(l, l, r);
    } else {
        Node *lv = nullptr, *midv = nullptr, *rv = nullptr, *lw = nullptr, *midw = nullptr, *rw = nullptr;
        split(rootV, lv, midv, index(pre[v]));
        split(midv, midv, rv, index(post[v]) + 1);
        split(rootW, lw, midw, index(pre[w]));
        split(midw, midw, rw, index(post[w]) + 1);
        merge(lv, lv, midw);
        merge(lv, lv, rv);
        merge(lw, lw, midv);
        merge(lw, lw, rw);
    }
    return true;
}

int treeRoot(int v) {
    return min(root(pre[v]))->vertex;
}

bool connected(int v, int w) {
    return treeRoot(v) == treeRoot(w);
}

long long getValue(int v) {
    Node *l = nullptr, *mid = nullptr, *r = nullptr;
    split(root(pre[v]), l, mid, index(pre[v]));
    split(mid, mid, r, index(post[v]) + 1);
    long long ret = mid->subtreeVal;
    merge(l, l, mid);
    merge(l, l, r);
    return ret;
}

void increment(int v, long long val) {
    Node *l = nullptr, *mid = nullptr, *r = nullptr;
    split(root(pre[v]), l, mid, index(pre[v]));
    split(mid, mid, r, index(post[v]) + 1);
    mid->subtreeVal += val * mid->size;
    mid->val += val;
    mid->delta += val;
    merge(l, l, mid);
    merge(l, l, r);
}

// returns true if and only if w is in the subtree of v
// a vertex is considered in a subtree of itself
bool inSubtree(int v, int w) {
    return connected(v, w) && index(pre[v]) <= index(pre[w]) && index(post[v]) >= index(post[w]);
}

void dfs(int v, int prev) {
    for (int w : adj[v]) {
        if (w == prev) continue;
        addEdge(v, w);
        dfs(w, v);
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    init(N);
    int t, a, b;
    ll c;
    FOR(i, N) {
        cin >> c;
        pre[i]->val = pre[i]->subtreeVal = post[i]->val = post[i]->subtreeVal = c;
    }
    FOR(i, N - 1) {
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dfs(0, -1);
    FOR(i, Q) {
        cin >> t;
        if (t == 1) {
            cin >> a;
            a--;
            cout << getValue(a) / 2 << nl;
        } else if (t == 2) {
            cin >> a >> c;
            a--;
            increment(a, c);
        } else {
            cin >> a >> b;
            a--; b--;
            if (!swapSubtrees(a, b)) cout << -1 << nl;
        }
    }
    return 0;
}
