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
#define SET0(a) memset((a), 0, sizeof(a))
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

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

template <typename T>
struct FenwickTree {
private:
    int size;
    T *array;

public:
    FenwickTree(int size) {
        this->size = size;
        array = new T[size + 1];
        for (int i = 0; i <= size; i++) {
            array[i] = 0;
        }
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
    T rsq(int ind) {
        T sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
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
    T rsq(int a, int b) {
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
    void update(int ind, T value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    int getSize() {
        return size;
    }
};

struct PersistentSegmentTree {
    struct Node {
        Node *left;
        Node *right;
        ll sum;

        Node(ll val) {
            this->sum = val;
            this->left = this->right = nullptr;
        }

        Node(Node *l, Node *r) {
            this->left = l;
            this->right = r;
            this->sum = l->sum + r->sum;
        }
    };

private:
    vector<Node*> rev;
    ll *array;
    int revInd = 0;
    int N;

    Node *build(int cL, int cR) {
        if (cL == cR) return new Node(array[cL]);
        int m = cL + (cR - cL) / 2;
        return new Node(build(cL , m), build(m + 1, cR));
    }

    Node *update(Node *cur, int cL, int cR, int ind, ll val) {
        if (cL <= ind && ind <= cR) {
            if (cL == cR) return new Node(cur->sum + val);
            int m = cL + (cR - cL) / 2;
            return new Node(update(cur->left, cL, m, ind, val), update(cur->right, m + 1, cR, ind, val));
        }
        return cur;
    }

    ll query(Node *cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) return 0LL;
        if (cL >= l && cR <= r) return cur->sum;
        int m = cL + (cR - cL) / 2;
        ll left = query(cur->left, cL, m, l, r);
        ll right = query(cur->right, m + 1, cR, l, r);
        return left + right;
    }

public:
    PersistentSegmentTree(int size, ll *arr, bool oneIndexed) {
        array = new ll[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = arr[i - !oneIndexed];
        }
        rev.push_back(build(1, size));
        N = size;
    }

    PersistentSegmentTree(int size) {
        array = new ll[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = 0LL;
        }
        rev.push_back(build(1, size));
        N = size;
    }

    void update(int l, int r, int val) {
        rev.push_back(update(update(rev[revInd++], 1, N, l, val), 1, N, r + 1, -val));
    }

    ll query(int revInd, int l, int r) {
        return query(rev[revInd], 1, N, l, r);
    }

    int size() {
        return N;
    }
};

#define MAXNM 100010
#define MAXK 7

FenwickTree<int> *ft;
PersistentSegmentTree *st;
int N, M, K, L[MAXNM], R[MAXNM], last[MAXNM];
ll S[MAXK], A[MAXNM], X[MAXNM];
vector<int> flip[MAXNM];

int main() {
    ri(N);
    ri(M);
    ri(K);
    For(i, 1, N + 1) {
        rll(A[i]);
    }
    FOR(i, K) {
        rll(S[i]);
    }
    ft = new FenwickTree<int>(N);
    st = new PersistentSegmentTree(N);
    FOR(i, M) {
        ri(L[i]);
        ri(R[i]);
        rll(X[i]);
        st->update(L[i], R[i], X[i]);
    }
    Fill(last, M + 1, N + 1);
    FOR(i, K) {
        For(j, 1, N + 1) {
            int lo = 0, hi = M, mid, ind = M + 1;
            while (lo <= hi) {
                mid = lo + (hi - lo) / 2;
                ll q = st->query(mid, 1, j) + A[j];
                if (S[i] == q) ind = mid;
                if (S[i] <= q) hi = mid - 1;
                else lo = mid + 1;
            }
            MIN(last[j], ind);
        }
    }
    ll sum = 0LL;
    For(i, 1, N + 1) {
        sum += A[i];
        ft->update(i, 1);
        flip[last[i]].pb(i);
    }
    FOR(i, M) {
        for (int x : flip[i]) {
            ft->update(x, -1);
        }
        sum += (ll) ft->rsq(L[i], R[i]) * X[i];
        printf("%lld\n", sum);
    }
    return 0;
}
