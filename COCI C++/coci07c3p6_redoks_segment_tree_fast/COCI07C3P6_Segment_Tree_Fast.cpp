/*
 * COCI07C3P6_Segment_Tree_Fast.cpp
 *
 *  Created on: Jun 24, 2017
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

inline int mod10(int a) {
    return a < 10 ? a : a - 10;
}

struct SegmentTree {
    struct Node {
        int freq[10];
        int lazy;
        Node *left = nullptr, *right = nullptr;

        Node() {
            lazy = 0;
            memset(freq, 0, sizeof freq);
        }

        void rotate(int x) {
            static int temp[10];
            for (int i = 0; i < 10; i++) {
                temp[i] = freq[i];
            }
            for (int i = 0; i < 10; i++) {
                freq[mod10(i + x)] = temp[i];
            }
            lazy = mod10(lazy + x);
        }

        void propogate() {
            left->rotate(lazy);
            right->rotate(lazy);
            lazy = 0;
        }

        void merge() {
            for (int i = 0; i < 10; i++) {
                freq[i] = left->freq[i] + right->freq[i];
            }
        }
    };

private:
    int N;
    int *array;
    Node *root;

    void build(Node *cur, int cL, int cR) {
        if (cL == cR) {
            cur->freq[array[cL]] = 1;
        } else {
            int m = cL + (cR - cL) / 2;
            cur->left = new Node();
            build(cur->left, cL, m);
            cur->right = new Node();
            build(cur->right, m + 1, cR);
            cur->merge();
        }
    }

    int updateQuery(Node *cur, int cL, int cR, int l, int r) {
        int ans = 0;
        if (cL > r || cR < l) return 0;
        if (cL >= l && cR <= r) {
            for (int i = 0; i < 10; i++) {
                 ans += i * cur->freq[i];
            }
            cur->rotate(1);
        } else {
            cur->propogate();
            int m = cL + (cR - cL) / 2;
            ans += updateQuery(cur->left, cL, m, l, r);
            ans += updateQuery(cur->right, m + 1, cR, l, r);
            cur->merge();
        }
        return ans;
    }

public:
    SegmentTree(int size, int *arr) {
        /*array = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = arr[i - 1];
        }*/
        array = arr;
        root = new Node();
        N = size;
        build(root, 1, N);
    }

    int updateQuery(int l, int r) {
        return updateQuery(root, 1, N, l, r);
    }
};

#define MAXN 250000

int N, M, arr[MAXN + 1];
string s;

int main() {
    ri(N);
    ri(M);
    cin >> s;
    for (int i = 1; i <= N; i++) {
        arr[i] = s[i - 1] - '0';
    }
    SegmentTree tree(N, arr);
    for (int i = 0; i < M; i++) {
        int a, b;
        ri(a);
        ri(b);
        printf("%d\n", tree.updateQuery(a, b));
    }
    return 0;
}
