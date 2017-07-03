/*
 * TLE16C5P5.cpp
 *
 *  Created on: Jul 3, 2017
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

#define MAXN 200000
#define MAXP 100000

int N, lastInd[MAXP + 1], ind[MAXN];
pair<double, int> sorted[MAXN];
pair<int, double> updates[MAXN];
double r, maxV[MAXP + 1], pwr[MAXP + 1];

struct SegmentTree {
    struct Node {
        double val = 0.0;
        int size = 0;
    };

private:
    vector<Node> tree;
    int N;
    double *array;

    void build(int cur, int cL, int cR) {
        if (cL == cR) {
            tree[cur].val = array[cL];
            tree[cur].size = 0;
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
        tree[cur].val = tree[cur * 2].val * pwr[tree[cur * 2 + 1].size] + tree[cur * 2 + 1].val;
        tree[cur].size = tree[cur * 2].size + tree[cur * 2 + 1].size;
    }

    void update(int cur, int cL, int cR, int ind, double val, int size) {
        if (cL > ind || cR < ind) return;
        if (cL >= ind && cR <= ind) {
            tree[cur].val = val;
            tree[cur].size += size;
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, ind, val, size);
        update(cur * 2 + 1, m + 1, cR, ind, val, size);
        tree[cur].val = tree[cur * 2].val * pwr[tree[cur * 2 + 1].size] + tree[cur * 2 + 1].val;
        tree[cur].size = tree[cur * 2].size + tree[cur * 2 + 1].size;
    }

public:
    SegmentTree(int size, double *arr, bool oneIndexed): tree(4 * size) {
        array = new double[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = arr[i - !oneIndexed];
        }
        build(1, 1, size);
        N = size;
    }

    SegmentTree(int size): tree(4 * size) {
        array = new double[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = 0.0;
        }
        build(1, 1, size);
        N = size;
    }

    void update(int ind, double val, int size) {
        update(1, 1, N, ind, val, size);
    }

    double query() {
        return tree[1].val;
    }

    int size() {
        return N;
    }
} *st;

int main() {
    rd(r);
    ri(N);
    pwr[0] = 1;
    for (int i = 1; i <= MAXP; i++) {
        pwr[i] = pwr[i - 1] * r;
    }
    for (int i = 0; i < N; i++) {
        int p;
        double v;
        ri(p);
        rd(v);
        sorted[i] = {v, i};
        updates[i] = {p, v};
    }
    sort(sorted, sorted + N);
    for (int i = 0; i < N; i++) {
        ind[sorted[i].s] = i + 1;
    }
    for (int i = 0; i <= MAXP; i++) {
        lastInd[i] = -1;
        maxV[i] = 0.0;
    }
    st = new SegmentTree(N);
    for (int i = 0; i < N; i++) {
        if (updates[i].s > maxV[updates[i].f]) {
            maxV[updates[i].f] = updates[i].s;
            if (lastInd[updates[i].f] != -1) st->update(lastInd[updates[i].f], 0, -1);
            st->update(ind[i], updates[i].s, 1);
            lastInd[updates[i].f] = ind[i];
        }
        printf("%.7f\n", st->query());
    }
    return 0;
}
