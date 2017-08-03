/*
 * MNYC17P6.cpp
 *
 *  Created on: Aug 3, 2017
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


#define MAXN 100000
#define MAXC 1000

int N, Q, arr[MAXN + 1], t, a, b;
queue<int> freeInd;
umii ind, cnt;

struct SegmentTree {
    struct Node {
        bitset<MAXC> freq;
    };

private:
    vector<Node> tree;
    int N;

    void build(int cur, int cL, int cR) {
        if (cL == cR) {
            tree[cur].freq[ind[arr[cL]]] = 1;
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL , m);
        build(cur * 2 + 1, m + 1, cR);
        tree[cur].freq = tree[cur * 2].freq | tree[cur * 2 + 1].freq;
    }

    void update(int cur, int cL, int cR, int ind, int val, int old) {
        if (cL > ind || cR < ind) return;
        if (cL >= ind && cR <= ind) {
            tree[cur].freq[old] = 0;
            tree[cur].freq[val] = 1;
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, ind, val, old);
        update(cur * 2 + 1, m + 1, cR, ind, val, old);
        tree[cur].freq = tree[cur * 2].freq | tree[cur * 2 + 1].freq;
    }

    bitset<MAXC> query(int cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) return 0;
        if (cL >= l && cR <= r) return tree[cur].freq;
        int m = cL + (cR - cL) / 2;
        bitset<MAXC> left = query(cur * 2, cL, m, l, r);
        bitset<MAXC> right = query(cur * 2 + 1, m + 1, cR, l, r);
        return left | right;
    }

public:
    SegmentTree(int size): tree((int) (2 * pow(2.0, ceil(log((double) size) / log(2.0))))) {
        build(1, 1, size);
        N = size;
    }

    void update(int ind, int val, int old) {
        update(1, 1, N, ind, val, old);
    }

    bitset<MAXC> query(int l, int r) {
        return query(1, 1, N, l, r);
    }

    int size() {
        return N;
    }
} *st;

int main() {
    for (int i = 1; i <= MAXC; i++) {
        freeInd.push(i);
    }
    ri(N);
    ri(Q);
    for (int i = 1; i <= N; i++) {
        ri(arr[i]);
        if (ind.find(arr[i]) == ind.end()) {
            ind[arr[i]] = freeInd.front();
            freeInd.pop();
        }
        cnt[arr[i]]++;
    }
    st = new SegmentTree(N);
    for (int i = 0; i < Q; i++) {
        ri(t);
        if (t == 1) {
            ri(a);
            ri(b);
            if (ind.find(b) == ind.end()) {
                ind[b] = freeInd.front();
                freeInd.pop();
            }
            st->update(a, ind[b], ind[arr[a]]);
            cnt[arr[a]]--;
            if (cnt[arr[a]] == 0) freeInd.push(ind[arr[a]]);
            arr[a] = b;
            cnt[arr[a]]++;
        } else {
            ri(a);
            ri(b);
            printf("%d\n", st->query(a, b).count());
        }
    }
    return 0;
}
