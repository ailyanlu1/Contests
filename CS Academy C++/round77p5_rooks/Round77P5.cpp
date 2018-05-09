// https://csacademy.com/contest/round-77/task/rooks/
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

#define MAXKQ 100005
#define MAXNM 30005

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

    T rsq(int ind) {
        T sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    T rsq(int a, int b) {
        return rsq(b) - rsq(a - 1);
    }

    void update(int ind, T value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    int getSize() {
        return size;
    }
};

struct Query {
    int x1, x2, y1, y2, ind, block1, block2;
};

bool cmp1(const Query &a, const Query &b) {
    if (a.block1 != b.block1) return a.block1 < b.block1;
    else return a.x2 < b.x2;
}

bool cmp2(const Query &a, const Query &b) {
    if (a.block2 != b.block2) return a.block2 < b.block2;
    else return a.y2 < b.y2;
}

bool cmpInd(const Query &a, const Query &b) {
    return a.ind < b.ind;
}

const int sz = 150;

int N, M, K, Q, xcnt[MAXNM], ycnt[MAXNM], xans[MAXKQ], yans[MAXKQ];
Query q[MAXKQ];
FenwickTree<int> *ftx, *fty;
vector<int> X[MAXNM], Y[MAXNM];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> K >> Q;
    FOR(i, N + 1) ycnt[i] = 0;
    FOR(i, M + 1) xcnt[i] = 0;
    int x, y;
    FOR(i, K) {
        cin >> y >> x;
        Y[x].pb(y);
        X[y].pb(x);
    }
    FOR(i, Q) {
        cin >> q[i].y1 >> q[i].x1 >> q[i].y2 >> q[i].x2;
        q[i].ind = i;
        q[i].block1 = q[i].x1 / sz;
        q[i].block2 = q[i].y1 / sz;
    }
    sort(q, q + Q, cmp1);
    fty = new FenwickTree<int>(N);
    int l = q[0].x1;
    int r = l - 1;
    FOR(i, Q) {
        while (l < q[i].x1) {
            for (int y : Y[l]) {
                ycnt[y]--;
                if (ycnt[y] == 0) fty->update(y, -1);
            }
            l++;
        }
        while (l > q[i].x1) {
            l--;
            for (int y : Y[l]) {
                if (ycnt[y] == 0) fty->update(y, 1);
                ycnt[y]++;
            }
        }
        while (r < q[i].x2) {
            r++;
            for (int y : Y[r]) {
                if (ycnt[y] == 0) fty->update(y, 1);
                ycnt[y]++;
            }
        }
        while (r > q[i].x2) {
            for (int y : Y[r]) {
                ycnt[y]--;
                if (ycnt[y] == 0) fty->update(y, -1);
            }
            r--;
        }
        yans[q[i].ind] = fty->rsq(q[i].y1, q[i].y2);
    }
    sort(q, q + Q, cmp2);
    ftx = new FenwickTree<int>(M);
    l = q[0].y1;
    r = l - 1;
    FOR(i, Q) {
        while (l < q[i].y1) {
            for (int x : X[l]) {
                xcnt[x]--;
                if (xcnt[x] == 0) ftx->update(x, -1);
            }
            l++;
        }
        while (l > q[i].y1) {
            l--;
            for (int x : X[l]) {
                if (xcnt[x] == 0) ftx->update(x, 1);
                xcnt[x]++;
            }
        }
        while (r < q[i].y2) {
            r++;
            for (int x : X[r]) {
                if (xcnt[x] == 0) ftx->update(x, 1);
                xcnt[x]++;
            }
        }
        while (r > q[i].y2) {
            for (int x : X[r]) {
                xcnt[x]--;
                if (xcnt[x] == 0) ftx->update(x, -1);
            }
            r--;
        }
        xans[q[i].ind] = ftx->rsq(q[i].x1, q[i].x2);
    }
    sort(q, q + Q, cmpInd);
    FOR(i, Q) {
        cout << xans[i] * (q[i].y2 - q[i].y1 + 1) + yans[i] * (q[i].x2 - q[i].x1 + 1 - xans[i]) << nl;
    }
    return 0;
}
