/*
 * MMCC14P2.cpp
 *
 *  Created on: Jun 17, 2017
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
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;

#define MAXN 2000
#define MAXM 5000

int N, M, Q, LCP[MAXN + 1];
string grid[MAXN + 1];

struct Node {
public:
    Node *left;
    Node *right;
    int minVal;
    Node(int val) {
        this->minVal = val;
        this->left = this->right = nullptr;
    }

    Node(Node *l, Node *r) {
        this->left = l;
        this->right = r;
        this->minVal = min(l->minVal, r->minVal);
    }
};

struct SegmentTree {
private:
    Node *root;
    int *arr;
    int N;

    Node *build(int cL, int cR) {
        if (cL == cR) return new Node(arr[cL]);
        int m = (cL + cR) >> 1;
        return new Node(build(cL, m), build(m + 1, cR));
    }

    Node *update(Node *cur, int cL, int cR, int ind) {
        if (cL <= ind && ind <= cR) {
            if (cL == cR) return new Node(arr[cL]);
            int m = (cL + cR) >> 1;
            return new Node(update(cur->left, cL, m, ind), update(cur->right, m + 1, cR, ind));
        }
        return cur;
    }

    int rMinQ(Node *cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) return INT_MAX;
        if (cL >= l && cR <= r) return cur->minVal;
        int m = (cL + cR) >> 1;
        int left = rMinQ(cur->left, cL, m, l, r);
        int right = rMinQ(cur->right, m + 1, cR, l, r);
        return min(left, right);
    }

public:
    void init(int size, int *array) {
        arr = array;
        root = build(1, size);
        N = size;
    }

    void update(int i) {
        if (i <= 1 || i > N) return;
        int j = 0;
        for (; j < M; j++) {
            if (grid[i][j] != grid[i - 1][j]) break;
        }
        LCP[i] = j;
        root = update(root, 1, N, i);
    }

    int rMinQ(int l, int r) {
        return rMinQ(root, 1, N, l, r);
    }
} st;

int main() {
    ri(N);
    ri(M);
    for (int i = 1; i <= N; i++) {
        cin >> grid[i];
    }
    for (int i = 2; i <= N; i++) {
        int j = 0;
        for (; j < M; j++) {
            if (grid[i][j] != grid[i - 1][j]) break;
        }
        LCP[i] = j;
    }
    st.init(N, LCP);
    ri(Q);
    for (int i = 0; i < Q; i++) {
        int l, r;
        ri(l);
        ri(r);
        if (l == r) {
            printf("%d\n", M * (r - l + 1));
        } else {
            printf("%d\n", st.rMinQ(l + 1, r) * (r - l + 1));
            string temp = grid[l];
            grid[l] = grid[r];
            grid[r] = temp;
            st.update(l);
            st.update(l + 1);
            st.update(r);
            st.update(r + 1);
        }
    }
    return 0;
}
