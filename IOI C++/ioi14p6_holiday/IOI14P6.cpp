#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
#define mid(x, y) (x + (y - x) / 2)
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
#define randi(a, b) (rand() % (b - a + 1) + a)

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

/*Node *build(int cL, int cR) {
    if (cL == cR) return new Node(0, 0LL);
    int m = mid(cL, cR);
    return new Node(build(cL, m), build(m + 1, cR));
}*/

Node *update(Node *&cur, int cL, int cR, int ind, int val) {
    if (cur == nullptr) cur = new Node(0, 0LL);
    if (cL > ind || cR < ind) return cur;
    if (cL == cR) return new Node(cur->cnt + 1, cur->sum + val);
    int m = mid(cL, cR);
    return new Node(update(cur->left, cL, m, ind, val), update(cur->right, m + 1, cR, ind, val));
}

ll query(Node *l, Node *r, int cL, int cR, int x) {
    if (l == nullptr || r == nullptr || x <= 0) return 0LL;
    if (x >= r->cnt - l->cnt) return r->sum - l->sum;
    if (cL == cR) return (ll) x * (ll) indToVal[cL];
    int m = mid(cL, cR);
    int y = (r->right ? r->right->cnt : 0) - (l->right ? l->right->cnt : 0);
    if (x > y) return query(l->left, r->left, cL, m, x - y) + (r->right ? r->right->sum : 0LL) - (l->right ? l->right->sum : 0LL);
    else return query(l->right, r->right, m + 1, cR, x);
}

ll solve(int cL, int cR, int l, int r) {
    if (cL > cR) return 0LL;
    int m = mid(cL, cR);
    ll ans = 0LL;
    int ind = l;
    for (int i = l; i <= r; i++) {
        ll q = query(root[m - 1], root[i], 1, SZ, D - (S - m) - (i - m));
        if (q > ans) {
            ans = q;
            ind = i;
        }
    }
    return max(ans, max(solve(cL, m - 1, l, ind), solve(m + 1, cR, ind, r)));
}

ll solveRev(int cL, int cR, int l, int r) {
    if (cL > cR) return 0LL;
    int m = mid(cL, cR);
    ll ans = 0LL;
    int ind = l;
    for (int i = l; i <= r; i++) {
        ll q = query(root[i - 1], root[m], 1, SZ, D - (m - S) - (m - i));
        if (q >= ans) {
            ans = q;
            ind = i;
        }
    }
    return max(ans, max(solveRev(cL, m - 1, l, ind), solveRev(m + 1, cR, ind, r)));
}

long long findMaxAttraction(int n, int start, int d, int attraction[]) {
    N = n;
    S = start + 1;
    D = d;
    for (int i = 0; i < N; i++) {
        ordered.insert(attraction[i]);
    }
    // index
    SZ = 0;
    for (int a : ordered) {
        SZ++;
        indToVal[SZ] = a;
        valToInd[a] = SZ;
    }
    // forward
    // root[0] = build(1, SZ);
    for (int i = 1; i <= N; i++) {
        root[i] = update(root[i - 1], 1, SZ, valToInd[attraction[i - 1]], attraction[i - 1]);
    }
    // ll ans = solve(1, S, S, N);
    // reverse
    // S = N - start;
    // root[0] = nullptr;
    // for (int i = 1; i <= N; i++) {
    //     root[i] = update(root[i - 1], 1, SZ, valToInd[attraction[N - i]], attraction[N - i]);
    // }
    // return max(ans, solve(1, S, S, N));
    return max(solve(1, S, S, N), solveRev(S, N, 1, S));
}

int main() {
    int n, start, d;
    ri(n);
    ri(start);
    ri(d);
    int attraction[n];
    for (int i = 0; i < n; i++) {
        ri(attraction[i]);
    }
    printf("%lld\n", findMaxAttraction(n, start, d, attraction));
    return 0;
}
