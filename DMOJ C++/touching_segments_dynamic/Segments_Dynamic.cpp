/*
 * Segments_Dynamic.cpp
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

struct DynamicLazySegmentTree {
    struct Node {
        Node *left = nullptr, *right = nullptr;
        int maxVal = 0, lazy = 0;

        Node(int val) {
            this->maxVal = val;
        }

        Node(Node *l, Node *r) {
            this->left = l;
            this->right = r;
            this->maxVal = max(l->maxVal, r->maxVal);
        }

        void propogate() {
            if (this->lazy != 0) {
                if (left != nullptr) {
                    left->maxVal += this->lazy;
                    left->lazy += this->lazy;
                }
                if (right != nullptr) {
                    right->maxVal += this->lazy;
                    right->lazy += this->lazy;
                }
                this->lazy = 0;
            }
        }
    };

private:
    Node *root;
    int N;
    int *array;

    Node *build(int cL, int cR) {
        if (cL == cR) return new Node(/*array[cL]*/0);
        int m = (cL + cR) >> 1;
        return new Node(build(cL , m), build(m + 1, cR));
    }

    void update(Node *cur, int cL, int cR, int l, int r, int val) {
        cur->propogate();
        if (cL > r || cR < l) return;
        if (cL >= l && cR <= r) {
            cur->maxVal += val;
            cur->lazy += val;
            return;
        }
        int m = (cL + cR) >> 1;
        update(cur->left, cL, m, l, r, val);
        update(cur->right, m + 1, cR, l, r, val);
        cur->maxVal = max(cur->left->maxVal, cur->right->maxVal);
    }

    int rMaxQ(Node *cur, int cL, int cR, int l, int r) {
        cur->propogate();
        if (cL > r || cR < l) return 0;
        if (cL >= l && cR <= r) return cur->maxVal;
        int m = (cL + cR) >> 1;
        int left = rMaxQ(cur->left, cL, m, l, r);
        int right = rMaxQ(cur->right, m + 1, cR, l, r);
        return max(left, right);
    }

public:
    DynamicLazySegmentTree(int size, int *arr) {
        array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = arr[i - 1];
        }
        root = build(1, size);
        N = size;
    }

    DynamicLazySegmentTree(int size) {
        array = new int[size + 1];
        /*for (int i = 1; i <= size; i++) {
            array[i] = 0;
        }*/
        root = build(1, size);
        N = size;
    }

    void update(int l, int r, int val) {
        update(root, 1, N, l, r, val);
    }

    int rMaxQ(int l, int r) {
        return rMaxQ(root, 1, N, l, r);
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
    DynamicLazySegmentTree st(size);
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
