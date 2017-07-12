/*
 * COCI14C2P6.cpp
 *
 *  Created on: Jul 11, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
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
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
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

#define MAXN 500000
#define MOD (int) (1e9)

inline int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

inline int sub(int a, int b) {
    return a - b >= 0 ? a - b : a - b + MOD;
}

inline int mul(int a, int b) {
    return (ll) a * b % MOD;
}

struct LazySegmentTree {
    struct Node {
        int range, len, minVal, maxVal, lenMin, lenMax, minMax, lenMinMax;
        int lazyLen = 0, lazyMin = 0, lazyMax = 0;

        void setLen(int val) {
            len = add(len, mul(val, range));
            lenMin = add(lenMin, mul(val, minVal));
            lenMax = add(lenMax, mul(val, maxVal));
            lenMinMax = add(lenMinMax, mul(val, minMax));
            lazyLen = add(lazyLen, val);
        }

        void setMin(int val) {
            minVal = mul(val, range);
            lenMin = mul(val, len);
            minMax = mul(val, maxVal);
            lenMinMax = mul(val, lenMax);
            lazyMin = val;
        }

        void setMax(int val) {
            maxVal = mul(val, range);
            lenMax = mul(val, len);
            minMax = mul(val, minVal);
            lenMinMax = mul(val, lenMin);
            lazyMax = val;
        }
    };

private:
    vector<Node> tree;
    int N;

    void propogate(int cur) {
        if (tree[cur].lazyLen != 0) {
            tree[cur * 2].setLen(tree[cur].lazyLen);
            tree[cur * 2 + 1].setLen(tree[cur].lazyLen);
            tree[cur].lazyLen = 0;
        }
        if (tree[cur].lazyMin != 0) {
            tree[cur * 2].setMin(tree[cur].lazyMin);
            tree[cur * 2 + 1].setMin(tree[cur].lazyMin);
            tree[cur].lazyMin = 0;
        }
        if (tree[cur].lazyMax != 0) {
            tree[cur * 2].setMax(tree[cur].lazyMax);
            tree[cur * 2 + 1].setMax(tree[cur].lazyMax);
            tree[cur].lazyMax = 0;
        }
    }

    void pushUp(int cur) {
        tree[cur].len = add(tree[cur * 2].len, tree[cur * 2 + 1].len);
        tree[cur].minVal = add(tree[cur * 2].minVal, tree[cur * 2 + 1].minVal);
        tree[cur].maxVal = add(tree[cur * 2].maxVal, tree[cur * 2 + 1].maxVal);
        tree[cur].lenMin = add(tree[cur * 2].lenMin, tree[cur * 2 + 1].lenMin);
        tree[cur].lenMax = add(tree[cur * 2].lenMax, tree[cur * 2 + 1].lenMax);
        tree[cur].minMax = add(tree[cur * 2].minMax, tree[cur * 2 + 1].minMax);
        tree[cur].lenMinMax = add(tree[cur * 2].lenMinMax, tree[cur * 2 + 1].lenMinMax);
    }

    void build(int cur, int cL, int cR) {
        tree[cur].range = cR - cL + 1;
        if (cL == cR) return;
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
    }

    void update(int cur, int cL, int cR, int l, int r, int val, int type) {
        if (cL != cR) propogate(cur);
        if (cL > r || cR < l) return;
        if (cL >= l && cR <= r) {
            if (type == 0) tree[cur].setLen(val);
            else if (type == 1) tree[cur].setMin(val);
            else tree[cur].setMax(val);
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, l, r, val, type);
        update(cur * 2 + 1, m + 1, cR, l, r, val, type);
        pushUp(cur);
    }

public:
    LazySegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log((double) size) / log(2.0))))) {
        build(1, 1, size);
        N = size;
    }

    void updateLen(int l, int r, int val) {
        update(1, 1, N, l, r, val, 0);
    }

    void updateMin(int l, int r, int val) {
        update(1, 1, N, l, r, val, 1);
    }

    void updateMax(int l, int r, int val) {
        update(1, 1, N, l, r, val, 2);
    }

    int query() {
        return tree[1].lenMinMax;
    }

    int size() {
        return N;
    }
} *st;

int N, val, ans = 0;

int main() {
    ri(N);
    st = new LazySegmentTree(N);
    stack<pii> lo;
    lo.push({-INT_INF, 0});
    stack<pii> hi;
    hi.push({INT_INF, 0});
    for (int i = 1; i <= N; i++) {
        ri(val);
        while (lo.top().f > val) {
            lo.pop();
        }
        while(hi.top().f < val) {
            hi.pop();
        }
        st->updateMin(lo.top().s + 1, i, val);
        st->updateMax(hi.top().s + 1, i, val);
        st->updateLen(1, i, 1);
        ans = add(ans, st->query());
        lo.push({val, i});
        hi.push({val, i});
    }
    printf("%d\n", ans);
    return 0;
}
