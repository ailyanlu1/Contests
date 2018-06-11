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
char _buffer[_bufferSize + 1], *_ptr = _buffer, _c, _sign, *_buf = nullptr;
int _cur;
double _div;
// returns a single character
#define _getchar() (*_ptr ? *_ptr++ : (_buffer[fread(_ptr = _buffer, 1, _bufferSize, stdin)] = '\0', *_ptr++))
// reads the unsigned number and the sign
#define _readSignAndNum(x) do { (x) = _getchar(); } while ((x) <= ' '); _sign = (x) == '-'; if (_sign) (x) = _getchar(); for ((x) -= '0'; (_c = _getchar()) >= '0'; (x) = (x) * 10 + _c - '0')
// reads a character
#define rc(x) do { do { (x) = _getchar(); } while ((x) <= ' '); } while (0)
// reads an integer/long integer
#define ri(x) do { _readSignAndNum(x); if (_sign) (x) = -(x); } while (0)
// reads a floating point number
#define rd(x) do { _readSignAndNum(x); if (_c == '.') for (_div = 1.0; (_c = _getchar()) >= '0'; (x) += (_c - '0') / (_div *= 10)); if (_sign) (x) = -(x); } while (0)
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

#define MAXNL 300005

int N, pre[MAXNL], post[MAXNL], preFreq[MAXNL], postFreq[MAXNL];
string S;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    setLength(MAXNL);
    ri(N);
    FOR(i, MAXNL) pre[i] = post[i] = 0;
    FOR(i, N) {
        rs(S);
        int cur = 0;
        FOR(j, sz(S)) {
            if (S[j] == '(') cur++;
            else {
                if (cur-- == 0) {
                    post[i] = -1;
                    break;
                }
            }
        }
        if (post[i] != -1) {
            post[i] = cur;
            postFreq[cur]++;
        }
        cur = 0;
        REV(j, sz(S) - 1) {
            if (S[j] == ')') cur++;
            else {
                if (cur-- == 0) {
                    pre[i] = -1;
                    break;
                }
            }
        }
        if (pre[i] != -1) {
            pre[i] = cur;
            preFreq[cur]++;
        }
    }
    ll cnt = 0;
    FOR(i, N) cnt += pre[i] >= 0 ? postFreq[pre[i]] : 0;
    printf("%lld\n", cnt);
    return 0;
}
