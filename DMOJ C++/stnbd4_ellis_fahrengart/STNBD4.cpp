#include <bits/stdc++.h>
using namespace std;

#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define f first
#define s second
#define all(a) (a).begin(), (a).end()
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())

#define uint unsigned int
#define ull unsigned long long
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pill pair<int, ll>
#define plli pair<ll, int>
#define pdd pair<double, double>
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

template<typename T1, typename T2, typename H1 = hash<T1>, typename H2 = hash<T2>>
struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * H1 {}(p.first) + H2 {}(p.second);}};

#define _bufferSize 4096
#define _maxNumLength 128
char _inputBuffer[_bufferSize + 1], *_inputPtr = _inputBuffer, _outputBuffer[_bufferSize], _c, _sign, *_tempInputBuf = nullptr, _numBuf[_maxNumLength], _tempOutputBuf[_maxNumLength], _fill = ' ';
const char* _delimiter = " ";
int _cur, _outputPtr = 0, _numPtr = 0, _precision = 6, _width = 0, _tempOutputPtr = 0, _cnt;
ll _precisionBase = 1000000;
#define _getchar() (*_inputPtr ? *_inputPtr++ : (_inputBuffer[fread(_inputPtr = _inputBuffer, 1, _bufferSize, stdin)] = '\0', *_inputPtr++))
#define _readSignAndNum(x) do { (x) = _getchar(); } while ((x) <= ' '); _sign = (x) == '-'; if (_sign) (x) = _getchar(); for ((x) -= '0'; (_c = _getchar()) >= '0'; (x) = (x) * 10 + _c - '0')
#define _readFloatingPoint(x, T) for (T _div = 1.0; (_c = _getchar()) >= '0'; (x) += (_c - '0') / (_div *= 10))
#define rc(x) do { do { (x) = _getchar(); } while ((x) <= ' '); } while (0)
#define ri(x) do { _readSignAndNum(x); if (_sign) (x) = -(x); } while (0)
#define rd(x) do { _readSignAndNum(x); if (_c == '.') _readFloatingPoint(x, double); if (_sign) (x) = -(x); } while (0)
#define rld(x) do { _readSignAndNum(x); if (_c == '.') _readFloatingPoint(x, ld); if (_sign) (x) = -(x); } while (0)
#define rcs(x) do{ _cur = 0; do { _c = _getchar(); } while (_c <= ' '); do { (x)[_cur++] = _c; } while ((_c = _getchar()) > ' '); (x)[_cur] = '\0'; } while (0)
#define rs(x) do { if (!_tempInputBuf) assert(0); rcs(_tempInputBuf); (x) = string(_tempInputBuf, _cur); } while (0)
#define rcln(x) do { _cur = 0; do { _c = _getchar(); } while (_c <= ' '); do { (x)[_cur++] = _c; } while ((_c = _getchar()) >= ' '); (x)[_cur] = '\0'; } while (0)
#define rln(x) do { if (!_tempInputBuf) assert(0); rcln(_tempInputBuf); (x) = string(_tempInputBuf, _cur); } while (0)
#define setLength(x) do { if (_tempInputBuf) delete[](_tempInputBuf); _tempInputBuf = new char[(x) + 1]; } while (0)
void read(char &x) { rc(x); }
void read(int &x) { ri(x); }
void read(uint &x) { ri(x); }
void read(ll &x) { ri(x); }
void read(ull &x) { ri(x); }
void read(double &x) { rd(x); }
void read(ld &x) { rld(x); }
void read(char* x) { rcs(x); }
void read(string &x) { rs(x); }
template <typename T, typename ...Ts> void read(T &&x, Ts &&...xs) { read(x); read(forward<Ts>(xs)...); }
#define flush() (fwrite(_outputBuffer, 1, _outputPtr, stdout), _outputPtr = 0)
#define _putchar(x) (_outputPtr == _bufferSize ? flush() : _outputBuffer[_outputPtr++] = (x))
#define _writeTempBuf(x) (_tempOutputBuf[_tempOutputPtr++] = (x))
#define _writeOutput() for (int _i = 0; _i < _tempOutputPtr; _putchar(_tempOutputBuf[_i++])); _tempOutputPtr = 0
#define _writeNum(x, T, digits) _cnt = 0; for (T _y = (x); _y; _y /= 10, _cnt++) _numBuf[_numPtr++] = '0' + _y % 10; _flushNumBuf(); for (; _cnt < digits; _cnt++) _writeTempBuf('0')
#define _writeFloatingPoint(x, T) _writeNum((ull) (x), ull, 1); _writeTempBuf('.'); _writeNum(((x) - ((ull) (x))) * _precisionBase + (T) (0.5), ull, _precision)
#define _checkFinite(x) if (isnan(x)) { wcs("NaN"); } else if (isinf(x)) { wcs("Inf"); }
#define _flushNumBuf() for (; _numPtr; _writeTempBuf(_numBuf[--_numPtr]))
#define _fillBuf(x) for (int _i = 0; _i < (x); _i++) _putchar(_fill)
#define _flushTempBuf() int _tempLen = _tempOutputPtr; _fillBuf(_width - _tempLen); _writeOutput(); _fillBuf(-_width - _tempLen)
#define wc(x) do { _writeTempBuf(x); _flushTempBuf(); } while (0)
#define wi(x) do { if ((x) < 0) { _writeTempBuf('-'); _writeNum(-(x), uint, 1); } else { _writeNum(x, uint, 1); } _flushTempBuf(); } while (0)
#define wll(x) do { if ((x) < 0) { _writeTempBuf('-'); _writeNum(-(x), ull, 1); } else { _writeNum(x, ull, 1); } _flushTempBuf(); } while (0)
#define wd(x) do { _checkFinite(x) else if ((x) < 0) { _writeTempBuf('-'); _writeFloatingPoint(-(x), double); } else { _writeFloatingPoint(x, double); } _flushTempBuf(); } while (0)
#define wld(x) do { _checkFinite(x) else if ((x) < 0) { _writeTempBuf('-'); _writeFloatingPoint(-(x), ld); } else { _writeFloatingPoint(x, ld); } _flushTempBuf(); } while (0)
#define wcs(x) do { int _slen = strlen(x); _fillBuf(_width - _slen); for (const char *_p = (x); *_p; _putchar(*_p++)); _fillBuf(-_width - _slen); } while (0)
#define ws(x) do { _fillBuf(_width - (int) (x).length()); for (int _i = 0; _i < (int) (x).length(); _putchar(x[_i++])); _fillBuf(-_width - (int) (x).length()); } while (0)
#define setPrecision(x) do { _precision = (x); _precisionBase = 1; for (int _i = 0; _i < (x); _i++, _precisionBase *= 10); } while (0)
#define setDelimiter(x) do { _delimiter = (x); } while (0)
#define setWidth(x) do { _width = (x); } while (0)
#define setFill(x) do { _fill = (x); } while (0)
void write(char x) { wc(x); }
void write(int x) { wi(x); }
void write(uint x) { wi(x); }
void write(ll x) { wll(x); }
void write(ull x) { wll(x); }
void write(double x) { wd(x); }
void write(ld x) { wld(x); }
void write(const char* x) { wcs(x); }
void write(string &x) { ws(x); }
template <typename T, typename ...Ts> void write(T &&x, Ts &&...xs) { write(x); write(_delimiter); write(forward<Ts>(xs)...); }
void writeln() { write('\n'); }
template <typename ...Ts> void writeln(Ts &&...xs) { write(forward<Ts>(xs)...); write('\n'); }
class IOManager { public: ~IOManager() { flush(); } };
unique_ptr<IOManager> _iomanager(new IOManager());

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
    read(N);
    for (int i = 0; i < N; i++) {
        read(A[i].first);
        A[i].second = i;
    }
    sort(A, A + N);
    for (int i = 1; i <= N; i++) {
        arr[A[i - 1].second] = i;
    }
    read(Q);
    qSize = sqrt(N);
    for (int i = 0; i < Q; i++) {
        read(l, r);
        q[i].l = l - 1;
        q[i].r = r - 1;
        q[i].ind = i;
    }
    sort(q, q + Q, queryCmp);
    l = 0;
    r = -1;
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
        writeln(ans[i]);
    }
    return 0;
}
