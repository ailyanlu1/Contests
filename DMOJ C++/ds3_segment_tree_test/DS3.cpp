/*
 * DS3.cpp
 *
 *  Created on: Jul 5, 2017
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

int gcd(int a, int b) {
    return b == 0 ? a : gcd (b, a % b);
}

struct SegmentTree {
    struct Node {
        int gcd = 0, cnt = 0, min = INT_MAX;
    };

private:
    vector<Node> tree;
    int N;
    int *array;

    void build(int cur, int cL, int cR) {
        if (cL == cR) {
            tree[cur].min = array[cL];
            tree[cur].gcd = array[cL];
            tree[cur].cnt = 1;
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
        tree[cur].min = min(tree[cur * 2].min, tree[cur * 2 + 1].min);
        tree[cur].gcd = gcd(tree[cur * 2].gcd, tree[cur * 2 + 1].gcd);
        tree[cur].cnt = 0;
        if (tree[cur].gcd == tree[cur * 2].gcd) tree[cur].cnt += tree[cur * 2].cnt;
        if (tree[cur].gcd == tree[cur * 2 + 1].gcd) tree[cur].cnt += tree[cur * 2 + 1].cnt;
    }

    void update(int cur, int cL, int cR, int ind, int val) {
        if (cL > ind || cR < ind) return;
        if (cL >= ind && cR <= ind) {
            tree[cur].min = val;
            tree[cur].gcd = val;
            tree[cur].cnt = 1;
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, ind, val);
        update(cur * 2 + 1, m + 1, cR, ind, val);
        tree[cur].min = min(tree[cur * 2].min, tree[cur * 2 + 1].min);
        tree[cur].gcd = gcd(tree[cur * 2].gcd, tree[cur * 2 + 1].gcd);
        tree[cur].cnt = 0;
        if (tree[cur].gcd == tree[cur * 2].gcd) tree[cur].cnt += tree[cur * 2].cnt;
        if (tree[cur].gcd == tree[cur * 2 + 1].gcd) tree[cur].cnt += tree[cur * 2 + 1].cnt;
    }

    int minQuery(int cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) return INT_MAX;
        if (cL >= l && cR <= r) return tree[cur].min;
        int m = cL + (cR - cL) / 2;
        int left = minQuery(cur * 2, cL, m, l, r);
        int right = minQuery(cur * 2 + 1, m + 1, cR, l, r);
        return min(left, right);
    }

    pii gcdQuery(int cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) return {0, 0};
        if (cL >= l && cR <= r) return {tree[cur].gcd, tree[cur].cnt};
        int m = cL + (cR - cL) / 2;
        pii left = gcdQuery(cur * 2, cL, m, l, r);
        pii right = gcdQuery(cur * 2 + 1, m + 1, cR, l, r);
        int GCD = gcd(left.f, right.f);
        int cnt = 0;
        if (GCD == left.f) cnt += left.s;
        if (GCD == right.f) cnt += right.s;
        return {GCD, cnt};
    }

public:
    SegmentTree(int size, int *arr, bool oneIndexed): tree((int) (2 * pow(2.0, ceil(log((double) size) / log(2.0))))) {
        array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = arr[i - !oneIndexed];
        }
        build(1, 1, size);
        N = size;
    }

    SegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log((double) size) / log(2.0))))) {
        array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = 0;
        }
        build(1, 1, size);
        N = size;
    }

    void update(int ind, int val) {
        update(1, 1, N, ind, val);
    }

    int minQuery(int l, int r) {
        return minQuery(1, 1, N, l, r);
    }

    pii gcdQuery(int l, int r) {
        return gcdQuery(1, 1, N, l, r);
    }

    int size() {
        return N;
    }
} *st;

#define MAXN 100000

int N, M, arr[MAXN], x, y;
char op;

int main() {
    ri(N);
    ri(M);
    for (int i = 0; i < N; i++) {
        ri(arr[i]);
    }
    st = new SegmentTree(N, arr, false);
    for (int i = 0; i < M; i++) {
        rc(op);
        ri(x);
        ri(y);
        if (op == 'C') {
            st->update(x, y);
        } else if (op =='M') {
            printf("%d\n", st->minQuery(x, y));
        } else if (op == 'G') {
            printf("%d\n", st->gcdQuery(x, y).f);
        } else if (op == 'Q') {
            printf("%d\n", st->gcdQuery(x, y).s);
        } else {
            i--;
        }
    }
    return 0;
}
