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

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

const int MAXVAL = 2e6 + 5;

struct Node {
    Node *left = nullptr, *right = nullptr;
    ll cnt = 0, sum = 0, lazy = 0;
    bool del = false;
};

Node *root = new Node();

void propagate(Node *cur, int cL, int cR) {
    int m = cL + (cR - cL) / 2;
    if (cur->lazy != 0 || cur->del) {
        if (!cur->left) cur->left = new Node();
        if (cur->del) {
            cur->left->cnt = 0;
            cur->left->sum = 0;
            cur->left->lazy = 0;
        }
        cur->left->cnt += cur->lazy * (m - cL + 1);
        cur->left->sum += cur->lazy * (m - cL + 1) * (cL + m) / 2;
        cur->left->lazy += cur->lazy;
        cur->left->del |= cur->del;
        if (!cur->right) cur->right = new Node();
        if (cur->del) {
            cur->right->cnt = 0;
            cur->right->sum = 0;
            cur->right->lazy = 0;
        }
        cur->right->cnt += cur->lazy * (cR - m);
        cur->right->sum += cur->lazy * (cR - m) * (m + 1 + cR) / 2;
        cur->right->lazy += cur->lazy;
        cur->right->del |= cur->del;
        cur->lazy = 0;
        cur->del = false;
    }
}

void insert(Node *cur, int cL, int cR, int l, int r, ll cnt) {
    if (cL > r || cR < l) return;
    if (cL != cR) propagate(cur, cL, cR);
    if (cL >= l && cR <= r) {
        cur->cnt += cnt * (cR - cL + 1);
        cur->sum += cnt * (cR - cL + 1) * (cL + cR) / 2;
        cur->lazy += cnt;
        return;
    }
    int m = cL + (cR - cL) / 2;
    if (!cur->left) cur->left = new Node();
    insert(cur->left, cL, m, l, r, cnt);
    if (!cur->right) cur->right = new Node();
    insert(cur->right, m + 1, cR, l, r, cnt);
    cur->cnt = cur->left->cnt + cur->right->cnt;
    cur->sum = cur->left->sum + cur->right->sum;
}

ll buyPrefixSum(Node *cur, int cL, int cR, ll k) {
    ll ret;
    if (cL != cR) propagate(cur, cL, cR);
    else {
        ret = min(cur->cnt, k / cL);
        cur->cnt -= ret;
        cur->sum -= ret * cL;
        return ret;
    }
    int m = cL + (cR - cL) / 2;
    if (!cur->left) cur->left = new Node();
    if (!cur->right) cur->right = new Node();
    ll t = cur->left->sum;
    if (t > k) {
        ret = buyPrefixSum(cur->left, cL, m, k);
    } else {
        ret = cur->left->cnt + buyPrefixSum(cur->right, m + 1, cR, k - t);
        cur->left->cnt = 0;
        cur->left->sum = 0;
        cur->left->lazy = 0;
        cur->left->del = true;
    }
    cur->cnt = cur->left->cnt + cur->right->cnt;
    cur->sum = cur->left->sum + cur->right->sum;
    return ret;
}

ll buyPrefixCnt(Node *cur, int cL, int cR, ll k) {
    ll ret;
    if (cL != cR) propagate(cur, cL, cR);
    else {
        ret = cL * k;
        cur->cnt -= k;
        cur->sum -= ret;
        return ret;
    }
    int m = cL + (cR - cL) / 2;
    if (!cur->left) cur->left = new Node();
    if (!cur->right) cur->right = new Node();
    ll t = cur->left->cnt;
    if (t > k) {
        ret = buyPrefixCnt(cur->left, cL, m, k);
    } else {
        ret = cur->left->sum + buyPrefixCnt(cur->right, m + 1, cR, k - t);
        cur->left->cnt = 0;
        cur->left->sum = 0;
        cur->left->lazy = 0;
        cur->left->del = true;
    }
    cur->cnt = cur->left->cnt + cur->right->cnt;
    cur->sum = cur->left->sum + cur->right->sum;
    return ret;
}

ll buySuffixCnt(Node *cur, int cL, int cR, ll k) {
    ll ret;
    if (cL != cR) propagate(cur, cL, cR);
    else {
        ret = cL * k;
        cur->cnt -= k;
        cur->sum -= ret;
        return ret;
    }
    int m = cL + (cR - cL) / 2;
    if (!cur->left) cur->left = new Node();
    if (!cur->right) cur->right = new Node();
    ll t = cur->right->cnt;
    if (t > k) {
        ret = buySuffixCnt(cur->right, m + 1, cR, k);
    } else {
        ret = cur->right->sum + buySuffixCnt(cur->left, cL, m, k - t);
        cur->right->cnt = 0;
        cur->right->sum = 0;
        cur->right->lazy = 0;
        cur->right->del = true;
    }
    cur->cnt = cur->left->cnt + cur->right->cnt;
    cur->sum = cur->left->sum + cur->right->sum;
    return ret;
}

int queryPrefixCnt(Node *cur, int cL, int cR, ll k) {
    if (cL != cR) propagate(cur, cL, cR);
    else return cL;
    int m = cL + (cR - cL) / 2;
    ll t = cur->left ? cur->left->cnt : 0;
    if (t > k) return queryPrefixCnt(cur->left, cL, m, k);
    else return queryPrefixCnt(cur->right, m + 1, cR, k - t);
}

int N;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    string cmd;
    int a, b;
    ll c;
    FOR(i, N) {
        cin >> cmd;
        if (cmd == "ADD") {
            cin >> c >> a;
            insert(root, 0, MAXVAL, a, a, c);
        } else if (cmd == "ADDRANGE") {
            cin >> a >> b;
            insert(root, 0, MAXVAL, a, b, 1);
        } else if (cmd == "BUYAMT") {
            cin >> c;
            cout << buyPrefixSum(root, 0, MAXVAL, c) << nl;
        } else if (cmd == "BUYLOW") {
            cin >> c;
            MIN(c, root->cnt);
            cout << buyPrefixCnt(root, 0, MAXVAL, c) << nl;
        } else if (cmd == "BUYHIGH") {
            cin >> c;
            MIN(c, root->cnt);
            cout << buySuffixCnt(root, 0, MAXVAL, c) << nl;
        } else if (cmd == "COST") {
            cin >> c;
            if (c > root->cnt) cout << -1 << nl;
            else cout << queryPrefixCnt(root, 0, MAXVAL, c - 1) << nl;
        } else if (cmd == "NUMCONES") {
            cout << root->cnt << nl;
        } else if (cmd == "TOTALCOST") {
            cout << root->sum << nl;
        } else {
            i--;
        }
    }
    return 0;
}
