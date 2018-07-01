#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define For(i, a, b) for (i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define uint unsigned int
#define ull unsigned long long
#define ll long long
#define ld long double

#define _bufferSize 4096
#define _maxNumLength 128
char _inputBuffer[_bufferSize + 1],*_inputPtr=_inputBuffer,_c,_sign;int _cur;
#define _getchar() (*_inputPtr?*_inputPtr++:(_inputBuffer[fread(_inputPtr=_inputBuffer,1,_bufferSize,stdin)]='\0',*_inputPtr++))
#define _readSignAndNum(x) do{(x)=_getchar();}while((x)<=' ');_sign=(x)=='-';if(_sign)(x)=_getchar();for((x)-='0';(_c=_getchar())>='0';(x)=(x)*10+_c-'0')
#define _readFloatingPoint(x,T) for(T _div=1.0;(_c=_getchar())>='0';(x)+=(_c-'0')/(_div*=10))
#define rc(x) do{do{(x)=_getchar();}while((x)<=' ');}while(0)
#define ri(x) do{_readSignAndNum(x);if(_sign)(x)=-(x);}while(0)
#define rd(x) do{_readSignAndNum(x);if(_c=='.')_readFloatingPoint(x,double);if(_sign)(x)=-(x);}while(0)
#define rld(x) do{_readSignAndNum(x);if(_c=='.')_readFloatingPoint(x,ld);if(_sign)(x)=-(x);}while(0)
#define rcs(x) do{_cur=0;do{_c=_getchar();}while(_c<=' ');do{(x)[_cur++]=_c;}while((_c=_getchar())>' ');(x)[_cur]='\0';}while(0)
#define rcln(x) do{_cur=0;do{_c=_getchar();}while(_c<=' ');do{(x)[_cur++]=_c;}while((_c=_getchar())>=' ');(x)[_cur]='\0';}while(0)

#define less(T)\
    int less_##T(const void *a, const void *b) {\
        T aa = *(T*) a;\
        T bb = *(T*) b;\
        if (aa < bb) return -1;\
        else if (aa > bb) return 1;\
        else return 0;\
    }

#define greater(T)\
    int greater_##T(const void *a, const void *b) {\
        T aa = *(T*) a;\
        T bb = *(T*) b;\
        if (aa > bb) return -1;\
        else if (aa < bb) return 1;\
        else return 0;\
    }

#define pair(T1, T2)\
    typedef struct {\
        T1 first;\
        T2 second;\
    } pair_##T1##_##T2;\
    \
    pair_##T1##_##T2 make_pair_##T1##_##T2(T1 first, T2 second) {\
        pair_##T1##_##T2 ret;\
        ret.first = first;\
        ret.second = second;\
        return ret;\
    }

less(ll)
greater(ll)
pair(ll, ll)
#define f first
#define s second
#define mp make_pair_ll_ll
#define pll pair_ll_ll

#define MAXN 100005

int L;
ll A[MAXN], B[MAXN], C[MAXN], front, back;
pll P[MAXN], PP[MAXN], dp[MAXN];

int cmp(const void *a, const void *b) {
    pll aa = *(pll*) a;
    pll bb = *(pll*) b;
    int x = less_ll((const void*) &aa.f, (const void*) &bb.f);
    if (x != 0) return x;
    return greater_ll((const void*) &aa.s, (const void*) &bb.s);
}

void resetConvexHullTrick() {
    front = back = 0;
}

void addLine(ll a, ll b, ll c) {
    while (back >= 2 && (B[back - 2] - B[back - 1]) * (a - A[back - 1]) <= (B[back - 1] - b) * (A[back - 1] - A[back - 2])) back--;
    A[back] = a;
    B[back] = b;
    C[back++] = c;
}

pll getMax(ll x) {
    while (front < back - 1 && A[front + 1] * x + B[front + 1] <= A[front] * x + B[front]) front++;
    return mp(A[front] * x + B[front], C[front]);
}

pll f(ll c) {
    resetConvexHullTrick();
    int i;
    dp[0] = mp(0, 0);
    FOR(i, L) {
        addLine(4 * PP[i].f, 2 * PP[i].f * PP[i].f + dp[i].f, dp[i].s);
        dp[i + 1] = getMax(-PP[i].s);
        dp[i + 1].f += 2 * PP[i].s * PP[i].s + c;
        dp[i + 1].s++;
        if (i < L - 1) dp[i + 1].f -= 2 * max(0, PP[i].s - PP[i + 1].f) * max(0, PP[i].s - PP[i + 1].f);
    }
    return dp[L];
}

ll take_photos(int n, int m, int k, int *r, int *c) {
    int i;
    FOR(i, n) {
        P[i] = mp(min(r[i], c[i]), max(r[i], c[i]));
        P[i].f--;
    }
    qsort(P, n, sizeof(pll), cmp);
    L = 0;
    FOR(i, n) if (L == 0 || PP[L - 1].s < P[i].s) PP[L++] = P[i];
    ll lo = 0, hi = 1LL *  m * m, mid;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (f(mid * 2 + 1).s > k) lo = mid + 1;
        else hi = mid; 
    }
    return f(lo * 2).f / 2 - lo * k;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    int n, m, k;
    ri(n);
    ri(m);
    ri(k);
    int *r = (int*) malloc(sizeof(int) * n);
    int *c = (int*) malloc(sizeof(int) * n);
    int i;
    FOR(i, n) {
        ri(r[i]);
        ri(c[i]);
    }
    printf("%lld\n", take_photos(n, m, k, r, c));
    return 0;
}
