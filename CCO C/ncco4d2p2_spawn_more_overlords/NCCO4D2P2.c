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
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define uint unsigned int
#define ull unsigned long long
#define ll long long
#define ld long double

#define _bufferSize 4096
#define _maxNumLength 128
char _inputBuffer[_bufferSize + 1],*_inputPtr=_inputBuffer,_c,_sign;int _cur;
#define _peekchar() (*_inputPtr?*_inputPtr:(_inputBuffer[fread(_inputPtr=_inputBuffer,1,_bufferSize,stdin)]='\0',*_inputPtr))
#define _getchar() (*_inputPtr?*_inputPtr++:(_inputBuffer[fread(_inputPtr=_inputBuffer,1,_bufferSize,stdin)]='\0',*_inputPtr++))
#define _hasNext() (*_inputPtr||!feof(stdin))
#define _readSignAndNum(x) do{(x)=_getchar();}while((x)<=' ');_sign=(x)=='-';if(_sign)(x)=_getchar();for((x)-='0';(_c=_getchar())>='0';(x)=(x)*10+_c-'0')
#define _readFloatingPoint(x,T) for(T _div=1.0;(_c=_getchar())>='0';(x)+=(_c-'0')/(_div*=10))
#define rc(x) do{do{(x)=_getchar();}while((x)<=' ');}while(0)
#define ri(x) do{_readSignAndNum(x);if(_sign)(x)=-(x);}while(0)
#define rd(x) do{_readSignAndNum(x);if(_c=='.')_readFloatingPoint(x,double);if(_sign)(x)=-(x);}while(0)
#define rld(x) do{_readSignAndNum(x);if(_c=='.')_readFloatingPoint(x,ld);if(_sign)(x)=-(x);}while(0)
#define rcs(x) do{_cur=0;do{_c=_getchar();}while(_c<=' ');do{(x)[_cur++]=_c;}while((_c=_getchar())>' ');(x)[_cur]='\0';}while(0)
#define rcln(x) do{_cur=0;do{_c=_getchar();}while(_c<=' ');do{(x)[_cur++]=_c;}while((_c=_getchar())>=' ');(x)[_cur]='\0';}while(0)
int hasNext(){while(_hasNext()&&_peekchar()<=' ')_getchar();return _hasNext();}

#define MAXN 105
#define MAXT 10005

int N, T, S[MAXN], U[MAXN], dp1[MAXT], dp2[MAXT], ans = INT_INF;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ri(N);
    ri(T);
    FOR(i, N) ri(S[i]);
    FOR(i, N) ri(U[i]);
    For(i, 1, MAXT) dp1[i] = dp2[i] = INT_INF;
    dp1[0] = dp2[0] = 0;
    FOR(i, N) {
        for (int j = 1; j <= U[i] && j * S[i] < MAXT; j++) Rev(k, MAXT - 1, j * S[i] - 1) MIN(dp1[k], dp1[k - S[i]] + 1);
        For(k, S[i], MAXT) MIN(dp2[k], dp2[k - S[i]] + 1);
    }
    For(i, T, MAXT) MIN(ans, dp1[i] + dp2[i - T]);
    printf("%d\n", ans == INT_INF ? -1 : ans);
    return 0;
}
