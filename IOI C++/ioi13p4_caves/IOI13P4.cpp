/*
 * IOI13P4.cpp
 *
 *  Created on: May 12, 2017
 *      Author: wleung
 */

#include <bits/stdc++.h>
#define MAXN 5001

using namespace std;

int connected[MAXN], switches[MAXN], comb[MAXN], dMap[MAXN];
int tries = 0;
int length;

bool judge(int S[], int D[]) {
    for (int i = 0; i < length; i++) {
        if (S[i] != comb[i]) return false;
    }
    for (int i = 0; i < length; i++) {
        if (i != dMap[D[i]]) return false;
    }
    return true;
}

void answer(int S[], int D[]) {
    for (int i = 0; i < length; i++) {
        printf("%d ", S[i]);
    }
    printf("\n");
    for (int i = 0; i < length; i++) {
        printf("%d ", D[i]);
    }
    printf("\n");
    bool correct = judge(S, D);
    if (correct) printf("AC\n");
    else printf("WA\n");
}

int tryCombination(int S[]) {
    tries++;
    if (tries > 70000) {
        printf("Function call limit exceeded");
        return -1;
    }
    for (int i = 0; i < length; i++) {
        if (S[dMap[i]] != comb[dMap[i]]) return i;
    }
    return -1;
}

void exploreCave(int N) {
    length = N;
    fill(begin(connected), begin(connected) + N, -1);
    fill(begin(switches), begin(switches) + N, 0);
    for (int i = 0; i < N; i++) {
        int c = tryCombination(switches);
        bool open = (i < c || c == -1);
        int low = 0;
        int high = N - 1;
        while (low < high) {
            int mid = (low + high) / 2;
            for (int j = mid + 1; j <= high; j++) {
                if (connected[j] != -1) continue;
                switches[j] = 1 - switches[j];
            }
            int door = tryCombination(switches);
            bool nextOpen = (i < door || door == -1);
            if (open != nextOpen) {
                low = mid + 1;
            } else {
                high = mid;
            }
            open = nextOpen;
        }
        if (!open) switches[low] = 1 - switches[low];
        connected[low] = i;
    }
    answer(switches, connected);
}

void initComb(int N) {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        comb[i] = rand() % 2;
    }
    for (int i = 0; i < N; i++) {
        dMap[i] = i;
    }
    for (int i = N-1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(dMap[i], dMap[j]);
    }
}

int main() {
    int N;
    scanf("%d", &N);
    initComb(N);
    exploreCave(N);
    return 0;
}
