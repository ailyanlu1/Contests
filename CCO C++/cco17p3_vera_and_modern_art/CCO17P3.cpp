/*
 * CCO17P3.cpp
 *
 *  Created on: Jun 18, 2017
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
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

#define MAXQ (int) 2e5

static pll getInd(ll n) {
    ll pre = 1, h = 60;
    while (n != 1) {
        if (n % 2 == 1) {
            pre += 2 * ((1LL << h) - 1);
        }
        pre++;
        n /= 2;
        h--;
    }
    return mp(pre, pre + 4 * ((1LL << h) - 1) + 1);
}

struct event {
    int type;
    ll x, ya, yb, c;
    event(int type, ll x, ll ya, ll yb, ll c) {
        this->type = type;
        this->x = x;
        this->ya = ya;
        this->yb = yb;
        this->c = c;
    }
};

bool event_cmp(const event &a, const event &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.type < b.type;
}

ll N, Q, x, y, c, xa, ya, xb, yb, type;
ll ans[MAXQ];
int cx, cy;
set<ll> X, Y;
mlli mapx, mapy;
vector<event> events;

struct FenwickTree {
private:
    int size;

public:
    ll *array;
    FenwickTree(int size) {
        this->size = size;
        array = new ll[size + 1];
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
    ll rsq(int ind) {
        int sum = 0;
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
    ll rsq(int a, int b) {
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
    void update(int ind, ll value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    void update(int a, int b, ll val) {
        update(a, val);
        update(b + 1, -val);
    }

    int getSize() {
        return size;
    }
} ft(1e6);


int main() {
    rll(N);
    rll(Q);
    for (int i = 0; i < N; i++) {
        rll(x);
        rll(y);
        rll(c);
        tie(xa, xb) = getInd(x);
        tie(ya, yb) = getInd(y);
        events.pb(event(1, xa, ya, yb, c));
        events.pb(event(2, xb, ya, yb, -c));
        X.insert(xa);
        X.insert(xb);
        Y.insert(ya);
        Y.insert(yb);
    }

    for (int i = 0; i < Q; i++) {
        rll(x);
        rll(y);
        tie(xa, xb) = getInd(x);
        tie(ya, yb) = getInd(y);
        events.pb(event(3, xa, ya, 0, i));
        X.insert(xa);
        Y.insert(ya);
    }

    for (ll xx: X) {
        mapx[xx] = ++cx;
    }
    for (ll yy: Y) {
        mapy[yy] = ++cy;
    }

    sort(events.begin(), events.end(), event_cmp);

    for (event v: events) {
        if (v.type == 3) {
            ans[v.c] = ft.rsq(mapy[v.ya]);
        } else {
            ft.update(mapy[v.ya], mapy[v.yb], v.c);
        }
    }

    for (int i = 0; i < Q; i++) {
        printf("%lld\n", ans[i]);
    }
}
