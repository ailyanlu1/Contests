#include <stdio.h>

char _buffer[(1 << 12) + 1], *_ptr = _buffer, _c;
int _cur, _sign;
double _div;
long _x;
// returns a single character
#define _getchar() (*_ptr ? *_ptr++ : (_buffer[fread(_ptr = _buffer, 1, 4096, stdin)] = '\0', *_ptr++))
// reads the unsigned number and the sign
#define _readSignAndNum(x) do { (x) = _getchar(); } while ((x) <= ' '); _sign = (x) == '-'; if (_sign) (x) = _getchar(); for ((x) -= '0'; (_c = _getchar()) >= '0'; (x) = ((x) << 3) + ((x) << 1) + _c - '0')
// reads a character
#define rc(x) do { do { (x) = _getchar(); } while ((x) <= ' '); } while (0)
// reads an integer/long integer
#define ri(x) do { _readSignAndNum(x); if (_sign) (x) = -(x); } while (0)
// reads a floating point number
#define rd(x) do { _readSignAndNum(_x); (x) = _x; _div = 1.0; if (_c == '.') while ((_c = _getchar()) >= '0') (x) += (_c - '0') / (_div *= 10); if (_sign) (x) = -(x); } while (0)
// reads a token into a c style string
#define rcs(x) do{ _cur = 0; do { _c = _getchar(); } while (_c <= ' '); do { (x)[_cur++] = _c; } while ((_c = _getchar()) > ' '); (x)[_cur] = '\0'; } while (0)
// reads a line into a c style string
#define rcln(x) do { _cur = 0; do { _c = _getchar(); } while (_c <= ' '); do { (x)[_cur++] = _c; } while ((_c = _getchar()) >= ' '); (x)[_cur] = '\0'; } while (0)
// sets the maximum length of a string to be read, required only for reading std::string
#define setLength(x) do { if (_buf) delete[](_buf); _buf = new char[(x) + 1]; } while (0)

#define MAXM 10005

int N, M, C, minA[MAXM], minB[MAXM], maxA[MAXM], maxB[MAXM], minFirst, minLast, maxFirst, maxLast;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ri(N);
    ri(M);
    ri(C);
    minFirst = minLast = maxFirst = maxLast = -1;
    char ans = 0;
    int a;
    for (int i = 0; i < M - 1; i++) {
        ri(a);
        while (minFirst != -1 && minB[minLast] >= a) {
            if (minFirst == minLast) minFirst = minLast = -1;
            else if (minLast == 0) minLast = M - 1;
            else minLast--;
        }
        while (maxFirst != -1 && maxB[maxLast] <= a) {
            if (maxFirst == maxLast) maxFirst = maxLast = -1;
            else if (maxLast == 0) maxLast = M - 1;
            else maxLast--;
        }
        if (minFirst == -1) minFirst = minLast = 0;
        else if (minLast == M - 1) minLast = 0;
        else minLast++;
        if (maxFirst == -1) maxFirst = maxLast = 0;
        else if (maxLast == M - 1) maxLast = 0;
        else maxLast++;
        minA[minLast] = maxA[maxLast] = i;
        minB[minLast] = maxB[maxLast] = a;
    }
    for (int i = M - 1; i < N; i++) {
        ri(a);
        while (minFirst != -1 && minA[minFirst] <= i - M) {
            if (minFirst == minLast) minFirst = minLast = -1;
            else if (minFirst == M - 1) minFirst = 0;
            else minFirst++;
        }
        while (maxFirst != -1 && maxA[maxFirst] <= i - M) {
            if (maxFirst == maxLast) maxFirst = maxLast = -1;
            else if (maxFirst == M - 1) maxFirst = 0;
            else maxFirst++;
        }
        while (minFirst != -1 && minB[minLast] >= a) {
            if (minFirst == minLast) minFirst = minLast = -1;
            else if (minLast == 0) minLast = M - 1;
            else minLast--;
        }
        while (maxFirst != -1 && maxB[maxLast] <= a) {
            if (maxFirst == maxLast) maxFirst = maxLast = -1;
            else if (maxLast == 0) maxLast = M - 1;
            else maxLast--;
        }
        if (minFirst == -1) minFirst = minLast = 0;
        else if (minLast == M - 1) minLast = 0;
        else minLast++;
        if (maxFirst == -1) maxFirst = maxLast = 0;
        else if (maxLast == M - 1) maxLast = 0;
        else maxLast++;
        minA[minLast] = maxA[maxLast] = i;
        minB[minLast] = maxB[maxLast] = a;
        if (maxB[maxFirst] - minB[minFirst] <= C) {
            ans = 1;
            printf("%d\n", i - M + 2);
        }
    }
    if (!ans) printf("NONE\n");
    return 0;
}
