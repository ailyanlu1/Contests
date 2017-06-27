/*
 * Odd.cpp
 *
 *  Created on: Apr 19, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n = 0;
    int odd = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x = 0;
        scanf("%d", &x);
        odd ^= x;
    }
    printf("%d", odd);
    return 0;
}
