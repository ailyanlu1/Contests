#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define f first
#define s second
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl "\n"

#define ll long long
#define ld long double
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

template <typename Value, typename Comparator = less<Value>>
struct AVLTreeSet {
private:
    Comparator cmp;

    struct Node {
        Value val;
        int height;
        Node *left = nullptr, *right = nullptr;
        Node(Value val, int height) {
            this->val = val;
            this->height = height;
        }
    };

    Node *root = nullptr;

    int height(Node *&x) {
        if (x == nullptr) return -1;
        return x->height;
    }

    void update(Node *&x) {
        x->height = 1 + max(height(x->left), height(x->right));
    }

    Node *add(Node *&x, Value val) {
        if (x == nullptr) return new Node(val, 0);
        if (cmp(val, x->val)) x->left = add(x->left, val);
        else if (cmp(x->val, val)) x->right = add(x->right, val);
        update(x);
        return x;
    }

    int sumHeights(Node *&x) {
        if (x == nullptr) return 0;
        return sumHeights(x->left) + x->height + sumHeights(x->right);
    }

public:
    AVLTreeSet() {}

    int height() {
        return height(root);
    }

    void add(Value val) {
        root = add(root, val);
    }

    int sumHeights() {
        return sumHeights(root);
    }
};

int N;
AVLTreeSet<int> bst;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int a;
    FOR(i, N) {
        cin >> a;
        bst.add(a);
    }
    cout << bst.height() << nl;
    cout << bst.sumHeights() << nl;
    return 0;
}
