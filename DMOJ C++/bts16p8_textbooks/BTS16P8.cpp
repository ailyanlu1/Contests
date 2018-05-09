/*
 * BTS16P8.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf("%c", &x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

struct LazySegmentTree {
    struct Node {
        int val, lazy;
    };

public:
    vector<Node> tree;

private:
    int N;
    // int *array;

    void propagate(int cur) {
        if (tree[cur].lazy != 0) {
            tree[cur * 2].val = max(tree[cur].lazy, tree[cur * 2].lazy);
            tree[cur * 2].lazy = tree[cur].lazy;
            tree[cur * 2 + 1].val = max(tree[cur].lazy, tree[cur * 2 + 1].lazy);
            tree[cur * 2 + 1].lazy = tree[cur].lazy;
            tree[cur].lazy = 0;
        }
    }

    void build(int cur, int cL, int cR) {
        if (cL == cR) {
            tree[cur].val = /*array[cL]*/0;
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
    }

    void update(int cur, int cL, int cR, int l, int r, int val) {
        if (cL != cR) propagate(cur);
        if (cL > r || cR < l) return;
        if (cL >= l && cR <= r) {
            tree[cur].val = val;
            tree[cur].lazy = val;
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, l, r, val);
        update(cur * 2 + 1, m + 1, cR, l, r, val);
        tree[cur].val = max(tree[cur * 2].val, tree[cur * 2 + 1].val);
    }

    int rMaxQ(int cur, int cL, int cR, int l, int r) {
        if (cL != cR) propagate(cur);
        if (cL > r || cR < l) return INT_MIN;
        if (cL >= l && cR <= r) return tree[cur].val;
        int m = cL + (cR - cL) / 2;
        int left = rMaxQ(cur * 2, cL, m, l, r);
        int right = rMaxQ(cur * 2 + 1, m + 1, cR, l, r);
        return max(left, right);
    }

public:
    /*LazySegmentTree(int size, int *arr, bool oneIndexed): tree(4 * size) {
        array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = arr[i - !oneIndexed];
        }
        build(1, 1, size);
        N = size;
    }*/

    LazySegmentTree(int size): tree(4 * size) {
        /*array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = 0;
        }*/
        build(1, 1, size);
        N = size;
    }

    void update(int l, int r, int val) {
        update(1, 1, N, l, r, val);
    }

    int rMaxQ(int l, int r) {
        return rMaxQ(1, 1, N, l, r);
    }

    int size() {
        return N;
    }
};

#define MAXN 500000
#define MOD 1000000007

struct Book {
    int l, r, w;
} books[MAXN + 1];

int N, cnt;
ll ans;
set<int> all;
umii ind;
vector<int> pos;

int main() {
    ri(N);
    for (int i = 1; i <= N; i++) {
        int s, l, w;
        ri(s);
        ri(l);
        ri(w);
        ans -= 1ll * l * w;
        books[i] = {s, s + l, w};
        all.insert(books[i].l);
        all.insert(books[i].r);
    }
    for (int a: all) {
        ind[a] = cnt++;
        pos.pb(a);
    }
    LazySegmentTree st(cnt);
    for (int i = 1; i <= N; i++) {
        int left = ind[books[i].l] + 1;
        int right = ind[books[i].r];
        st.update(left, right, st.rMaxQ(left, right) + books[i].w);
    }
    for (int i = 1; i < cnt; i++) {
        ans += 1ll * st.rMaxQ(i, i) * (pos[i] - pos[i - 1]);
    }
    printf("%lld\n", ans % MOD);
    return 0;
}
