// http://www.spoj.com/problems/DYNALCA/
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

struct LinkCutTreeLCA {
private:
    struct Node {
    public:
        int vertex;
        Node *left = nullptr, *right = nullptr, *parent = nullptr;

        Node (int vertex) : vertex(vertex) {};
    };

    int V;
    vector<Node*> nodes;

    bool isRoot(Node *x) {
        return nullptr == x->parent || (x != x->parent->left && x != x->parent->right);
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
    }

    void splay(Node *x) {
        while (!isRoot(x)) {
            Node *p = x->parent;
            Node *g = p->parent;
            if (!isRoot(p)) rotate((x == p->left) == (p == g->left) ? p : x);
            rotate(x);
        }
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
        if (nullptr != x->right) throw runtime_error("x is not a root node");
        x->parent = y;
        return true;
    }

    void cutParent(Node *x) {
        expose(x);
        if (nullptr == x->right) throw runtime_error("x is a root node");
        x->right->parent = nullptr;
        x->right = nullptr;
    }

    Node *lca(Node *x, Node *y) {
        if (findRoot(x) != findRoot(y)) return nullptr;
        expose(x);
        return expose(y);
    }

public:
    LinkCutTreeLCA(int V) : V(V), nodes(V) {
        for (int v = 0; v < V; v++) {
            nodes[v] = new Node(v);
        }
    }

    bool link(int v, int w) {
        return link(nodes[v], nodes[w]);
    }

    void cutParent(int v) {
        cutParent(nodes[v]);
    }

    int lca(int v, int w) {
        Node *x = lca(nodes[v], nodes[w]);
        return nullptr == x ? -1 : x->vertex;
    }
} *lct;

#define MAXN 100005

int N, M;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    lct = new LinkCutTreeLCA(N);
    string cmd;
    int a, b;
    FOR(i, M) {
        cin >> cmd;
        if (cmd == "link") {
            cin >> a >> b;
            a--; b--;
            lct->link(a, b);
        } else if (cmd == "cut") {
            cin >> a;
            a--;
            lct->cutParent(a);
        } else if (cmd == "lca") {
            cin >> a >> b;
            a--; b--;
            cout << lct->lca(a, b) + 1 << nl;
        } else {
            i--;
        }
    }
    return 0;
}
