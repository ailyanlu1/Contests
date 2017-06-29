/*
 * CCC17S5_Sqrt.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair

using namespace std;

#define MAX 150001
#define SIZE 400

int N, M, Q, L[MAX], A[MAX], cur[MAX], ind[MAX], SQRT[MAX / SIZE], RHT[MAX][SIZE];
vector<int> lines[MAX];

inline int val(int i) {
    return A[lines[L[i]][(ind[i] + cur[L[i]]) % lines[L[i]].size()]];
}

int main() {
    scanf("%d%d%d", &N, &M, &Q);
    memset(RHT, -1, sizeof RHT);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &L[i]);
        lines[L[i]].pb(i);
        ind[i] = lines[L[i]].size() - 1;
        RHT[L[i]][i / SIZE] = i;
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        SQRT[i / SIZE] += A[i];
    }
    int type, l, r, x, ans;
    for (int q = 0; q < Q; q++) {
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d%d", &l, &r);
            ans = 0;
            if (r - l < SIZE) {
                for (int i = l; i <= r; i++) {
                    ans += val(i);
                }
            } else {
                while (l % SIZE) {
                    ans += val(l);
                    l++;
                }
                while (l + SIZE <= r) {
                    ans += SQRT[l / SIZE];
                    l += SIZE;
                }
                while (l <= r) {
                    ans += val(l);
                    l++;
                }
            }
            printf("%d\n", ans);
        } else {
            scanf("%d", &x);
            int start = -1;
            int prev = 0;
            for (int i = 0; i < SIZE; i++) {
                int rt = RHT[x][i];
                if (rt == -1) continue;
                if (start == -1) start = i;
                SQRT[i] += prev;
                prev = val(rt);
                SQRT[i] -= prev;
            }
            SQRT[start] += prev;
            cur[x] = (cur[x] + lines[x].size() - 1) % lines[x].size();
        }
    }
    return 0;
}
