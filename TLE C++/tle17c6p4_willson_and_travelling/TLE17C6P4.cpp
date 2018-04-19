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

#define MAXXY 500005

struct Line {
    int x, y1, y2;
};

bool cmpy1lt(const Line &a, const Line &b) {
    return a.y1 < b.y1;
}

bool cmpy2gt(const Line &a, const Line &b) {
    return a.y2 > b.y2;
}

int N;
vector<Line> LL[MAXXY][2];

template <typename T>
struct FenwickTreeRangePoint {
private:
    int size;
    T *array;

public:
    FenwickTreeRangePoint(int size) {
        this->size = size;
        array = new T[size + 1];
        for (int i = 0; i <= size; i++) {
            array[i] = 0;
        }
    }

    T getValue(int ind) {
        T sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    void update(int ind, T value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    void update(int a, int b, T value) {
        update(a, value);
        update(b + 1, -value);
    }

    int getSize() {
        return size;
    }
};

FenwickTreeRangePoint<int> *ft;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int x1, y1, x2, y2;
    FOR(i, N) {
        cin >> x1 >> y1 >> x2 >> y2;
        LL[x1][0].pb({x1, y1, y2});
        LL[x2][1].pb({x2, y1, y2});
    }
    ft = new FenwickTreeRangePoint<int>(MAXXY);
    int ans = 0;
    FOR(x, MAXXY) {
        umap<int, pair<int, pair<bool, bool>>> left, right;
        for (Line &l : LL[x][0]) {
            ft->update(l.y1, l.y2, 1);
            if (left.count(l.y1) && left[l.y1].s.f) left[l.y1].s.s = 0;
            else {
                left[l.y1].f++;
                left[l.y1].s.f = 0;
                left[l.y1].s.s = 1;
            }
            if (left.count(l.y2) && !left[l.y2].s.f) left[l.y2].s.s = 0;
            else {
                left[l.y2].f++;
                left[l.y2].s.f = 1;
                left[l.y2].s.s = 1;
            }
        }
        for (Line &l : LL[x][1]) {
            if (left.count(l.y1)) {
                left[l.y1].s.s = 0;
                if (right.count(l.y1) && right[l.y1].s.f) right[l.y1].s.s = 0;
            } else if (right.count(l.y1) && right[l.y1].s.f) {
                right[l.y1].s.s = 0;
            } else {
                right[l.y1].f++;
                right[l.y1].s.f = 0;
                right[l.y1].s.s = 1;
            }
            if (left.count(l.y2)) {
                left[l.y2].s.s = 0;
                if (right.count(l.y2) && !right[l.y2].s.f) right[l.y2].s.s = 0;
            } else if (right.count(l.y2) && !right[l.y2].s.f) {
                right[l.y2].s.s = 0;
            } else {
                right[l.y2].f++;
                right[l.y2].s.f = 1;
                right[l.y2].s.s = 1;
            }
        }
        for (pair<int, pair<int, pair<bool, bool>>> y : left) if (y.s.s.s && ft->getValue(y.f) == y.s.f) ans++;
        for (pair<int, pair<int, pair<bool, bool>>> y : right) if (y.s.s.s && ft->getValue(y.f) == y.s.f) ans++;
        for (Line &l : LL[x][1]) ft->update(l.y1, l.y2, -1);
    }
    cout << ans << nl;
    return 0;
}
