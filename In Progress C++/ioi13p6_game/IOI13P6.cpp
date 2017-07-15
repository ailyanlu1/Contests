/*
 * IOI13P6.cpp
 *
 *  Created on: Jul 13, 2017
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

long long gcd2(long long p, long long q) {
    return q == 0 ? p : gcd2(q, p % q);
}

long long gcd4(long long W, long long X, long long Y, long long Z) {
    return gcd2(gcd2(W, X), gcd2(Y, Z));
}

struct DynamicSegmentTree2D {
    struct Node {
    public:
        int child0, child1, child2, child3;
        long long gcd;
    };

    struct RowNode {
    public:
        RowNode *child0, *child1, *child2, *child3;
        int rowRoot;
    };

    vector<Node *> nodeAll = {nullptr};
    int nodeCnt = 1;

private:
    RowNode *root;
    int R; // number of rows
    int C; // number of columns

    void updateCol(int cur, int cL, int cR, int colInd, long long val) {
        if (cL > colInd || cR < colInd) return;
        if (cL >= colInd && cR <= colInd) {
            nodeAll[cur]->gcd = val;
            return;
        }
        int p2 = cL + (cR - cL) / 2;
        int p1 = cL + (p2 - cL) / 2;
        int p3 = p2 + 1 + (cR - p2 - 1) / 2;
        if (colInd <= p2) {
            if (colInd <= p1) {
                if (nodeAll[cur]->child0 == 0) {
                    nodeAll[cur]->child0 = nodeCnt++;
                    nodeAll.pb(new Node());
                }
                updateCol(nodeAll[cur]->child0, cL, p1, colInd, val);
                nodeAll[cur]->gcd = gcd4(nodeAll[nodeAll[cur]->child0]->gcd, (nodeAll[cur]->child1 ? nodeAll[nodeAll[cur]->child1]->gcd : 0),
                        (nodeAll[cur]->child2 ? nodeAll[nodeAll[cur]->child2]->gcd : 0), (nodeAll[cur]->child3 ? nodeAll[nodeAll[cur]->child3]->gcd : 0));
            } else {
                if (nodeAll[cur]->child1 == 0) {
                    nodeAll[cur]->child1 = nodeCnt++;
                    nodeAll.pb(new Node());
                }
                updateCol(nodeAll[cur]->child1, p1 + 1, p2, colInd, val);
                nodeAll[cur]->gcd = gcd4(nodeAll[nodeAll[cur]->child1]->gcd, (nodeAll[cur]->child0 ? nodeAll[nodeAll[cur]->child0]->gcd : 0),
                        (nodeAll[cur]->child2 ? nodeAll[nodeAll[cur]->child2]->gcd : 0), (nodeAll[cur]->child3 ? nodeAll[nodeAll[cur]->child3]->gcd : 0));
            }
        } else {
            if (colInd <= p3) {
                if (nodeAll[cur]->child2 == 0) {
                    nodeAll[cur]->child2 = nodeCnt++;
                    nodeAll.pb(new Node());
                }
                updateCol(nodeAll[cur]->child2, p2 + 1, p3, colInd, val);
                nodeAll[cur]->gcd = gcd4(nodeAll[nodeAll[cur]->child2]->gcd, (nodeAll[cur]->child0 ? nodeAll[nodeAll[cur]->child0]->gcd : 0),
                        (nodeAll[cur]->child1 ? nodeAll[nodeAll[cur]->child1]->gcd : 0), (nodeAll[cur]->child3 ? nodeAll[nodeAll[cur]->child3]->gcd : 0));
            } else {
                if (nodeAll[cur]->child3 == 0) {
                    nodeAll[cur]->child3 = nodeCnt++;
                    nodeAll.pb(new Node());
                }
                updateCol(nodeAll[cur]->child3, p3 + 1, cR, colInd, val);
                nodeAll[cur]->gcd = gcd4(nodeAll[nodeAll[cur]->child3]->gcd, (nodeAll[cur]->child0 ? nodeAll[nodeAll[cur]->child0]->gcd : 0),
                        (nodeAll[cur]->child1 ? nodeAll[nodeAll[cur]->child1]->gcd : 0), (nodeAll[cur]->child2 ? nodeAll[nodeAll[cur]->child2]->gcd : 0));
            }
        }
    }

    long long queryCol(int cur, int cL, int cR, int l, int r) {
        if (cur == 0 || cL > r || cR < l) return 0LL;
        if (cL >= l && cR <= r) return nodeAll[cur]->gcd;
        int p2 = cL + (cR - cL) / 2;
        int p1 = cL + (p2 - cL) / 2;
        int p3 = p2 + 1 + (cR - p2 - 1) / 2;
        if (r <= p2) {
            if (r <= p1) return nodeAll[cur]->child0 ? queryCol(nodeAll[cur]->child0, cL, p1, l, r) : 0;
            else if (l > p1) return nodeAll[cur]->child1 ? queryCol(nodeAll[cur]->child1, p1 + 1, p2, l, r) : 0;
            return gcd2(nodeAll[cur]->child0 ? queryCol(nodeAll[cur]->child0, cL, p1, l, r) : 0, nodeAll[cur]->child1 ? queryCol(nodeAll[cur]->child1, p1 + 1, p2, l, r) : 0);
        } else if (l > p2) {
            if (r <= p3) return nodeAll[cur]->child2 ? queryCol(nodeAll[cur]->child2, p2 + 1, p3, l, r) : 0;
            else if (l > p3) return nodeAll[cur]->child3 ? queryCol(nodeAll[cur]->child3, p3 + 1, cR, l, r) : 0;
            return gcd2(nodeAll[cur]->child2 ? queryCol(nodeAll[cur]->child2, p2 + 1, p3, l, r) : 0, nodeAll[cur]->child3 ? queryCol(nodeAll[cur]->child3, p3 + 1, cR, l, r) : 0);
        }
        long long q0 = nodeAll[cur]->child0 ? queryCol(nodeAll[cur]->child0, cL, p1, l, p2) : 0;
        long long q1 = nodeAll[cur]->child1 ? queryCol(nodeAll[cur]->child1, p1 + 1, p2, l, p2) : 0;
        long long q2 = nodeAll[cur]->child2 ? queryCol(nodeAll[cur]->child2, p2 + 1, p3, p2 + 1, r) : 0;
        long long q3 = nodeAll[cur]->child3 ? queryCol(nodeAll[cur]->child3, p3 + 1, cR, p2 + 1, r) : 0;
        return gcd4(q0, q1, q2, q3);
    }

    void updateRow(RowNode *&cur, int cU, int cD, int rowInd, int colInd, long long val) {
        if (cU > rowInd || cD < rowInd) return;
        if (cur == nullptr) cur = new RowNode();
        if (cU >= rowInd && cD <= rowInd) {
            if (cur->rowRoot == 0) {
                cur->rowRoot = nodeCnt++;
                nodeAll.pb(new Node());
            }
            updateCol(cur->rowRoot, 1, C, colInd, val);
            return;
        }
        int p2 = cU + (cD - cU) / 2;
        int p1 = cU + (p2 - cU) / 2;
        int p3 = p2 + 1 + (cD - p2 - 1) / 2;
        if (rowInd <= p2) {
            if (rowInd <= p1) {
                updateRow(cur->child0, cU, p1, rowInd, colInd, val);
                long long gcd = gcd4(queryCol(cur->child0->rowRoot, 1, C, colInd, colInd),
                        (cur->child1 ? queryCol(cur->child1->rowRoot, 1, C, colInd, colInd) : 0),
                        (cur->child2 ? queryCol(cur->child2->rowRoot, 1, C, colInd, colInd) : 0),
                        (cur->child3 ? queryCol(cur->child3->rowRoot, 1, C, colInd, colInd) : 0));
                if (cur->rowRoot == 0) {
                    cur->rowRoot = nodeCnt++;
                    nodeAll.pb(new Node());
                }
                updateCol(cur->rowRoot, 1, C, colInd, gcd);
            } else {
                updateRow(cur->child1, p1 + 1, p2, rowInd, colInd, val);
                long long gcd = gcd4(queryCol(cur->child1->rowRoot, 1, C, colInd, colInd),
                        (cur->child0 ? queryCol(cur->child0->rowRoot, 1, C, colInd, colInd) : 0),
                        (cur->child2 ? queryCol(cur->child2->rowRoot, 1, C, colInd, colInd) : 0),
                        (cur->child3 ? queryCol(cur->child3->rowRoot, 1, C, colInd, colInd) : 0));
                if (cur->rowRoot == 0) {
                    cur->rowRoot = nodeCnt++;
                    nodeAll.pb(new Node());
                }
                updateCol(cur->rowRoot, 1, C, colInd, gcd);
            }
        } else {
            if (rowInd <= p3) {
                updateRow(cur->child2, p2 + 1, p3, rowInd, colInd, val);
                long long gcd = gcd4(queryCol(cur->child2->rowRoot, 1, C, colInd, colInd),
                        (cur->child0 ? queryCol(cur->child0->rowRoot, 1, C, colInd, colInd) : 0),
                        (cur->child1 ? queryCol(cur->child1->rowRoot, 1, C, colInd, colInd) : 0),
                        (cur->child3 ? queryCol(cur->child3->rowRoot, 1, C, colInd, colInd) : 0));
                if (cur->rowRoot == 0) {
                    cur->rowRoot = nodeCnt++;
                    nodeAll.pb(new Node());
                }
                updateCol(cur->rowRoot, 1, C, colInd, gcd);
            } else {
                updateRow(cur->child3, p3 + 1, cD, rowInd, colInd, val);
                long long gcd = gcd4(queryCol(cur->child3->rowRoot, 1, C, colInd, colInd),
                        (cur->child0 ? queryCol(cur->child0->rowRoot, 1, C, colInd, colInd) : 0),
                        (cur->child1 ? queryCol(cur->child1->rowRoot, 1, C, colInd, colInd) : 0),
                        (cur->child2 ? queryCol(cur->child2->rowRoot, 1, C, colInd, colInd) : 0));
                if (cur->rowRoot == 0) {
                    cur->rowRoot = nodeCnt++;
                    nodeAll.pb(new Node());
                }
                updateCol(cur->rowRoot, 1, C, colInd, gcd);
            }
        }
    }

    long long queryRow(RowNode *cur, int cU, int cD, int u, int l, int d, int r) {
        if (cur == nullptr || cU > d || cD < u) return 0LL;
        if (cU >= u && cD <= d) return queryCol(cur->rowRoot, 1, C, l, r);
        int p2 = cU + (cD - cU) / 2;
        int p1 = cU + (p2 - cU) / 2;
        int p3 = p2 + 1 + (cD - p2 - 1) / 2;
        if (d <= p2) {
            if (d <= p1) return cur->child0 ? queryRow(cur->child0, cU, p1, u, l, d, r) : 0;
            else if (u > p1) return cur->child1 ? queryRow(cur->child1, p1 + 1, p2, u, l, d, r) : 0;
            return gcd2(cur->child0 ? queryRow(cur->child0, cU, p1, u, l, p1, r) : 0, cur->child1 ? queryRow(cur->child1, p1 + 1, p2, p1 + 1, l, d, r) : 0);
        } else if (u > p2) {
            if (d <= p3) return cur->child2 ? queryRow(cur->child2, p2 + 1, p3, u, l, d, r) : 0;
            else if (u > p3) return cur->child3 ? queryRow(cur->child3, p3 + 1, cD, u, l, d, r) : 0;
            return gcd2(cur->child2 ? queryRow(cur->child2, p2 + 1, p3, u, l, p3, r) : 0, cur->child3 ? queryRow(cur->child3, p3 + 1, cD, p3 + 1, l, d, r) : 0);
        }
        long long q0 = cur->child0 ? queryRow(cur->child0, cU, p1, u, l, p2, r) : 0;
        long long q1 = cur->child1 ? queryRow(cur->child1, p1 + 1, p2, u, l, p2, r) : 0;
        long long q2 = cur->child2 ? queryRow(cur->child2, p2 + 1, p3, p2 + 1, l, d, r) : 0;
        long long q3 = cur->child3 ? queryRow(cur->child3, p3 + 1, cD, p2 + 1, l, d, r) : 0;
        return gcd4(q0, q1, q2, q3);
    }

public:
    DynamicSegmentTree2D(int rows, int cols) {
        root = new RowNode();
        R = rows;
        C = cols;
    }

    void update(int rowInd, int colInd, long long val) {
        updateRow(root, 1, R, rowInd, colInd, val);
    }

    long long query(int u, int l, int d, int r) {
        return queryRow(root, 1, R, u, l, d, r);
    }

    int rows() {
        return R;
    }

    int cols() {
        return C;
    }
} *st;

void init(int R, int C) {
    st = new DynamicSegmentTree2D(R, C);
}

void update(int P, int Q, long long K) {
    st->update(P + 1, Q + 1, K);
}

long long calculate(int P, int Q, int U, int V) {
    return st->query(P + 1, Q + 1, U + 1, V + 1);
}

int main() {
    int R, C, N;
    ri(R);
    ri(C);
    ri(N);
    init(R, C);
    for (int i = 0; i < N; i++) {
        int T;
        ri(T);
        if (T == 1) {
            int P, Q;
            ll K;
            ri(P);
            ri(Q);
            rll(K);
            update(P, Q, K);
        } else if (T == 2) {
            int P, Q, U, V;
            ri(P);
            ri(Q);
            ri(U);
            ri(V);
            printf("%lld\n", calculate(P, Q, U, V));
        } else {
            i--;
        }
    }
    return 0;
}
