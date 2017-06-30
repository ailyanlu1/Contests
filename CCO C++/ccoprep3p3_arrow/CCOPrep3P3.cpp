/*
 * CCOPrep3P3.cpp
 *
 *  Created on: Jun 29, 2017
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

#define MAXN 100000
#define EPS 1e-15

struct Vector {
    double x, y;
    Vector() {};
    Vector(double x, double y) {
        this->x = x;
        this->y = y;
    }

    // plus
    Vector operator + (const Vector &v) const {
        return Vector(x + v.x, y + v.y);
    }

    // minus
    Vector operator - (const Vector &v) const {
        return Vector(x - v.x, y - v.y);
    }

    // scale / times
    Vector operator * (double a) const {
        return Vector(x * a, y * a);
    }

    // dot
    double operator ^ (const Vector &v) const {
        return x * v.x + y * v.y;
    }

    // cross 2D
    double operator * (const Vector &v) const {
        return x * v.y - y * v.x;
    }
};

struct Line {
    Vector a, b;
    double rad;

    Line() {}
    Line(const Vector &a, const Vector &b) {
        this->a = a;
        this->b = b;
        this->rad = atan2(b.y, b.x);
    }

    bool operator < (const Line &l) const {
        return rad < l.rad;
    }

    bool onLeft(const Vector &v) const {
        return b * (v - a) > EPS;
    }
};

int N;
Line all[MAXN * 2];
vector<Line> L;

Vector getLineIntersection(Line la, Line lb) {
    double t = (lb.b * (la.a - lb.a)) / (la.b * lb.b);
    return la.a + la.b * t;
}

bool halfPlaneIntersection(int n) {
    static Vector v[MAXN * 2];
    static Line q[MAXN * 2];
    sort(L.begin(), L.end());
    int front = 0;
    int back = 0;
    q[0] = L[0];
    for (int i = 1; i < n; i++) {
        while (front < back && !L[i].onLeft(v[back - 1])) back--;
        while (front < back && !L[i].onLeft(v[front])) front++;
        if (abs(q[back].b * L[i].b) < EPS) {
            if (q[back].onLeft(L[i].a)) q[back] = L[i];
        } else {
            q[++back] = L[i];
        }
        if (front < back) v[back - 1] = getLineIntersection(q[back - 1], q[back]);
    }
    while (front < back && !q[front].onLeft(v[back - 1])) back--;
    return (back - front) > 1;
}

bool check(int n) {
    L.clear();
    for (int i = 0; i < n * 2; i++) {
        L.pb(all[i]);
    }
    return halfPlaneIntersection(n * 2);
}

int main() {
    ri(N);
    for (int i = 0; i < N; i++) {
        int x, y1, y2;
        ri(x);
        ri(y1);
        ri(y2);
        all[i * 2] = Line(Vector(0, (double) y2 / x), Vector(-1.0 / x, 1.0));
        all[i * 2 + 1] = Line(Vector(0, (double) y1 / x), Vector(1.0 / x, -1.0));
    }
    int l = 1;
    int r = N;
    int count = 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            count = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%d", count);
    return 0;
}
