#include <stdio.h>

#define INT_INF 0x3f3f3f3f
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

#define MAXM 10005

int N, M, C, TMAX[2 * MAXM], TMIN[2 * MAXM];

void update(int i, int v) {
    i += M;
    for (TMAX[i] = TMIN[i] = v; i >>= 1;) {
        TMAX[i] = max(TMAX[i << 1], TMAX[i << 1 | 1]);
        TMIN[i] = min(TMIN[i << 1], TMIN[i << 1 | 1]);
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    char ans = 0;
    scan(N);
    scan(M);
    scan(C);
    int a;
    for (int i = 0; i < 2 * M; i++) {
        TMAX[i] = -INT_INF;
        TMIN[i] = INT_INF;
    }
    for (int i = 0; i < N; i++) {
        scan(a);
        update(i % M, a);
        if (i >= M - 1 && TMAX[1] - TMIN[1] <= C) {
            ans = 1;
            printf("%d\n", i - M + 2);
        }
    }
    if (!ans) printf("NONE\n");
    return 0;
}
