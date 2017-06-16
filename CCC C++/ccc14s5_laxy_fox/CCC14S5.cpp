
/*
 * CCC14S5.cpp
 *
 *  Created on: May 14, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>
#define MAXN 2000

using namespace std;

struct point {
    int x;
    int y;
    point(int x, int y) {
        this -> x = x;
        this -> y = y;
    }
};

struct path {
    int i;
    int j;
    int dist;
    path(int i, int j, int dist) {
        this -> i = i;
        this -> j = j;
        this -> dist = dist;
    }
};

bool compare (path p1, path p2) {
    return p2.dist > p1.dist;
}

int N;
vector<point> points;
vector<path> paths;
int best[MAXN + 1];
int prevBest[MAXN + 1];
int prevDist[MAXN + 1];

int main() {
    scanf("%d", &N);
    points.push_back(point(0, 0));
    for (int i = 1; i <= N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        points.push_back(point(x, y));
    }
    for (int i = 0; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            int dx = points[j].x - points[i].x;
            int dy = points[j].y - points[i].y;
            paths.push_back(path(i, j, dx * dx + dy * dy));
        }
    }
    sort(paths.begin(), paths.end(), compare);
    for (int x = 0; x < N * (N + 1) / 2; x++) {
        int i = paths[x].i;
        int j = paths[x].j;
        int dist = paths[x].dist;
        if (dist != prevDist[i]) {
            prevDist[i] = dist;
            prevBest[i] = best[i];
        }
        if (dist != prevDist[j]) {
            prevDist[j] = dist;
            prevBest[j] = best[j];
        }
        if (i == 0) {
            best[i] = max(best[i], prevBest[j]);
        } else {
            best[i] = max(best[i], prevBest[j] + 1);
            best[j] = max(best[j], prevBest[i] + 1);
        }
    }
    printf("%d\n", best[0] + 1);
    return 0;
}
