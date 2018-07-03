// http://codeforces.com/contest/707/problem/D
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

#define MAXQ 100005

int N, M, K, Q;

struct Node {
public:
    Node *left = nullptr;
    Node *right = nullptr;
    int val = 0;
    bool flip = false;

    Node() {}

    Node(Node *n) : left(n->left), right(n->right), val(n->val), flip(n->flip) {}
};

Node *nodes[MAXQ];

Node *build(int cL, int cR) {
    if (cL == cR) return new Node();
    int m = cL + (cR - cL) / 2;
    Node *ret = new Node();
    ret->left = build(cL, m);
    ret->right = build(m + 1, cR);
    return ret;
}

Node *update(Node *cur, int cL, int cR, int ind, int val, bool flip) {
    if (cL > ind || cR < ind) return cur;
    flip ^= cur->flip;
    Node *ret = new Node(cur);
    if (cL == cR) {
        if (flip) ret->val = 1 - val;
        else ret->val = val;
        return ret;
    }
    int m = cL + (cR - cL) / 2;
    if (ret->left == nullptr) ret->left = new Node();
    if (ret->right == nullptr) ret->right = new Node();
    ret->left = update(ret->left, cL, m, ind, val, flip);
    ret->right = update(ret->right, m + 1, cR, ind, val, flip);
    ret->val = 0;
    if (ret->left->flip) ret->val += (m - cL + 1) - ret->left->val;
    else ret->val += ret->left->val;
    if (ret->right->flip) ret->val += (cR - m) - ret->right->val;
    else ret->val += ret->right->val;
    return ret;
}

Node *flipRange(Node *cur, int cL, int cR, int l, int r) {
    if (cL > r || cR < l) return cur;
    Node *ret = new Node(cur);
    if (cL >= l && cR <= r) {
        ret->flip = !ret->flip;
        return ret;
    }
    int m = cL + (cR - cL) / 2;
    if (ret->left == nullptr) ret->left = new Node();
    if (ret->right == nullptr) ret->right = new Node();
    ret->left = flipRange(ret->left, cL, m, l, r);
    ret->right = flipRange(ret->right, m + 1, cR, l, r);
    ret->val = 0;
    if (ret->left->flip) ret->val += (m - cL + 1) - ret->left->val;
    else ret->val += ret->left->val;
    if (ret->right->flip) ret->val += (cR - m) - ret->right->val;
    else ret->val += ret->right->val;
    return ret;
}

int query(Node *root, int cL, int cR) {
    if (root->flip) return (cR - cL + 1) - root->val;
    else return root->val;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> Q;
    K = N * M;
    nodes[0] = build(0, K - 1);
    int t, a, b;
    For(i, 1, Q + 1) {
        cin >> t;
        if (t == 1) {
            cin >> a >> b;
            int ind = (a - 1) * M + (b - 1);
            nodes[i] = update(nodes[i - 1], 0, K - 1, ind, 1, false);
        } else if (t == 2) {
            cin >> a >> b;
            int ind = (a - 1) * M + (b - 1);
            nodes[i] = update(nodes[i - 1], 0, K - 1, ind, 0, false);
        } else if (t == 3) {
            cin >> a;
            int l = (a - 1) * M;
            int r = l + M - 1;
            nodes[i] = flipRange(nodes[i - 1], 0, K - 1, l, r);
        } else {
            cin >> a;
            nodes[i] = nodes[a];
        }
        cout << query(nodes[i], 0, K - 1) << nl;
    }
    return 0;
}
