/*
 * STNBD4.cpp
 *
 *  Created on: Jun 14, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

using namespace std;

struct Query {
    int l, r, ind;
};

int N, qSize, l, r, Q, arr[100001], BIT[100001];
pair<int, int> A[100001];
Query q[100001];
long long res, ans[100001];

long long rsq(int ind) {
    long long sum = 0;
    for (; ind > 0; ind -= (ind & -ind)) {
        sum += BIT[ind];
    }
    return sum;
}

void update(int ind, long long value) {
    for (; ind <= N; ind += (ind & -ind)) {
        BIT[ind] += value;
    }
}

bool queryCmp(Query q1, Query q2) {
    if (q1.l / qSize != q2.l / qSize) return q1.l < q2.l;
    else return q1.r < q2.r;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i].first);
        A[i].second = i;
    }
    sort(A + 1, A + N + 1);
    for (int i = 1; i <= N; i++) {
        arr[A[i].second] = i;
    }
    scanf("%d", &Q);
    qSize = sqrt(N);
    for (int i = 0; i < Q; i++) {
        scanf("%d%d", &l, &r);
        q[i].l = l;
        q[i].r = r;
        q[i].ind = i;
    }
    sort(q, q + Q, queryCmp);
    l = N + 1;
    r = N;
    res = 0;
    for (int i = 0; i < Q; i++) {
        while (l < q[i].l) {
            res -= rsq(arr[l] - 1);
            update(arr[l], -1);
            l++;
        }
        while (l > q[i].l) {
            l--;
            res += rsq(arr[l] - 1);
            update(arr[l], 1);
        }
        while (r < q[i].r) {
            r++;
            res += r - l - rsq(arr[r]);
            update(arr[r], 1);
        }
        while (r > q[i].r) {
            res -= r - l + 1 - rsq(arr[r]);
            update(arr[r], -1);
            r--;
        }
        ans[q[i].ind] = res;
    }
    for (int i = 0; i < Q; i++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}
