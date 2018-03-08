#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define f first
#define s second
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl "\n"

#define ll long long
#define ld long double
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

struct Edge {
    int a, b;
    ll c;
    bool type;

    bool operator < (const Edge &e) const {
        return c != e.c ? c < e.c : type < e.type;
    }

    bool operator > (const Edge &e) const {
        return c != e.c ? c > e.c : type > e.type;
    }
};

struct UF {
private:
    vector<int> par;
    vector<char> rank;
    int cnt;

public:
    UF(int N) : par(N), rank(N), cnt(N) {
        for (int i = 0; i < N; i++) {
            par[i] = i;
            rank[i] = 0;
        }
    }

    int find(int p) {
        while (p != par[p]) {
            par[p] = par[par[p]];
            p = par[p];
        }
        return p;
    }

    int getCnt() {
        return cnt;
    }

    bool connected(int p, int q) {
        return find(p) == find(q);
    }

    bool join(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return false;
        if (rank[rootP] < rank[rootQ]) par[rootP] = rootQ;
        else if (rank[rootP] > rank[rootQ]) par[rootQ] = rootP;
        else {
            par[rootQ] = rootP;
            rank[rootP]++;
        }
        cnt--;
        return true;
    }
};

int N, M, P, Q;
ll tot = 0LL;
vector<Edge> edges;

ll mst() {
    ll weight = 0LL;
    minpq<Edge> PQ;
    for (Edge e : edges) PQ.push(e);
    UF cities(M), planets(N);
    while (!PQ.empty() && (cities.getCnt() > 1 || planets.getCnt() > 1)) {
        Edge e = PQ.top();
        PQ.pop();
        if (e.type == 0 && cities.join(e.a, e.b)) weight += planets.getCnt() * e.c;
        else if (e.type == 1 && planets.join(e.a, e.b)) weight += cities.getCnt() * e.c;
    }
    return weight;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> P >> Q;
    int a, b;
    ll c;
    FOR(i, P) {
        cin >> a >> b >> c;
        a--; b--;
        tot += c * N;
        edges.pb({a, b, c, 0});
    }
    FOR(i, Q) {
        cin >> a >> b >> c;
        a--; b--;
        tot += c * M;
        edges.pb({a, b, c, 1});
    }
    cout << tot - mst() << nl;
    return 0;
}
