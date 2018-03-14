#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define all(a) (a).begin(), (a).end()
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

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

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXN 200005

char rnk[MAXN];
int N, M, Q, V[MAXN], par[MAXN];

int find(int p) {
    while (p != par[p]) p = par[p] = par[par[p]];
    return p;
}

void join(int p, int q) {
    p = find(p);
    q = find(q);
    if (p == q) return;
    if (rnk[p] < rnk[q]) par[p] = q;
    else if (rnk[p] > rnk[q]) par[q] = p;
    else {
        par[q] = p;
        rnk[p]++;
    }
}

struct Node {
    int i;
    Node *child[2] = {nullptr, nullptr};
};

void connect(Node *cur, int i, int val, int d) {
    bool v = (val >> d) & 1;
    bool x = (M >> d) & 1;
    if ((cur->child[!(v ^ x)] && x)) join(cur->child[!(v ^ x)]->i, i);
    if (d == 0 && cur->child[v ^ x]) join(cur->child[v ^ x]->i, i);
    if (d > 0 && cur->child[v ^ x]) connect(cur->child[v ^ x], i, val, d - 1);
}

void insert(Node *cur, int i, int val, int d) {
    bool v = (val >> d) & 1;
    if (!cur->child[v]) cur->child[v] = new Node();
    if (d == 0) cur->child[v]->i = i;
    else insert(cur->child[v], i, val, d - 1);
    cur->i = cur->child[v]->i;
}

Node *root = new Node();

void test() {
    N = 200000, Q = 200000;
    const int MAXVAL = (int) min((ll) N * (ll) N, (ll) 1e9);
    pii QS[Q];
    bool QA[Q];
    mt19937 rng(time(0));
    M = rng() % (MAXVAL + 1);
    FOR(i, N) V[i] = rng() % (MAXVAL + 1);
    FOR(i, Q) {
        QS[i].f = rng() % N + 1;
        QS[i].s = rng() % N + 1;
    }
    if (N <= 5005) {
        FOR(i, N) {
            par[i] = i;
            rnk[i] = 0;
        }
        FOR(i, N) FOR(j, i) if ((V[i] ^ V[j]) <= M) join(i, j);
        FOR(i, Q) QA[i] = find(QS[i].f - 1) == find(QS[i].s - 1);
    }
    const auto start_time = chrono::system_clock::now();
    FOR(i, N) {
        par[i] = i;
        rnk[i] = 0;
    }
    FOR(i, N) {
        connect(root, i, V[i], 30);
        insert(root, i, V[i], 30);
    }
    if (N <= 5005) FOR(i, Q) assert(QA[i] == (find(QS[i].f - 1) == find(QS[i].s - 1)));
    else FOR(i, Q) QA[i] = (find(QS[i].f - 1) == find(QS[i].s - 1));
    const auto end_time = chrono::system_clock::now();
    cerr << "Time Elasped: " << ((end_time - start_time).count() / static_cast<double>(chrono::system_clock::period::den)) << " sec" << endl;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    bool isTest = true;
    if (isTest) {
        test();
        return 0;
    }
    cin >> N >> M >> Q;
    FOR(i, N) {
        par[i] = i;
        rnk[i] = 0;
    }
    if (N <= 5005) {
        FOR(i, N) {
            cin >> V[i];
            FOR(j, i) if ((V[i] ^ V[j]) <= M) join(i, j);
        }
    } else {
        int vi;
        FOR(i, N) {
            cin >> vi;
            connect(root, i, vi, 30);
            insert(root, i, vi, 30);
        }
    }
    int p, q;
    FOR(i, Q) {
        cin >> p >> q;
        cout << (find(p - 1) == find(q - 1) ? "YES" : "NO") << nl;
    }
    return 0;
}
