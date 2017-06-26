/*
 * CCO15P6.cpp
 *
 *  Created on: Jun 25, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf("%c", &x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

struct FenwickTree {
private:
    int size;

public:
    int *array;
    FenwickTree(int size) {
        this->size = size;
        array = new int[size + 1];
    }

    /**
     * Range Sum query from 1 to ind
     * ind is 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  ind index
     * @return sum
     */
    int rsq(int ind) {
        ind = min(size, ind);
        int sum = 0;
        for (int x = ind; x > 0; x -= (x & -x)) {
            sum += array[x];
        }
        return sum;
    }

    /**
     * Range Sum Query from a to b.
     * Search for the sum from array index from a to b
     * a and b are 1-indexed
     * <p>
     * Time-Complexity:    O(log(n))
     *
     * @param  a left index
     * @param  b right index
     * @return sum
     */
    int rsq(int a, int b) {
        return rsq(b) - rsq(a - 1);
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
        if (ind == 0) return;
        for (int x = ind; x <= size; x += (x & -x)) {
            array[x] += value;
        }
    }

    int getSize() {
        return size;
    }
};

struct State {
    int col, val;
    State(int col, int val) {
        this->col = col;
        this->val = val;
    }

    bool operator < (const State &s) const {
        return col < s.col;
    }
};

#define MAXN 2500
#define MAXM 100000

int N, M, K, T, grid[MAXN + 2][MAXN + 2];

FenwickTree ft(MAXM);

int main() {
    ri(N);
    ri(K);
    ri(M);
    for (int i = 0; i < M; i++) {
        int S;
        ri(S);
        int R[S];
        int C[S];
        for (int j = 0; j < S; j++) {
            ri(R[j]);
            ri(C[j]);
        }
        for (int j = 1; j < (1 << S); j++) {
            int size = 0, minR = 1, maxR = N, minC = 1, maxC = N;
            for (int k = 0; k < S; k++) {
                if (!(j & 1 << k)) continue;
                size++;
                int up = max(0, R[k] - K + 1);
                int down = R[k];
                int left = max(0, C[k] - K + 1);
                int right = C[k];
                minR = max(minR, up);
                maxR = min(maxR, down);
                minC = max(minC, left);
                maxC = min(maxC, right);
            }
            if (minR <= maxR && minC <= maxC) {
                maxR++;
                maxC++;
                int inc = (size % 2) * 2 - 1;
                grid[minR][minC] += inc;
                grid[minR][maxC] -= inc;
                grid[maxR][minC] -= inc;
                grid[maxR][maxC] += inc;
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            grid[i][j] += grid[i - 1][j] + grid[i][j - 1] - grid[i - 1][j - 1];
        }
    }
    vector<set<State>> rows(N + 1);
    for (int i = 1; i <= N - K + 1; i++) {
        for (int j = 1; j <= N - K + 1; j++) {
            if (grid[i][j]) {
                ft.update(grid[i][j], 1);
                rows[i].insert(State(j, grid[i][j]));
            }
        }
    }
    ri(T);
    for (int t = 0; t < T; t++) {
        int type;
        ri(type);
        if (type == 1) {
            int A, B;
            ri(A);
            ri(B);
            int up = max(1, A - K + 1);
            int down = min (N - K + 1, A);
            int left = max(1, B - K + 1);
            int right = min(N - K + 1, B);
            for (int i = down; i >= up; i--) {
                auto iter = rows[i].lower_bound(State(left, 0));
                while (iter != rows[i].end() && iter->col <= right) {
                    ft.update(iter->val, -1);
                    iter = rows[i].erase(iter);
                }
            }
        } else {
            int V;
            ri(V);
            printf("%.6f\n", (double) (ft.rsq(V, MAXM)) / ((N - K + 1) * (N - K + 1)));
        }
    }
    return 0;
}
