#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
#define mid(x, y) (x + (y - x) / 2)
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) (rand() % (b - a + 1) + a)

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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int N, M;
ordered_set T;

int main() {
    ri(N);
    ri(M);
    for (int i = 0; i < N; i++) {
        int x;
        ri(x);
        T.insert({x, i});
    }
    int lastAns = 0;
    for (int i = 0; i < M; i++) {
        char op;
        int x;
        rc(op);
        ri(x);
        x ^= lastAns;
        if (op == 'I') {
            T.insert({x, N + i});
        } else if (op == 'R') {
            auto r = T.lower_bound({x, 0});
            if (r != T.end() && r->f == x) T.erase(r);
        } else if (op == 'S') {
            lastAns = T.find_by_order(x - 1)->f;
            printf("%d\n", lastAns);
        } else if (op == 'L') {
            auto k = T.lower_bound({x, 0});
            lastAns = k != T.end() && k->f == x ? T.order_of_key(*k) + 1 : -1;
            printf("%d\n", lastAns);
        } else {
            i--;
        }
    }
    for (pii x : T) {
        printf("%d ", x.f);
    }
    printf("\n");
    return 0;
}
