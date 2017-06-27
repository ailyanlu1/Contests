/*
 * CCO10P3.cpp
 *
 *  Created on: Apr 25, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

using namespace std;

#define SIZE 1000002

int N;
int num = 0;
char c[SIZE];
int X[SIZE];
int R[SIZE];
int K[SIZE];
int idToRating[SIZE];
int ratingToId[SIZE];
vector<int> ratings;
long long FenwickTree[SIZE];
unordered_map<int, int> ratingMap;

long long rsq(int ind) {
    long long sum = 0;
    while (ind > 0) {
        sum += FenwickTree[ind];
        ind -= ind & (-ind);
    }
    return sum;
}

void update(int ind, int value) {
    while (ind < SIZE) {
        FenwickTree[ind] += value;
        ind += ind & (-ind);
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%c", &c[i]);
        if (c[i] == 'N' || c[i] == 'M') {
            scanf("%d %d", &X[i], &R[i]);
            ratings.push_back(R[i]);
        } else if (c[i] == 'Q'){
            scanf("%d", &K[i]);
        } else {
            i--;
        }
    }
    sort(ratings.begin(), ratings.end());
    for (int i = 0; i < ratings.size(); i++) {
        ratingMap[ratings[i]] = i + 1;
    }
    for (int i = 0; i < N; i++) {
        if (c[i] == 'N') {
            idToRating[X[i]] = ratingMap[R[i]];
            ratingToId[ratingMap[R[i]]] = X[i];
            update(ratingMap[R[i]], 1);
            num++;
        } else if (c[i] == 'M') {
            // no need to remove old ratingToId reference
            update(idToRating[X[i]], -1);
            update(ratingMap[R[i]], 1);
            idToRating[X[i]] = ratingMap[R[i]];
            ratingToId[ratingMap[R[i]]] = X[i];
        } else {
            int lo = 1;
            int hi = ratings.size();
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (rsq(mid) > num - K[i]) {
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            printf("%d\n", ratingToId[lo]);
        }
    }
}
