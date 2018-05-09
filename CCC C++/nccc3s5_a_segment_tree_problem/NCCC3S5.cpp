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
    ll cnt = 0, sum = 0, lazy = 0;
    bool del = false;
};

Node tree[MAXVAL * 4];

void propagate(int cur, int cL, int cR) {
    int m = cL + (cR - cL) / 2;
    if (tree[cur].lazy != 0 || tree[cur].del) {
        if (tree[cur].del) {
            tree[cur * 2].cnt = 0;
            tree[cur * 2].sum = 0;
            tree[cur * 2].lazy = 0;
        }
        tree[cur * 2].cnt += tree[cur].lazy * (m - cL + 1);
        tree[cur * 2].sum += tree[cur].lazy * (m - cL + 1) * (cL + m) / 2;
        tree[cur * 2].lazy += tree[cur].lazy;
        tree[cur * 2].del |= tree[cur].del;
        if (tree[cur].del) {
            tree[cur * 2 + 1].cnt = 0;
            tree[cur * 2 + 1].sum = 0;
            tree[cur * 2 + 1].lazy = 0;
        }
        tree[cur * 2 + 1].cnt += tree[cur].lazy * (cR - m);
        tree[cur * 2 + 1].sum += tree[cur].lazy * (cR - m) * (m + 1 + cR) / 2;
        tree[cur * 2 + 1].lazy += tree[cur].lazy;
        tree[cur * 2 + 1].del |= tree[cur].del;
        tree[cur].lazy = 0;
        tree[cur].del = false;
    }
}

void insert(int cur, int cL, int cR, int l, int r, ll cnt) {
    if (cL > r || cR < l) return;
    if (cL != cR) propagate(cur, cL, cR);
    if (cL >= l && cR <= r) {
        tree[cur].cnt += cnt * (cR - cL + 1);
        tree[cur].sum += cnt * (cR - cL + 1) * (cL + cR) / 2;
        tree[cur].lazy += cnt;
        return;
    }
    int m = cL + (cR - cL) / 2;
    insert(cur * 2, cL, m, l, r, cnt);
    insert(cur * 2 + 1, m + 1, cR, l, r, cnt);
    tree[cur].cnt = tree[cur * 2].cnt + tree[cur * 2 + 1].cnt;
    tree[cur].sum = tree[cur * 2].sum + tree[cur * 2 + 1].sum;
}

ll buyPrefixSum(int cur, int cL, int cR, ll k) {
    ll ret;
    if (cL != cR) propagate(cur, cL, cR);
    else {
        ret = min(tree[cur].cnt, k / cL);
        tree[cur].cnt -= ret;
        tree[cur].sum -= ret * cL;
        return ret;
    }
    int m = cL + (cR - cL) / 2;
    ll t = tree[cur * 2].sum;
    if (t > k) {
        ret = buyPrefixSum(cur * 2, cL, m, k);
    } else {
        ret = tree[cur * 2].cnt + buyPrefixSum(cur * 2 + 1, m + 1, cR, k - t);
        tree[cur * 2].cnt = 0;
        tree[cur * 2].sum = 0;
        tree[cur * 2].lazy = 0;
        tree[cur * 2].del = true;
    }
    tree[cur].cnt = tree[cur * 2].cnt + tree[cur * 2 + 1].cnt;
    tree[cur].sum = tree[cur * 2].sum + tree[cur * 2 + 1].sum;
    return ret;
}

ll buyPrefixCnt(int cur, int cL, int cR, ll k) {
    ll ret;
    if (cL != cR) propagate(cur, cL, cR);
    else {
        ret = cL * k;
        tree[cur].cnt -= k;
        tree[cur].sum -= ret;
        return ret;
    }
    int m = cL + (cR - cL) / 2;
    ll t = tree[cur * 2].cnt;
    if (t > k) {
        ret = buyPrefixCnt(cur * 2, cL, m, k);
    } else {
        ret = tree[cur * 2].sum + buyPrefixCnt(cur * 2 + 1, m + 1, cR, k - t);
        tree[cur * 2].cnt = 0;
        tree[cur * 2].sum = 0;
        tree[cur * 2].lazy = 0;
        tree[cur * 2].del = true;
    }
    tree[cur].cnt = tree[cur * 2].cnt + tree[cur * 2 + 1].cnt;
    tree[cur].sum = tree[cur * 2].sum + tree[cur * 2 + 1].sum;
    return ret;
}

ll buySuffixCnt(int cur, int cL, int cR, ll k) {
    ll ret;
    if (cL != cR) propagate(cur, cL, cR);
    else {
        ret = cL * k;
        tree[cur].cnt -= k;
        tree[cur].sum -= ret;
        return ret;
    }
    int m = cL + (cR - cL) / 2;
    ll t = tree[cur * 2 + 1].cnt;
    if (t > k) {
        ret = buySuffixCnt(cur * 2 + 1, m + 1, cR, k);
    } else {
        ret = tree[cur * 2 + 1].sum + buySuffixCnt(cur * 2, cL, m, k - t);
        tree[cur * 2 + 1].cnt = 0;
        tree[cur * 2 + 1].sum = 0;
        tree[cur * 2 + 1].lazy = 0;
        tree[cur * 2 + 1].del = true;
    }
    tree[cur].cnt = tree[cur * 2].cnt + tree[cur * 2 + 1].cnt;
    tree[cur].sum = tree[cur * 2].sum + tree[cur * 2 + 1].sum;
    return ret;
}

int queryPrefixCnt(int cur, int cL, int cR, ll k) {
    if (cL != cR) propagate(cur, cL, cR);
    else return cL;
    int m = cL + (cR - cL) / 2;
    ll t = tree[cur * 2].cnt;
    if (t > k) return queryPrefixCnt(cur * 2, cL, m, k);
    else return queryPrefixCnt(cur * 2 + 1, m + 1, cR, k - t);
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
            insert(1, 0, MAXVAL, a, a, c);
        } else if (cmd == "ADDRANGE") {
            cin >> a >> b;
            insert(1, 0, MAXVAL, a, b, 1);
        } else if (cmd == "BUYAMT") {
            cin >> c;
            cout << buyPrefixSum(1, 0, MAXVAL, c) << nl;
        } else if (cmd == "BUYLOW") {
            cin >> c;
            MIN(c, tree[1].cnt);
            cout << buyPrefixCnt(1, 0, MAXVAL, c) << nl;
        } else if (cmd == "BUYHIGH") {
            cin >> c;
            MIN(c, tree[1].cnt);
            cout << buySuffixCnt(1, 0, MAXVAL, c) << nl;
        } else if (cmd == "COST") {
            cin >> c;
            if (c > tree[1].cnt) cout << -1 << nl;
            else cout << queryPrefixCnt(1, 0, MAXVAL, c - 1) << nl;
        } else if (cmd == "NUMCONES") {
            cout << tree[1].cnt << nl;
        } else if (cmd == "TOTALCOST") {
            cout << tree[1].sum << nl;
        } else {
            i--;
        }
    }
    return 0;
}
