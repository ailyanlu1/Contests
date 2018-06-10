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
char _buffer[_bufferSize + 1], *_ptr = _buffer, _c, *_buf = nullptr;
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
#define rcs(x) do{ _cur = 0; do { _c = _getchar(); } while (_c <= ' '); do { (x)[_cur++] = _c; } while ((_c = _getchar()) > ' '); (x)[_cur] = '\0'; } while (0)
// reads a token into a std::string
#define rs(x) do { if (!_buf) assert(0); rcs(_buf); (x) = string(_buf, _cur); } while (0)
// reads a line into a c style string
#define rcln(x) do { _cur = 0; do { _c = _getchar(); } while (_c <= ' '); do { (x)[_cur++] = _c; } while ((_c = _getchar()) >= ' '); (x)[_cur] = '\0'; } while (0)
// reads a line into a std::string
#define rln(x) do { if (!_buf) assert(0); rcln(_buf); (x) = string(_buf, _cur); } while (0)
// sets the maximum length of a string to be read, required only for reading std::string
#define setLength(x) do { if (_buf) delete[](_buf); _buf = new char[(x) + 1]; } while (0)

#define MAXN 10
#define MAXPROD 10000000

int N, Q, BIT[MAXPROD], L[MAXN], sufProd[MAXN], A[MAXN], B[MAXN];
unsigned char ARR[MAXPROD];

void init() {
    int prod = 1;
    for (int i = N - 1; i >= 0; i--) {
        sufProd[i] = prod;
        prod *= L[i];
    }
}

int rsq(int curDim, int pos) {
    int sum = 0;
    if (curDim == N) {
        sum += BIT[pos];
    } else {
        for (int i = B[curDim]; i > 0; i -= (i & -i)) {
            sum += rsq(curDim + 1, pos + (i - 1) * sufProd[curDim]);
        }
        for (int i = A[curDim] - 1; i > 0; i -= (i & -i)) {
            sum -= rsq(curDim + 1, pos + (i - 1) * sufProd[curDim]);
        }
    }
    return sum;
}

void update(int curDim, int pos, int value) {
    if (curDim == N) {
        BIT[pos] += value;
    } else {
        for (int i = A[curDim]; i <= L[curDim]; i += (i & -i)) {
            update(curDim + 1, pos + (i - 1) * sufProd[curDim], value);
        }
    }
}

//void generate();

int main() {
//    generate();
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
//    const auto start_time = chrono::system_clock::now();
    ri(N);
    ri(Q);
    FOR(i, N) ri(L[i]);
    init();
    int op, pos, x;
    FOR(q, Q) {
        ri(op);
        if (op == 1) {
            pos = 0;
            FOR(i, N) {
                ri(A[i]);
                pos += (A[i] - 1) * sufProd[i];
            }
            ri(x);
            update(0, 0, x - ARR[pos]);
            ARR[pos] = x;
        } else if (op == 2) {
            FOR(i, N) ri(A[i]);
            FOR(i, N) ri(B[i]);
            printf("%d\n", rsq(0, 0));
        } else {
            q--;
        }
    }
//    double time_elapsed = ((chrono::system_clock::now() - start_time).count() / static_cast<double>(chrono::system_clock::period::den));
//    fprintf(stderr, "Completed in %.3f seconds.\n", time_elapsed);
    return 0;
}
