#include <stdio.h>

#define INT_INF 0x3f3f3f3f
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#define _bufferSize 4096
char _buffer[_bufferSize + 1], *_ptr = _buffer, _c;
int _cur, _sign;
double _div;
long _x;
// returns a single character
#define _getchar() (*_ptr ? *_ptr++ : (_buffer[fread(_ptr = _buffer, 1, _bufferSize, stdin)] = '\0', *_ptr++))
// reads the unsigned number and the sign
#define _readSignAndNum(x) do { (x) = _getchar(); } while ((x) <= ' '); _sign = (x) == '-'; if (_sign) (x) = _getchar(); for ((x) -= '0'; (_c = _getchar()) >= '0'; (x) = ((x) << 3) + ((x) << 1) + _c - '0')
// reads a character
#define rc(x) do { do { (x) = _getchar(); } while ((x) <= ' '); } while (0)
// reads an integer/long integer
#define ri(x) do { _readSignAndNum(x); if (_sign) (x) = -(x); } while (0)
// reads a floating point number
#define rd(x) do { _readSignAndNum(_x); (x) = _x; _div = 1.0; if (_c == '.') while ((_c = _getchar()) >= '0') (x) += (_c - '0') / (_div *= 10); if (_sign) (x) = -(x); } while (0)
// reads a token into a c style string
#define rcs(x) do{ _cur = 0; do { _c = _getchar(); } while (_c <= ' '); do { (x)[_cur++] = _c; } while ((_c = _getchar()) > ' '); } while (0)
// reads a line into a c style string
#define rcln(x) do { _cur = 0; do { _c = _getchar(); } while (_c <= ' '); do { (x)[_cur++] = _c; } while ((_c = _getchar()) >= ' '); } while (0)
// sets the maximum length of a string to be read, required only for reading std::string
#define setLength(x) do { if (_buf) delete[](_buf); _buf = new char[(x) + 1]; } while (0)

#define MAXN 50005

int N, Q, TMAX[MAXN * 2], TMIN[MAXN * 2];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ri(N);
    ri(Q);
    int a, b;
    for (int i = 0; i < N; i++) {
        ri(a);
        TMAX[N + i] = TMIN[N + i] = a;
    }
    for (int i = N - 1; i > 0; i--) {
        TMAX[i] = max(TMAX[i << 1], TMAX[i << 1 | 1]);
        TMIN[i] = min(TMIN[i << 1], TMIN[i << 1 | 1]);
    }
    for (int i = 0; i < Q; i++) {
        ri(a);
        ri(b);
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
