#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) ((x) << 1)
#define r(x) ((x) << 1 | 1)
#define m(x, y) ((x) + ((y) - (x)) / 2)
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define FILL(a, x) memset((a), (x), sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x);
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<int, float> pif;
typedef pair<float, int> pfi;
typedef pair<double, double> pdd;
typedef pair<int, double> pid;
typedef pair<double, int> pdi;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef pair<llu, llu> pllu;
typedef pair<int, llu> pillu;
typedef pair<llu, int> pllui;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

struct FenwickTreeRangePoint {
private:
    int size;
    int *array;

public:
    FenwickTreeRangePoint(int size) {
        this->size = size;
        array = new int[size + 1];
        for (int i = 0; i <= size; i++) {
            array[i] = 0;
        }
    }

    /**
     * Value at index {@code ind}.
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind index
     * @return sum
     */
    int getValue(int ind) {
        int sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    /**
     * Update the array at ind and all the affected regions above ind.
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind   index
     * @param  value value
     */
    void update(int ind, int value) {
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    /**
     * Update the array between a and b.
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  a left index
     * @param  b right index
     * @param  value value
     */
    void update(int a, int b, int value) {
        update(a, value);
        update(b + 1, -value);
    }

    int getSize() {
        return size;
    }
};

#define MAXN 100010

int N, x, arr[MAXN];
umii ind;
FenwickTreeRangePoint *adj;

int main() {
    ri(N);
    adj = new FenwickTreeRangePoint(N);
    For(i, 1, N + 1) {
        ri(arr[i]);
        ind[arr[i]] = i;
    }
    For(i, 1, N + 1) {
        ri(x);
        arr[ind[x]] = i;
    }
    For(i, 1, N + 1) {
        ind[arr[i]] = i;
    }
    ind[0] = 0;
    pii maxRun = mp(-1, 0);
    pii curRun = mp(0, 1);
    For(i, 1, N + 1) {
        if (ind[i - 1] < ind[i]) curRun.f++;
        else {
            MAX(maxRun, curRun);
            curRun = mp(1, i);
        }
    }
    MAX(maxRun, curRun);
    printf("%d\n", N - maxRun.f);
    Rev(i, maxRun.s - 1, 0) {
        printf("F %d\n", ind[i] + adj->getValue(ind[i]));
        adj->update(1, ind[i] - 1, 1);
    }
    For(i, maxRun.s + maxRun.f, N + 1) {
        printf("B %d\n", ind[i] + adj->getValue(ind[i]));
        adj->update(ind[i] + 1, N, -1);
    }
    return 0;
}
