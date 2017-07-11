/*
 * IOI14P1.cpp
 *
 *  Created on: Jul 10, 2017
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

// TESTING

// SAMPLE 1
// const int _N = 4;
// int _DIST[_N][_N] = {{0, 3, 5, 7}, {3, 0, 2, 4}, {5, 2, 0, 6}, {7, 4, 6, 0}};
// int _FIRST = 2;

// SAMPLE 2
const int _N = 5;
int _DIST[_N][_N] = {{0, 2, 7, 6, 3}, {2, 0, 5, 4, 1}, {7, 5, 0, 1, 6}, {6, 4, 1, 0, 5}, {3, 1, 6, 5, 0}};
int _FIRST = 2;

int _COUNT = 0;
int _MAXCOUNT = 3 * (_N - 1);
int getDistance(int i, int j) {
    if (_COUNT++ >= _MAXCOUNT) {
        printf("EXCEEDED LIMIT OF CALLS TO getDistance()");
        exit(0);
    }
    if (i < 0 || i >= _N || j < 0 || j >= _N) return -1;
    return _DIST[i][j];
}
// END TESTING

#define MAXN 5000
#define MAXM 1000000

#define C 1
#define D 2

int block[MAXM]; // stores the station at that block
int dist[MAXN][MAXN], S, L, R; // S is station closest to 0 (of type D)
                               // L is current leftmost station of type C
                               // R is current rightmost station of type D
vector<pii> leftStations, rightStations; // left is stations left of 0
                                         // right is stations right of S

void findLocation(int n, int first, int location[], int stype[]) {
    Fill(block, -1);
    location[0] = first;
    block[first] = 0;
    stype[0] = C;
    int minDist = INT_MAX; // closest distance of a station to 0
    for (int i = 1; i < n; i++) {
        dist[0][i] = dist[i][0] = getDistance(0, i); // distances are symmetric
        if (dist[0][i] < minDist) {
            minDist = dist[0][i];
            S = i;
        }
    }
    location[S] = location[0] + dist[0][S]; // location is loc of 0 plus dist from 0 to S
    block[location[S]] = S;
    stype[S] = D; // station S must be opposite type of 0 since it is the closest (no loops)
    for (int i = 1; i < n; i++) {
        if (i == S) continue;
        dist[S][i] = dist[i][S] = getDistance(S, i);
        if (dist[S][i] < dist[S][0] && dist[0][S] + dist[S][i] == dist[i][0]) { // station lies between 0 and S
            location[i] = location[S] - dist[S][i];
            block[location[i]] = i;
            stype[i] = C; // must be opposite type of S
        } else if (dist[0][S] + dist[S][i] == dist[0][i]) { // station to left of 0
            leftStations.pb({dist[S][i], i});
        } else { // station to right of S
            rightStations.pb({dist[0][i], i});
        }
    }
    sort(leftStations.begin(), leftStations.end());
    sort(rightStations.begin(), rightStations.end());
    L = 0;
    R = S;
    for (pii p: leftStations) {
        int t = p.s;
        if (dist[L][t] == 0) dist[L][t] = dist[t][L] = getDistance(L, t);
        int d = dist[S][L] + dist[L][t] - dist[S][t];
        if (stype[block[location[L] + d / 2]] == C) { // station t is type D
            location[t] = location[L] + dist[L][t];
            block[location[t]] = t;
            stype[t] = D;
        } else { // station t is type C
            location[t] = location[S] - dist[S][t];
            block[location[t]] = t;
            stype[t] = C;
            L = t;
        }
    }
    for (pii p: rightStations) {
        int t = p.s;
        if (dist[R][t] == 0) dist[R][t] = dist[t][R] = getDistance(R, t);
        int d = dist[0][R] + dist[R][t] - dist[0][t];
        if (stype[block[location[R] - d / 2]] == D) { // station t is type C
            location[t] = location[R] - dist[R][t];
            block[location[t]] = t;
            stype[t] = C;
        } else { // station t is type D
            location[t] = location[0] + dist[0][t];
            block[location[t]] = t;
            stype[t] = D;
            R = t;
        }
    }
}

int main() {
    int location[_N], stype[_N];
    findLocation(_N, _FIRST, location, stype);
    for (int i = 0; i < _N; i++) {
        printf("%d %d\n", location[i], stype[i]);
    }
    return 0;
}
