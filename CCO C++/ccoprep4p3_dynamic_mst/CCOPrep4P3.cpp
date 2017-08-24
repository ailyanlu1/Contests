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

struct UF {
private:
    int* parent;
    int* vis;
    int stamp;
    char* rank; // equivalent to byte

    void prop(int p) {
        if (vis[p] != stamp) {
            vis[p] = stamp;
            parent[p] = p;
        }
    }

public:

    UF(int n) {
        parent = new int[n];
        vis = new int[n];
        rank = new char[n];
        stamp = 0;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            vis[i] = -1;
            rank[i] = 0;
        }
    }

    void reset() {
        stamp++;
    }

    int find(int p) {
        prop(p);
        return parent[p] == p ? p : parent[p] = find(parent[p]);
    }

    bool join(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return false;

        // make root of smaller rank point to root of larger rank
        if      (rank[rootP] < rank[rootQ]) parent[rootP] = rootQ;
        else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootP;
        else {
            parent[rootQ] = rootP;
            rank[rootP]++;
        }
        return true;
    }
};

#define MAXMQ 50005
#define FACTOR 1.0

int N, M, Q, x[MAXMQ], y[MAXMQ], z[MAXMQ], k[MAXMQ], d[MAXMQ];

int flag[MAXMQ];
int ind[MAXMQ];
int curFlag;
UF *uf1, *uf2;
set<pair<int, int>> small, large;

void offlineDynamicMST() {
    uf1 = new UF(N);
    uf2 = new UF(N);
    curFlag = 0;
    int cnt;
    ll forest, mst;
    for (int l = 0, b = (int) (sqrt(Q) * FACTOR), r; l < Q; l += b) {
        r = min(l + b - 1, Q - 1);
        curFlag++;
        uf1->reset();
        small.clear();
        for (int i = l; i <= r; i++) {
            flag[k[i]] = curFlag;
            uf1->join(x[k[i]], y[k[i]]);
            small.insert({z[k[i]], k[i]});
        }
        cnt = 0;
        uf2->reset();
        for (pair<int, int> p : large) {
            if (flag[p.s] != curFlag) {
                if (uf2->join(x[p.s], y[p.s])) ind[cnt++] = p.s;
            }
        }
        uf2->reset();
        forest = 0LL;
        for (int i = 0; i < cnt; i++) {
            if (uf1->join(x[ind[i]], y[ind[i]])) {
                uf2->join(x[ind[i]], y[ind[i]]);
                forest += z[ind[i]];
            } else {
                small.insert({z[ind[i]], ind[i]});
            }
        }
        for (int i = l; i <= r; i++) {
            large.erase({z[k[i]], k[i]});
            small.erase({z[k[i]], k[i]});
            z[k[i]] = d[i];
            large.insert({z[k[i]], k[i]});
            small.insert({z[k[i]], k[i]});
            uf1->reset();
            mst = 0LL;
            for (pair<int, int> p : small) {
                if (uf1->join(uf2->find(x[p.s]), uf2->find(y[p.s]))) {
                    mst += z[p.s];
                }
            }
            printf("%lld\n", forest + mst);
        }
    }
}

int main() {
    ri(N);
    ri(M);
    ri(Q);
    for (int i = 0; i < M; i++) {
        ri(x[i]); x[i]--;
        ri(y[i]); y[i]--;
        ri(z[i]);
        large.insert({z[i], i});
    }
    for (int i = 0; i < Q; i++) {
        ri(k[i]); k[i]--;
        ri(d[i]);
    }
    offlineDynamicMST();
    return 0;
}
