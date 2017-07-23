/*
 * JOI14P2.cpp
 *
 *  Created on: Jul 21, 2017
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

#define MAXNK 200000

struct FenwickTree {
private:
    int size;
    int *array;

public:
    FenwickTree(int size) {
        this->size = size;
        array = new int[size + 1];
        for (int i = 0; i <= size; i++) {
            array[i] = 0;
        }
    }

    /**
     * Range Sum query from 1 to ind
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind index
     * @return sum
     */
    int rsq(int ind) {
        int sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    /**
     * Range Sum Query from a to b.
     * Search for the sum from array index from a to b
     * a and b are 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  a left index
     * @param  b right index
     * @return sum
     */
    int rsq(int a, int b) {
        return rsq(b) - rsq(a - 1);
    }

    /**
     * Update the array at ind and all the affected regions above ind.
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind   index
     * @param  value value
     */
    void update(int ind, int value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    int getSize() {
        return size;
    }
};

pii T[MAXNK + 2];

struct SegmentTree {
    struct Node {
        int val = 0;
    };

private:
    vector<Node> tree;
    int N;

    void build(int cur, int cL, int cR) {
        if (cL == cR) {
            tree[cur].val = T[cL].s;
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
        tree[cur].val = max(tree[cur * 2].val, tree[cur * 2 + 1].val);
    }

    void update(int cur, int cL, int cR, int ind, int val) {
        if (cL > ind || cR < ind) return;
        if (cL >= ind && cR <= ind) {
            tree[cur].val += val;
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, ind, val);
        update(cur * 2 + 1, m + 1, cR, ind, val);
        tree[cur].val = max(tree[cur * 2].val, tree[cur * 2 + 1].val);
    }

    int query(int cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) return 0;
        if (cL >= l && cR <= r) return tree[cur].val;
        int m = cL + (cR - cL) / 2;
        int left = query(cur * 2, cL, m, l, r);
        int right = query(cur * 2 + 1, m + 1, cR, l, r);
        return max(left, right);
    }

public:
    SegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log((double) size) / log(2.0))))) {
        build(1, 1, size);
        N = size;
    }

    void update(int ind, int val) {
        update(1, 1, N, ind, val);
    }

    int query(int l, int r) {
        return query(1, 1, N, l, r);
    }

    int size() {
        return N;
    }
};

int lowerBoundInd(pii a[], int start, int end, int key) {
    int lo = start;
    int hi = end;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (key <= a[mid].f) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

struct Card {
    int A, B, MIN, MAX;
    Card() {}
    Card(int A, int B) {
        this->A = A;
        this->B = B;
        this->MIN = min(A, B);
        this->MAX = max(A, B);
    }

    bool operator < (const Card &c) const {
        return MAX < c.MAX;
    }
};

int N, K, a, b;
Card C[MAXNK + 1];
FenwickTree *ft;
SegmentTree *st;
int cur = 1;
ll sum = 0LL;

int main() {
    ri(N);
    ri(K);
    for (int i = 1; i <= N; i++) {
        ri(a);
        ri(b);
        C[i] = Card(a, b);
    }
    sort(C + 1, C + N + 1);
    ft = new FenwickTree(K);
    for (int i = 1; i <= K; i++) {
        ri(T[i].f);
        T[i].s = i;
        ft->update(i, 1);
    }
    sort(T + 1, T + K + 1);
    T[K + 1] = {INT_INF, K + 1};
    st = new SegmentTree(K + 1);
    for (int i = 1; i <= N; i++) {
        for ( ; cur <= K && T[cur].f < C[i].MAX; cur++) {
            ft->update(T[cur].s, 1);
        }
        int maxT = st->query(lowerBoundInd(T, 1, K + 2, C[i].MIN), lowerBoundInd(T, 1, K + 2, C[i].MAX) - 1);
        bool flipped = (ft->rsq(K) - ft->rsq(maxT)) % 2 != 0;
        if (maxT == 0) {
            if (flipped) sum += C[i].B;
            else sum += C[i].A;
        } else {
            if (flipped) sum += C[i].MIN;
            else sum += C[i].MAX;
        }
    }
    printf("%lld\n", sum);
    return 0;
}
