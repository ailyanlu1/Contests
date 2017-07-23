/*
 * COCI08C2P6.cpp
 *
 *  Created on: Jul 22, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
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
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
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

#define L 0
#define R 1
#define D 2
#define U 3
#define MAXN 300000

struct Point {
    ll x;
    ll y;
    bool marked;
    Point *adj[4];
    Point *CCW;
    Point *CW;

    Point(ll x, ll y) {
        this->x = x;
        this->y = y;
        marked = false;
        for (int i = 0; i < 4; i++) {
            adj[i] = nullptr;
        }
        CCW = nullptr, CW = nullptr;
    }
};

bool cmpX(Point *a, Point *b) {
    return a->x < b->x;
}

bool cmpY(Point *a, Point *b) {
    return a->y < b->y;
}

ll area2(Point *p) {
    return (p->x * p->CCW->y - p->y * p->CCW->x)
            + (p->CW->x * p->y - p->CW->y * p->x)
            - (p->CW->x * p->CCW->y - p->CW->y * p->CCW->x);
}

int ccw(Point *a, Point *b, Point *c) {
    ll a2 = (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
    if (a2 < 0) return -1;
    else if (a2 > 0) return +1;
    else return 0;
}

int N;
char order[MAXN - 2];
Point *nails[MAXN];
Point *extreme[4];
ll area;
stack<ll> ans;

int main() {
    ri(N);
    for (int i = 0; i < N; i++) {
        ll x, y;
        rll(x);
        rll(y);
        nails[i] = new Point(x, y);
    }
    rs(order);

    sort(nails, nails + N, cmpX);
    extreme[L] = nails[0];
    for (int i = 1; i < N; i++) {
        nails[i]->adj[L] = nails[i - 1];
        nails[i - 1]->adj[R] = nails[i];
    }
    extreme[R] = nails[N - 1];

    sort(nails, nails + N, cmpY);
    extreme[D] = nails[0];
    for (int i = 1; i < N; i++) {
        nails[i]->adj[D] = nails[i - 1];
        nails[i - 1]->adj[U] = nails[i];
    }
    extreme[U] = nails[N - 1];

    for (int i = 0; i < N - 2; i++) {
        if (order[i] == 'L') nails[i] = extreme[L];
        else if (order[i] == 'R') nails[i] = extreme[R];
        else if (order[i] == 'D') nails[i] = extreme[D];
        else /*if (order[i] == 'U')*/ nails[i] = extreme[U];
        nails[i]->marked = true;
        for (int j = 0; j < 4; j++){
            while (extreme[j]->marked) {
                extreme[j] = extreme[j]->adj[j ^ 1];
            }
        }
    }
    extreme[L]->CCW = extreme[L]->CW = extreme[R];
    extreme[R]->CCW = extreme[R]->CW = extreme[L];
    nails[N - 2] = extreme[L];
    nails[N - 1] = extreme[R];

    area = 0.0;
    for (int i = N - 3; i >= 0; i--) {
        int d;
        if (order[i] == 'L') d = L;
        else if (order[i] == 'R') d = R;
        else if (order[i] == 'D') d = D;
        else /*if (order[i] == 'U')*/ d = U;
        for (nails[i]->CCW = extreme[d]; nails[i]->CCW != extreme[d ^ 1] && ccw(nails[i], nails[i]->CCW, nails[i]->CCW->CCW) <= 0; nails[i]->CCW = nails[i]->CCW->CCW) {
            if (nails[i]->CCW == extreme[d]) continue;
            nails[i]->CCW->CCW->CW = nails[i]->CCW->CW;
            nails[i]->CCW->CW->CCW = nails[i]->CCW->CCW;
            area -= area2(nails[i]->CCW);
        }
        for (nails[i]->CW = extreme[d]; nails[i]->CW != extreme[d ^ 1] && ccw(nails[i], nails[i]->CW, nails[i]->CW->CW) >= 0; nails[i]->CW = nails[i]->CW->CW) {
            if (nails[i]->CW == extreme[d]) continue;
            nails[i]->CW->CCW->CW = nails[i]->CW->CW;
            nails[i]->CW->CW->CCW = nails[i]->CW->CCW;
            area -= area2(nails[i]->CW);
        }
        if (nails[i]->CCW != extreme[d] && nails[i]->CW != extreme[d]) {
            extreme[d]->CCW->CW = extreme[d]->CW;
            extreme[d]->CW->CCW = extreme[d]->CCW;
            area -= area2(extreme[d]);
        }
        nails[i]->CCW->CW = nails[i];
        nails[i]->CW->CCW = nails[i];
        area += area2(nails[i]);
        ans.push(area);
        if (nails[i]->x < extreme[L]->x) extreme[L] = nails[i];
        if (nails[i]->x > extreme[R]->x) extreme[R] = nails[i];
        if (nails[i]->y < extreme[D]->y) extreme[D] = nails[i];
        if (nails[i]->y > extreme[U]->y) extreme[U] = nails[i];
    }
    while(!ans.empty()) {
        printf("%lld.%lld\n", ans.top() / 2, ans.top() % 2 * 5);
        ans.pop();
    }
    return 0;
}
