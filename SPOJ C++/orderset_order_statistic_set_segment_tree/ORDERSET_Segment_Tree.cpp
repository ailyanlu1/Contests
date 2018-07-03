// http://www.spoj.com/problems/ORDERSET/
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

template <typename T>
struct OrderStatisticSegmentTree {
private:
    struct Node {
        Node *left = nullptr, *right = nullptr;
        int sz = 0;
    };

    T MAXVAL;
    Node *root = nullptr;

    void insert(Node *&cur, T cL, T cR, T val) {
        if (cL > val || cR < val) return;
        if (!cur) cur = new Node();
        if (cL == cR) {
           cur->sz++;
           return;
        }
        T m = cL + (cR - cL) / 2;
        insert(cur->left, cL, m, val);
        insert(cur->right, m + 1, cR, val);
        cur->sz = (cur->left ? cur->left->sz : 0) + (cur->right ? cur->right->sz : 0);
    }

    void erase(Node *cur, T cL, T cR, T val) {
        if (cL > val || cR < val) return;
        if (cL == cR) {
           if (cur->sz > 0) cur->sz--;
           return;
        }
        T m = cL + (cR - cL) / 2;
        if (cur->left) erase(cur->left, cL, m, val);
        if (cur->right) erase(cur->right, m + 1, cR, val);
        cur->sz = (cur->left ? cur->left->sz : 0) + (cur->right ? cur->right->sz : 0);
    }

    bool contains(Node *cur, T cL, T cR, T val) {
        if (!cur || cL > val || cR < val) return false;
        if (cL == cR) return cur->sz > 0;
        T m = cL + (cR - cL) / 2;
        return contains(cur->left, cL, m, val) || contains(cur->right, m + 1, cR, val);
    }

    int getRank(Node *cur, T cL, T cR, T l, T r) {
        if (!cur || cL > r || cR < l) return 0;
        if (cL >= l && cR <= r) return cur->sz;
        T m = cL + (cR - cL) / 2;
        return getRank(cur->left, cL, m, l, r) + getRank(cur->right, m + 1, cR, l, r);
    }

    T select(Node *cur, T cL, T cR, int k) {
        if (cL == cR) return cL;
        int t = cur->left ? cur->left->sz : 0;
        T m = cL + (cR - cL) / 2;
        if (t > k) return select(cur->left, cL, m, k);
        else return select(cur->right, m + 1, cR, k - t);
    }

    void values(Node *cur, T cL, T cR, vector<T> &queue) {
        if (!cur) return;
        if (cL == cR) {
            for (int i = 0; i < cur->sz; i++) queue.push_back(cL);
            return;
        }
        T m = cL + (cR - cL) / 2;
        values(cur->left, cL, m, queue);
        values(cur->right, m + 1, cR, queue);
    }

    void clear(Node *cur) {
        if (!cur) return;
        clear(cur->left);
        clear(cur->right);
        delete cur;
    }

public:
    OrderStatisticSegmentTree(T MAXVAL) : MAXVAL(MAXVAL) {}

    ~OrderStatisticSegmentTree() {
        clear(root);
        root = nullptr;
    }

    void insert(T val) {
        insert(root, 0, MAXVAL, val);
    }

    void erase(T val) {
        erase(root, 0, MAXVAL, val);
    }

    bool contains(T val) {
        return contains(root, 0, MAXVAL, val);
    }

    int getRank(T val) {
        return getRank(root, 0, MAXVAL, 0, val - 1);
    }

    T select(int k) {
        if (!root || k < 0 || k >= root->sz) throw invalid_argument("k is not in range 0 to size");
        return select(root, 0, MAXVAL, k);
    }

    vector<T> values() {
        vector<T> queue;
        values(root, 0, MAXVAL, queue);
        return queue;
    }

    bool isEmpty() {
        return !root || root->sz == 0;
    }

    int size() {
        return root ? root->sz : 0;
    }

    void clear() {
        clear();
    }
};

const int MAXVAL = 1e9 + 5;

int Q;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> Q;
    OrderStatisticSegmentTree<int> T(MAXVAL * 2);
    char op;
    int x;
    FOR(i, Q) {
        cin >> op >> x;
        switch (op) {
        case 'I':
            x += MAXVAL;
            if (!T.contains(x)) T.insert(x);
            break;
        case 'D':
            x += MAXVAL;
            if (T.contains(x)) T.erase(x);
            break;
        case 'K':
            if (x > sz(T)) cout << "invalid" << nl;
            else cout << T.select(x - 1) - MAXVAL << nl;
            break;
        case 'C':
            x += MAXVAL;
            cout << T.getRank(x) << nl;
            break;
        default:
            i--;
            break;
        }
    }
    return 0;
}
