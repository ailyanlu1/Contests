/*
 * COCI15C2P5.cpp
 *
 *  Created on: May 26, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAXN 1000000

using namespace std;

struct FenwickTree {
private:
    long long* array;
    int _size;

public:
    FenwickTree(int size) {
        this->_size = size;
        array = new long long[size];
    }

    long long rsq(int ind) {
        long long sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    long long rsq(int a, int b) {
        return rsq(b) - rsq(a - 1);
    }

    void update(int ind, long long value) {
        for (int x = ind; x <= _size; x += (x & -x)) {
            array[x] += value;
        }
    }

    int size() {
        return _size;
    }
};

int N, P;
long long ans;
pair<long long, int> arr[MAXN + 1];
FenwickTree ft(MAXN + 1);

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int a;
        scanf("%d", &a);
        arr[i] = make_pair(a, i);
    }
    scanf("%d", &P);
    for (int i = 1; i <= N; i++) {
        arr[i].first += arr[i - 1].first - P;
    }
    sort(arr, arr + N + 1);
    for (int i = 0; i <= N; i++) {
        ans += ft.rsq(arr[i].second + 1);
        ft.update(arr[i].second + 1, 1);
    }
    printf("%lld", ans);
    return 0;
}
