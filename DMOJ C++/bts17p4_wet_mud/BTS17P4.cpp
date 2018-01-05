#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) ((x) << 1)
#define r(x) ((x) << 1 | 1)
#define m(x, y) ((x) + ((y) - (x)) / 2)
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define FILL(a, x) memset((a), (x), sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x);
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<int, float> pif;
typedef pair<float, int> pfi;
typedef pair<double, double> pdd;
typedef pair<int, double> pid;
typedef pair<double, int> pdi;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef pair<llu, llu> pllu;
typedef pair<int, llu> pillu;
typedef pair<llu, int> pllui;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

struct DynamicSegmentTree {
    struct Node {
        Node *left = nullptr, *right = nullptr;
        int val = INT_MAX;
    };

private:
    Node *root;
    int N;

    void update(Node *cur, int cL, int cR, int ind, int val) {
        if (cL > ind || cR < ind) return;
        if (cL >= ind && cR <= ind) {
           cur->val = val;
           return;
        }
        int m = cL + (cR - cL) / 2;
        if (cur->left == nullptr) cur->left = new Node();
        update(cur->left, cL, m, ind, val);
        if (cur->right == nullptr) cur->right = new Node();
        update(cur->right, m + 1, cR, ind, val);
        cur->val = min(cur->left->val, cur->right->val);
    }

    pii query(Node *cur, int cL, int cR, int l, int r) {
        if (cur == nullptr || cL > r || cR < l) return mp(INT_MAX, l);
        if (cL >= l && cR <= r) return mp(cur->val, l);
        int m = cL + (cR - cL) / 2;
        pii left = query(cur->left, cL, m, l, r);
        pii right = query(cur->right, m + 1, cR, l, r);
        return min(left, right);
    }

public:
    DynamicSegmentTree(int size) {
        root = new Node();
        N = size;
    }

    void update(int ind, int val) {
        update(root, 1, N, ind, val);
    }

    pii query(int l, int r) {
        return query(root, 1, N, l, r);
    }

    int size() {
        return N;
    }
};

int N, M, J, p, t;
umii tToP;
umii pToT;
set<int> times;
DynamicSegmentTree *st;

int main() {
    ri(N);
    ri(M);
    ri(J);
    st = new DynamicSegmentTree(N);
    FOR(i, M) {
        ri(p);
        ri(t);
        st->update(p, t);
        tToP[t] = p;
        pToT[p] = t;
        times.insert(t);
    }
    int curPos = 0, curTime = 0;
    pii q;
    auto iter = times.begin();
    while (curPos + J <= N) {
        q = st->query(curPos + 1, min(curPos + J, N));
        if (q.f == INT_MAX) {
            printf("-1\n");
            return 0;
        }
        MAX(curTime, q.f);
        curPos = q.s;
        while (*iter < curTime) {
            st->update(pToT[*(iter++)], 0);
        }
    }
    printf("%d\n", curTime);
    return 0;
}
