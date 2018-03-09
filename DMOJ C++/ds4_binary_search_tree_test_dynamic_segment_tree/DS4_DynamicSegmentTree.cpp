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

struct Node {
    Node *left = nullptr, *right = nullptr;
    int sz = 0;
};

void insert(Node *&cur, int cL, int cR, int val) {
    if (cL > val || cR < val) return;
    if (!cur) cur = new Node();
    if (cL == cR) {
       cur->sz++;
       return;
    }
    int m = cL + (cR - cL) / 2;
    insert(cur->left, cL, m, val);
    insert(cur->right, m + 1, cR, val);
    cur->sz = (cur->left ? cur->left->sz : 0) + (cur->right ? cur->right->sz : 0);
}

void erase(Node *cur, int cL, int cR, int val) {
    if (cL > val || cR < val) return;
    if (cL == cR) {
       if (cur->sz > 0) cur->sz--;
       return;
    }
    int m = cL + (cR - cL) / 2;
    if (cur->left) erase(cur->left, cL, m, val);
    if (cur->right) erase(cur->right, m + 1, cR, val);
    cur->sz = (cur->left ? cur->left->sz : 0) + (cur->right ? cur->right->sz : 0);
}

int getRank(Node *cur, int cL, int cR, int l, int r) {
    if (!cur || cL > r || cR < l) return 0;
    if (cL >= l && cR <= r) return cur->sz;
    int m = cL + (cR - cL) / 2;
    int left = getRank(cur->left, cL, m, l, r);
    int right = getRank(cur->right, m + 1, cR, l, r);
    return left + right;
}

bool contains(Node *cur, int cL, int cR, int val) {
    if (!cur || cL > val || cR < val) return false;
    if (cL == cR) return cur->sz > 0;
    int m = cL + (cR - cL) / 2;
    bool left = contains(cur->left, cL, m, val);
    bool right = contains(cur->right, m + 1, cR, val);
    return left || right;
}

int select(Node *cur, int cL, int cR, int k) {
    if (cL == cR) return cL;
    int t = cur->left ? cur->left->sz : 0;
    int m = cL + (cR - cL) / 2;
    if (t > k) return select(cur->left, cL, m, k);
    else return select(cur->right, m + 1, cR, k - t);
}

void print(Node *cur, int cL, int cR) {
    if (!cur) return;
    if (cL == cR) {
        for (int i = 0; i < cur->sz; i++) cout << cL << sp;
        return;
    }
    int m = cL + (cR - cL) / 2;
    print(cur->left, cL, m);
    print(cur->right, m + 1, cR);
}

int N, M, a;
Node *root = new Node();

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    FOR(i, N) {
        cin >> a;
        insert(root, 1, 1e9, a);
    }
    int lastAns = 0;
    FOR(i, M) {
        char op;
        int x;
        cin >> op >> x;
        x = x ^ lastAns;
        if (op == 'I') {
            insert(root, 1, 1e9, x);
        } else if (op == 'R') {
            erase(root, 1, 1e9, x);
        } else if (op == 'S') {
            lastAns = select(root, 1, 1e9, x - 1);
            cout << lastAns << nl;
        } else if (op == 'L') {
            int k = contains(root, 1, 1e9, x) ? getRank(root, 1, 1e9, 1, x - 1) : -1;
            lastAns = k == -1 ? -1 : k + 1;
            cout << lastAns << nl;
        } else {
            i--;
        }
    }
    print(root, 1, 1e9);
    return 0;
}
