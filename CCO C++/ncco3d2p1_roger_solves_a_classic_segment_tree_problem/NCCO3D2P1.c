#include <stdio.h>

#define INT_INF 0x3f3f3f3f
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

#define MAXN 50005

int N, Q, TMAX[MAXN * 2], TMIN[MAXN * 2];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    scan(N);
    scan(Q);
    int a, b;
    for (int i = 0; i < N; i++) {
        scan(a);
        TMAX[N + i] = TMIN[N + i] = a;
    }
    for (int i = N - 1; i > 0; i--) {
        TMAX[i] = max(TMAX[i << 1], TMAX[i << 1 | 1]);
        TMIN[i] = min(TMIN[i << 1], TMIN[i << 1 | 1]);
    }
    for (int i = 0; i < Q; i++) {
        scan(a);
        scan(b);
        int lo = INT_INF, hi = -INT_INF;
        for (a += (N - 1), b += (N - 1); a <= b; a >>= 1, b >>= 1) {
            if (a & 1) {
                hi = max(hi, TMAX[a]);
                lo = min(lo, TMIN[a]);
                a++;
            }
            if (!(b & 1)) {
                hi = max(hi, TMAX[b]);
                lo = min(lo, TMIN[b]);
                b--;
            }
        }
        printf("%d\n", hi - lo);
    }
    return 0;
}
