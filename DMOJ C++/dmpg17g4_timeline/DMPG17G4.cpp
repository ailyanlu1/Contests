/*
 * DMPG17G4.cpp
 *
 *  Created on: Jul 4, 2017
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

struct DynamicSegmentTree {
    struct Node {
    public:
        Node *left = nullptr, *right = nullptr;
        set<int> times;
    };

private:
    int N;
    Node *root;

    void update(Node *cur, int cL, int cR, int ind, int val, bool ins) {
        if (cL > ind || cR < ind) return;
        if (ins) cur->times.insert(val);
        else cur->times.erase(val);
        if (cL >= ind && cR <= ind) return;
        int m = cL + (cR - cL) / 2;
        if (cur->left == nullptr) cur->left = new Node();
        update(cur->left, cL, m, ind, val, ins);
        if (cur->right == nullptr) cur->right = new Node();
        update(cur->right, m + 1, cR, ind, val, ins);
    }

    int query(Node *cur, int cL, int cR, int l, int r, int val) {
        if (cur == nullptr || cL > r || cR < l || cur->times.size() == 0) return INT_MIN;
        if (cL >= l && cR <= r) {
            auto above = cur->times.lower_bound(val);
            auto below = cur->times.lower_bound(val);
            if (above != cur->times.begin()) below--;
            if (above == cur->times.end()) return *below;
            return (abs(*above - val) <= abs(*below - val)) ? *above : *below;
        }
        int m = cL + (cR - cL) / 2;
        int left = query(cur->left, cL, m, l, r, val);
        int right = query(cur->right, m + 1, cR, l, r, val);
        if (left == INT_MIN) return right;
        if (right == INT_MIN) return left;
        if (left < right) swap(left, right);
        return (abs(left - val) <= abs(right - val)) ? left : right;
    }

public:
    DynamicSegmentTree(int size) {
        root = new Node();
        N = size;
    }

    void update(int ind, int val, bool ins) {
        update(root, 1, N, ind, val, ins);
    }

    int query(int l, int r, int val) {
        return query(root, 1, N, l, r, val);
    }

    int size() {
        return N;
    }
} *st;

#define MAXN (int) (1e5)
#define MAXT (int) (1e8)
#define MAXL (int) (1e9)

struct Query {
    char c, s;
    int a, b, v, filter;
} queries[MAXN];

int T[MAXN], L[MAXN], N, Q, filter, a, b, v, l, ans, numLabels, labels[MAXN * 2];
umii tToL;
umii lToInd;
char c, s;

int main() {
    ri(N);
    for (int i = 0; i < N; i++) {
        ri(a);
        ri(b);
        T[i] = a;
        L[i] = b;
        labels[i] = b;
    }
    numLabels = N;
    ri(Q);
    for (int i = 0; i < Q; i++) {
        rc(c);
        queries[i].c = c;
        if (c == 'T') {
            ri(a);
            ri(b);
            queries[i].a = a;
            queries[i].b = b;
        } else if (c == 'L') {
            ri(a);
            ri(b);
            labels[numLabels++] = b;
            queries[i].a = a;
            queries[i].b = b;
        } else if (c == 'F') {
            rc(s);
            ri(filter);
            queries[i].s = s;
            queries[i].filter = filter;
            labels[numLabels++] = filter;
        } else if (c == 'S') {
            ri(v);
            queries[i].v = v;
        } else {
            i--;
        }
    }
    st = new DynamicSegmentTree(numLabels);
    sort(labels, labels + numLabels);
    for (int i = 1; i <= numLabels; i++) {
        lToInd[labels[i - 1]] = i;
    }
    for (int i = 0; i < N; i++) {
        st->update(lToInd[L[i]], T[i], true);
        tToL[T[i]] = lToInd[L[i]];
    }
    s = '.';
    for (int i = 0; i < Q; i++) {
        c = queries[i].c;
        if (c == 'T') {
            a = queries[i].a;
            b = queries[i].b;
            l = tToL[a];
            st->update(l, a, false);
            st->update(l, b, true);
            tToL[b] = l; // no need to remove old reference
        } else if (c == 'L') {
            a = queries[i].a;
            b = lToInd[queries[i].b];
            l = tToL[a];
            st->update(l, a, false);
            st->update(b, a, true);
            tToL[a] = b;
        } else if (c == 'F') {
            s = queries[i].s;
            filter = queries[i].filter;
        } else if (c == 'S') {
            v = queries[i].v;
            if (s == '<') ans = st->query(1, lToInd[filter] - 1, v);
            else if (s == '>') ans = st->query(lToInd[filter] + 1, numLabels, v);
            else ans = st->query(1, numLabels, v);
            if (ans != INT_MIN) printf("%d\n", ans);
            else printf("-1\n");
        } else {
            i--;
        }
    }
    return 0;
}
