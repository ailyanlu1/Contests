/*
 * JOI14P5.cpp
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

#define MAXN 100000

int M, N;
vector<int> squares;

struct Device {
    int a, b, c, d;

    void compress() {
        a = lower_bound(squares.begin(), squares.end(), a) - squares.begin();
        b = lower_bound(squares.begin(), squares.end(), b) - squares.begin();
        c = lower_bound(squares.begin(), squares.end(), c) - squares.begin();
    }
} devices[MAXN];

struct RMQ {
private:
    int N;
    ll *tree;

    ll query(int cur, int cL, int cR, int l, int r) {
        if (cL >= r || cR <= l) return LL_INF;
        if (cL >= l && cR <= r) return tree[cur];
        int m = cL + (cR - cL) / 2;
        ll left = query(cur * 2 + 1, cL, m, l, r);
        ll right = query(cur * 2 + 2, m, cR, l, r);
        return min(left, right);
    }

    void update(int ind, ll val) {
        ind += N - 1;
        tree[ind] = val;
        while (ind > 0) {
            ind = (ind - 1) / 2;
            tree[ind] = min(tree[ind * 2 + 1], tree[ind * 2 + 2]);
        }
    }

public:
    RMQ(int size) {
        tree = new ll[2 * size];
        for (int i = 0; i < 2 * size; i++) {
            tree[i] = LL_INF;
        }
        N = size;
    }

    ll query(int l, int r) {
        return query(0, 0, N, l, r);
    }

    bool change(int ind, ll val) {
        if (val < tree[ind + N - 1]) {
            update(ind, val);
            return true;
        }
        return false;
    }
};

int main() {
    ri(M);
    ri(N);
    for (int i = 0; i < M; i++) {
        ri(devices[i].a);
        devices[i].a--;
        ri(devices[i].b);
        ri(devices[i].c);
        devices[i].c--;
        ri(devices[i].d);
        squares.pb(devices[i].a);
        squares.pb(devices[i].b);
        squares.pb(devices[i].c);
    }
    squares.pb(0);
    squares.pb(N);
    sort(squares.begin(), squares.end());
    squares.erase(unique(squares.begin(), squares.end()), squares.end());
    N = squares.size();
    for (int i = 0; i < M; i++) {
        devices[i].compress();
    }
    int n = 1;
    while (n < N) {
        n *= 2;
    }
    RMQ left(n), right(n);
    ll ans = LL_INF;
    for (int i = 0; i < M; i++) {
        ll costL = (devices[i].a == 0 ? 0 : left.query(devices[i].a, devices[i].b)) + devices[i].d;
        ll costR = (devices[i].b == N - 1 ? 0 : right.query(devices[i].a, devices[i].b)) + devices[i].d;
        left.change(devices[i].c, costL);
        right.change(devices[i].c, costR);
        ll cost = costL + costR - devices[i].d;
        ans = min(ans, cost);
    }
    if (ans == LL_INF) printf("-1");
    else printf("%lld", ans);
    return 0;
}
