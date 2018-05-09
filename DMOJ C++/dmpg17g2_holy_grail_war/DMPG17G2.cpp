#include <bits/stdc++.h>
using namespace std;

#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define f first
#define s second
#define all(a) (a).begin(), (a).end()
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pill pair<int, ll>
#define plli pair<ll, int>
#define pdd pair<double, double>
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

struct MaxContiguousSumSegmentTree {
private:
    struct Node {
        long long pre, suf, sum, maxSum;
        bool isNull;

        Node() {
            this->pre = this->suf = this->sum = this->maxSum = 0;
            this->isNull = true;
        }

        Node(long long val) {
            this->pre = this->suf = this->sum = this->maxSum = val;
            this->isNull = false;
        }

        Node(Node l, Node r) {
            if (l.isNull) {
                this->pre = r.pre;
                this->suf = r.suf;
                this->sum = r.sum;
                this->maxSum = r.maxSum;
                this->isNull = r.isNull;
            } else if (r.isNull) {
                this->pre = l.pre;
                this->suf = l.suf;
                this->sum = l.sum;
                this->maxSum = l.maxSum;
                this->isNull = l.isNull;
            } else {
                this->pre = max(l.pre, l.sum + r.pre);
                this->suf = max(l.suf + r.sum, r.suf);
                this->sum = l.sum + r.sum;
                this->maxSum = max(max(l.maxSum, r.maxSum), l.suf + r.pre);
                this->isNull = false;
            }
        }
    };

    vector<Node> tree;
    long long *array;
    int N;

    void build(int cur, int cL, int cR) {
        if (cL == cR) {
            tree[cur] = Node(array[cL]);
            return;
        }
        int m = cL + (cR - cL) / 2;
        build(cur * 2, cL, m);
        build(cur * 2 + 1, m + 1, cR);
        tree[cur] = Node(tree[cur * 2], tree[cur * 2 + 1]);
    }

    void update(int cur, int cL, int cR, int ind, long long val) {
        if (cL > ind || cR < ind) return;
        if (cL == cR) {
            tree[cur] = Node(val);
            return;
        }
        int m = cL + (cR - cL) / 2;
        update(cur * 2, cL, m, ind, val);
        update(cur * 2 + 1, m + 1, cR, ind, val);
        tree[cur] = Node(tree[cur * 2], tree[cur * 2 + 1]);
    }

    Node query(int cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) return Node();
        if (cL >= l && cR <= r) return tree[cur];
        int m = cL + (cR - cL) / 2;
        Node left = query(cur * 2, cL, m, l, r);
        Node right = query(cur * 2 + 1, m + 1, cR, l, r);
        if (left.isNull) return right;
        if (right.isNull) return left;
        return Node(left, right);
    }

public:
    MaxContiguousSumSegmentTree(int size, long long *arr, bool oneIndexed) : tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        array = new long long[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = arr[i - !oneIndexed];
        }
        build(1, 1, size);
        N = size;
    }

    MaxContiguousSumSegmentTree(int size) : tree((int) (2 * pow(2.0, ceil(log2((double) size))))) {
        array = new long long[size + 1];
        for (int i = 1; i <= size; i++) {
            array[i] = 0;
        }
        build(1, 1, size);
        N = size;
    }

    void update(int ind, long long val) {
        update(1, 1, N, ind, val);
    }

    long long maxPreSum(int l, int r) {
        return query(1, 1, N, l, r).pre;
    }

    long long maxSufSum(int l, int r) {
        return query(1, 1, N, l, r).suf;
    }

    long long maxSum(int l, int r) {
        return query(1, 1, N, l, r).maxSum;
    }

    int size() {
        return N;
    }
} *st;

#define MAXN 100005

int N, Q;
ll A[MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    For(i, 1, N + 1) cin >> A[i];
    st = new MaxContiguousSumSegmentTree(N, A, true);
    char c;
    int a, b;
    FOR(i, Q) {
        cin >> c >> a >> b;
        if (c == 'S') {
            st->update(a, b);
        } else if (c == 'Q') {
            cout << st->maxSum(a, b) << nl;
        } else {
            i--;
        }
    }
    return 0;
}
