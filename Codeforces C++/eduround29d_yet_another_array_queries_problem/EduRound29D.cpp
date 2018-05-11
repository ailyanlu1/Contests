// http://codeforces.com/contest/863/problem/D
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
    int val;
    double priority;
    int size;
    bool rev = 0;
    Node *left = nullptr, *right = nullptr;
    Node (int val, double priority, int size) : val(val), priority(priority), size(size) {}
};

int size(Node *x) {
    return x ? x->size : 0;
}

void update(Node *x) {
    if (x) x->size = 1 + size(x->left) + size(x->right);
}

void push(Node *x) {
    if (x && x->rev) {
        x->rev = 0;
        swap(x->left, x->right);
        if (x->left) x->left->rev ^= 1;
        if (x->right) x->right->rev ^= 1;
    }
}

void merge(Node *&x, Node *l, Node *r) {
    push(l);
    push(r);
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

void split(Node *x, Node *&l, Node *&r, int ind, int add = 0) {
    if (!x) {
        l = r = nullptr;
        return;
    }
    push(x);
    int curInd = size(x->left) + add;
    if (ind <= curInd) {
        split(x->left, l, x->left, ind, add);
        r = x;
    } else {
        split(x->right, x->right, r, ind, curInd + 1);
        l = x;
    }
    update(x);
}

void reverse(Node *x, int l, int r) {
    Node *left = nullptr, *right = nullptr, *mid = nullptr;
    split(x, left, mid, l);
    split(mid, mid, right, r - l + 1);
    mid->rev ^= 1;
    merge(x, left, mid);
    merge(x, x, right);
}

void rotateRight(Node *x, int l, int r) {
    Node *left = nullptr, *right = nullptr, *mid = nullptr, *end = nullptr;
    split(x, left, mid, l);
    split(mid, mid, right, r - l + 1);
    split(mid, mid, end, r - l);
    merge(x, left, end);
    merge(x, x, mid);
    merge(x, x, right);
}

int getValue(Node *x, int i) {
    Node *left = nullptr, *right = nullptr, *mid = nullptr;
    split(x, left, mid, i);
    split(mid, mid, right, 1);
    int ret = mid->val;
    merge(x, left, mid);
    merge(x, x, right);
    return ret;
}

Node *root = nullptr;
int N, M, Q;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> Q >> M;
    int t, a, b;
    FOR(i, N) {
        cin >> a;
        merge(root, root, new Node(a, dis(rng), 1));
    }
    FOR(i, Q) {
        cin >> t >> a >> b;
        a--; b--;
        if (t == 1) rotateRight(root, a, b);
        else reverse(root, a, b);
    }
    FOR(i, M) {
        cin >> a;
        a--;
        cout << getValue(root, a) << sp;
    }
    cout << nl;
    return 0;
}
