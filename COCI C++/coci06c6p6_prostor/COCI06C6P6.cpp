/*
 * COCI06C6P6.cpp
 *
 *  Created on: Jun 16, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair
#define left(x) x << 1
#define right(x) x << 1 | 1
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
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;

#define MAXX 1000

struct FenwickTree2D {
private:
    int sizeX;
    int sizeY;

public:
    int **array;

    FenwickTree2D(int sizeX, int sizeY) {
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        array = new int*[sizeX + 1];
        for (int i = 0; i <= sizeX; i++) {
            array[i] = new int[sizeY];
        }
    }

    /**
     * Range Sum Query
     * <p>
     * Time-Complexity:    O(log(nm))
     *
     * @param  indX x index
     * @param  indY y index
     * @return sum
     */
    int rsq(int indX, int indY) {
        // assert indX > 0 && indY > 0;
        int sum = 0;
        for (int x = indX; x > 0; x -= (x & -x)) {
            for (int y = indY; y > 0; y -= (y & -y)) {
                sum += array[x][y];
            }
        }
        return sum;
    }

    /**
     * Range Sum Query
     * <p>
     * Time-Complexity:    O(log(nm))
     *
     * @param  x1 top index
     * @param  y1 left index
     * @param  x2 bottom index
     * @param  y2 right index
     * @return sum
     */
    int rsq(int x1, int y1, int x2, int y2) {
        return rsq(x2, y2) + rsq(x1 - 1, y1 - 1) - rsq(x1 - 1, y2) - rsq(x2, y1 - 1);
    }

    /**
     * Update the array at [indX][indY] and all the affected regions above ind.
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(nm))
     *
     * @param  indX   x index
     * @param  indY   y index
     * @param  value value
     */
    void update(int indX, int indY, int value) {
        for (int x = indX; x <= sizeX; x += (x & -x)) {
            for (int y = indY; y <= sizeY; y += (y & -y)) {
                array[x][y] += value;
            }
        }
    }

    int getSizeX() {
        return sizeX;
    }

    int getSizeY() {
        return sizeY;
    }
} lo(MAXX, MAXX), hi(MAXX, MAXX);

struct event {
public:
    int type, y, x1, x2, z1, z2;

    event(int type, int y, int x1, int x2, int z1, int z2) {
        this->type = type;
        this->y = y;
        this->x1 = x1;
        this->x2 = x2;
        this->z1 = z1;
        this->z2 = z2;
    }
};

bool operator < (const event &a, const event &b) {
    if (a.y != b.y) return a.y < b.y;
    return a.type < b.type;
}

ll sweep(vector<event> *events) {
    ll ret = 0;
    sort(events->begin(), events->end());
    memset(lo.array, 0, sizeof(*lo.array));
    memset(hi.array, 0, sizeof(*hi.array));
    for (auto e = events->begin(); e != events->end(); e++) {
        if (e->type == 1 || e->type == 2) {
            ret += lo.rsq(e->x1, 1, e->x2, e->z2) - hi.rsq(e->x1, 1, e->x2, e->z1 - 1);
        }
        if (e->type == 1) {
            lo.update(e->x1, e->z1, 1);
            hi.update(e->x2, e->z2, 1);
        }
        if (e->type == 3) {
            lo.update(e->x1, e->z1, -1);
            hi.update(e->x2, e->z2, -1);
        }
    }
    return ret;
}

int N;
vector<event> xy, yz, zx;

int main() {
    ri(N);
    for (int i = 0; i < N; i++) {
        int x1, y1, z1, x2, y2, z2;
        scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
        if (x2 < x1) swap(x1, x2);
        if (y2 < y1) swap(y1, y2);
        if (z2 < z1) swap(z1, z2);
        if (x1 == x2) {
            xy.pb(event(1, y1, x1, x2, z1, z2));
            zx.pb(event(2, x1, z1, z2, y1, y2));
            xy.pb(event(3, y2, x1, x2, z1, z2));
        }
        if (y1 == y2) {
            yz.pb(event(1, z1, y1, y2, x1, x2));
            xy.pb(event(2, y1, x1, x2, z1, z2));
            yz.pb(event(3, z2, y1, y2, x1, x2));
        }
        if (z1 == z2) {
            zx.pb(event(1, x1, z1, z2, y1, y2));
            yz.pb(event(2, z1, y1, y2, x1, x2));
            zx.pb(event(3, x2, z1, z2, y1, y2));
        }
    }
    printf("%lld\n", sweep(&xy) + sweep(&yz) + sweep(&zx));
    return 0;
}
