// http://codeforces.com/contest/948/problem/C
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

template <typename Value, typename Comparator = less<Value>>
struct IncrementalSkewHeap {
private:
    Comparator cmp;

    struct Node {
        Value val;
        Node *left = nullptr, *right = nullptr;
        Value delta = 0;
        Node (Value val) : val(val) {}
    };

    int sz = 0;
    Node *root = nullptr;

    void propagate(Node *a) {
        a->val += a->delta;
        if (nullptr != a->left) a->left->delta += a->delta;
        if (nullptr != a->right) a->right->delta += a->delta;
        a->delta = 0;
    }

    Node *merge(Node *a, Node *b) {
        if (nullptr == a || nullptr == b) return nullptr == a ? b : a;
        propagate(a);
        propagate(b);
        if (cmp(a->val, b->val)) swap(a, b);
        a->right = merge(b, a->right);
        swap(a->left, a->right);
        return a;
    }

public:
    IncrementalSkewHeap() {}

    bool isEmpty() {
        return nullptr == root;
    }

    Value top() {
        propagate(root);
        return root->val;
    }

    Value pop() {
        propagate(root);
        Value ret = root->val;
        Node *temp = root;
        root = merge(root->left, root->right);
        delete(temp);
        sz--;
        return ret;
    }

    void push(Value val) {
        Node *x = new Node(val);
        root = merge(root, x);
        sz++;
    }

    void increment(Value delta) {
        if (nullptr != root) root->delta += delta;
    }

    void merge(IncrementalSkewHeap &h) {
        root = merge(root, h.root);
        sz += h.sz;
    }

    int size() {
        return sz;
    }
};

int N;
ll V[100005], T[100005];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    IncrementalSkewHeap<ll, greater<int>> heap;
    FOR(i, N) cin >> V[i];
    FOR(i, N) cin >> T[i];
    FOR(i, N) {
        ll sum = 0;
        heap.push(V[i]);
        while (!heap.isEmpty() && heap.top() - T[i] <= 0) sum += heap.pop();
        heap.increment(-T[i]);
        sum += heap.size() * T[i];
        cout << sum << " \n"[i == N - 1];
    }
    return 0;
}
