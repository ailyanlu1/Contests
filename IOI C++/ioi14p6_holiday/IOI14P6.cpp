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
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
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
typedef map<ll, ll> mll;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;
typedef unordered_map<ll, ll> umll;

#define MAXN 100005

int N, S, D, SZ;
umii indToVal, valToInd;
set<int> ordered;

struct Node {
    Node *left = nullptr, *right = nullptr;
    int cnt = 0;
    ll sum = 0LL;
    Node(int cnt, ll sum) {
        this->cnt = cnt;
        this->sum = sum;
    }
    Node(Node *left, Node *right) {
        this->left = left;
        this->right = right;
        this->cnt = left->cnt + right->cnt;
        this->sum = left->sum + right->sum;
    }
} *root[MAXN];

Node *update(Node *&cur, int cL, int cR, int ind, int val) {
    if (cur == nullptr) cur = new Node(0, 0LL);
    if (cL > ind || cR < ind) return cur;
    if (cL == cR) return new Node(cur->cnt + 1, cur->sum + val);
    int m = m(cL, cR);
    return new Node(update(cur->left, cL, m, ind, val), update(cur->right, m + 1, cR, ind, val));
}

ll query(Node *l, Node *r, int cL, int cR, int x) {
    if (l == nullptr || r == nullptr || x <= 0) return 0LL;
    if (x >= r->cnt - l->cnt) return r->sum - l->sum;
    if (cL == cR) return (ll) x * (ll) indToVal[cL];
    int m = m(cL, cR);
    int y = (r->right ? r->right->cnt : 0) - (l->right ? l->right->cnt : 0);
    if (x > y) return query(l->left, r->left, cL, m, x - y) + (r->right ? r->right->sum : 0LL) - (l->right ? l->right->sum : 0LL);
    else return query(l->right, r->right, m + 1, cR, x);
}

ll solve(int cL, int cR, int l, int r, bool rev) {
    if (cL > cR) return 0LL;
    int m = m(cL, cR);
    ll ans = 0LL;
    int ind = l;
    For(i, l, r + 1) {
        ll q = rev ? query(root[i - 1], root[m], 1, SZ, D - (m - S) - (m - i)) : query(root[m - 1], root[i], 1, SZ, D - (S - m) - (i - m));
        if (q + rev > ans) {
            ans = q;
            ind = i;
        }
    }
    return max(ans, max(solve(cL, m - 1, l, ind, rev), solve(m + 1, cR, ind, r, rev)));
}

long long findMaxAttraction(int n, int start, int d, int attraction[]) {
    N = n;
    S = start + 1;
    D = d;
    FOR(i, N) {
        ordered.insert(attraction[i]);
    }
    SZ = 0;
    for (int a : ordered) {
        SZ++;
        indToVal[SZ] = a;
        valToInd[a] = SZ;
    }
    For(i, 1, N + 1) {
        root[i] = update(root[i - 1], 1, SZ, valToInd[attraction[i - 1]], attraction[i - 1]);
    }
    return max(solve(1, S, S, N, false), solve(S, N, 1, S, true));
}

int main() {
    int n, start, d;
    ri(n);
    ri(start);
    ri(d);
    int attraction[n];
    FOR(i, n) {
        ri(attraction[i]);
    }
    printf("%lld\n", findMaxAttraction(n, start, d, attraction));
    return 0;
}
