/*
 * Segments.cpp
 *
 *  Created on: Jun 19, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

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
        int l, r, maxVal, lazy;
    };

private:
    vector<Node> tree;
    int N;
    int *array;

    void propogate(int cur) {
        if (tree[cur].lazy != 0) {
            tree[l(cur)].maxVal += tree[cur].lazy;
            tree[l(cur)].lazy += tree[cur].lazy;
            tree[r(cur)].maxVal += tree[cur].lazy;
            tree[r(cur)].lazy += tree[cur].lazy;
            tree[cur].lazy = 0;
        }
    }

    void build(int cur, int l, int r) {
        tree[cur].l = l;
        tree[cur].r = r;
        if (l == r) {
            // tree[cur].maxVal = array[l];
            return;
        }
        int m = mid(l, r);
        build(l(cur), l , m);
        build(r(cur), m + 1, r);
    }

    void update(int cur, int l, int r, int val) {
        if (tree[cur].l != tree[cur].r) propogate(cur);
        if (tree[cur].l > r || tree[cur].r < l) return;
        if (tree[cur].l >= l && tree[cur].r <= r) {
            tree[cur].maxVal += val;
            tree[cur].lazy += val;
            return;
        }
        update(l(cur), l, r, val);
        update(r(cur), l, r, val);
        tree[cur].maxVal = max(tree[l(cur)].maxVal, tree[r(cur)].maxVal);
    }

    int rMaxQ(int cur, int l, int r) {
        if (tree[cur].l != tree[cur].r) propogate(cur);
        if (tree[cur].l > r || tree[cur].r < l) return 0;
        if (tree[cur].l >= l && tree[cur].r <= r) return tree[cur].maxVal;;
        int left = rMaxQ(l(cur), l, r);
        int right = rMaxQ(r(cur), l, r);
        return max(left, right);
    }

public:
    LazySegmentTree(int size, int *arr): tree(4 * size) {
        array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = arr[i - 1];
        }
        build(1, 1, size);
        N = size;
    }

    LazySegmentTree(int size): tree(4 * size) {
        array = new int[size + 1];
        /*for (int i = 1; i <= size; i++) {
            array[i] = 0;
        }*/
        build(1, 1, size);
        N = size;
    }

    void update(int l, int r, int val) {
        update(1, l, r, val);
    }

    int rMaxQ(int l, int r) {
        return rMaxQ(1, l, r);
    }
};

struct FenwickTree {
private:
    int size;

public:
    vector<int> array1;
    vector<int> array2;

    FenwickTree(int size): array1(size + 1), array2(size + 2){
        this->size = size;
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
    int rsq(vector<int> &array, int ind) {
        int sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    int rsq(int ind) {
        return rsq(array1, ind) * ind - rsq(array2, ind);
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
    void update(vector<int> &array, int ind, int value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    void update(int a, int b, int value) {
        update(array1, a, value);
        update(array1, b + 1, -value);
        update(array2, a, value * (a - 1));
        update(array2, b + 1, -value * b);
    }

    int getSize() {
        return size;
    }
};

#define MAXN 100000

int T, N;
pii segments[MAXN];
vector<int> all;
umii mapAll;

void run(int testCaseNum) {
    all.clear();
    mapAll.clear();
    ri(N);
    all = {-1};
    int ans = 0;
    for (int i = 0; i < N; i++) {
        ri(segments[i].f);
        ri(segments[i].s);
        all.pb(segments[i].f);
        all.pb(segments[i].s);
    }
    sort(segments, segments + N);
    sort(all.begin(), all.end());
    int size = 0;
    for (int i = 1; i < all.size(); i++) {
        while (i < all.size() && all[i] == all[i - 1]) {
            i++;
        }
        if (i < all.size()) {
            mapAll[all[i]] = ++size;
        }
    }
    LazySegmentTree st(size);
    for (int i = 0; i < N; i++) {
        st.update(mapAll[segments[i].f], mapAll[segments[i].s], 1);
    }
    FenwickTree ft(size);
    for (int i = 1, j = 0; i <= size; ++i) {
        while (j < N && mapAll[segments[j].f] <= i) {
            st.update(mapAll[segments[j].f], mapAll[segments[j].s], -1);
            ft.update(mapAll[segments[j].f], mapAll[segments[j].s], 1);
            j++;
        }
        ans = max(ans, ft.rsq(i, i) + st.rMaxQ(i + 1, size));
    }
    printf("Case %d: %d\n", testCaseNum, ans);
}

int main() {
    ri(T);
    for (int i = 1; i <= T; i++) {
        run(i);
    }
    return 0;
}
