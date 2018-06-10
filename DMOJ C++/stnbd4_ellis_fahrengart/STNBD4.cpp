#include <bits/stdc++.h>

using namespace std;

char _buffer[(1 << 12) + 1], *_ptr = _buffer, _c;
int _cur;
bool _sign;
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
    ri(N);
    for (int i = 0; i < N; i++) {
        ri(A[i].first);
        A[i].second = i;
    }
    sort(A, A + N);
    for (int i = 1; i <= N; i++) {
        arr[A[i - 1].second] = i;
    }
    ri(Q);
    qSize = sqrt(N);
    for (int i = 0; i < Q; i++) {
        ri(l);
        ri(r);
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
        printf("%lld\n", ans[i]);
    }
    return 0;
}
