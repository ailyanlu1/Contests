
/*
 * IOI01P1.cpp
 *
 *  Created on: May 13, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>
#define MAXN 1025

using namespace std;

int arr[MAXN][MAXN];
int c, N, x, y, a, l, b, r, t;

int rsq(int indX, int indY) {
    int sum = 0;
    for (int x = indX; x > 0; x -= (x & -x)) {
        for (int y = indY; y > 0; y -= (y & -y)) {
            sum += arr[x][y];
        }
    }
    return sum;
}

int rsq(int x1, int y1, int x2, int y2) {
    return rsq(x2, y2) + rsq(x1 - 1, y1 - 1) - rsq(x1 - 1, y2) - rsq(x2, y1 - 1);
}

void update(int indX, int indY, int value) {
    for (int x = indX; x <= N; x += (x & -x)) {
        for (int y = indY; y <= N; y += (y & -y)) {
            arr[x][y] += value;
        }
    }
}

int main() {
    scanf("%d", &c);
    while(c != 3) {
        if (c == 1) {
            scanf("%d%d%d", &x, &y, &a);
            update(x + 1, y + 1, a);
        } else if (c == 2) {
            scanf("%d%d%d%d", &l, &b, &r, &t);
            printf("%d\n", rsq(l + 1, b + 1, r + 1, t + 1));
        } else {
            scanf("%d", &N);
        }
        scanf("%d", &c);
    }
    return 0;
}
