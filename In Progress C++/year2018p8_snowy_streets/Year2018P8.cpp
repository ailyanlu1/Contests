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

template<typename T1, typename T2, typename H1 = hash<T1>, typename H2 = hash<T2>>
struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * H1 {}(p.first) + H2 {}(p.second);}};

#define MAXR 55
#define MAXC 2005
#define MAXQ 100005

int R, C, Q, TIME[MAXR][MAXC], SZ[MAXR * MAXC], PAR[MAXR * MAXC];
ll K, BIT[MAXR][MAXC];
pii ORD[MAXR * MAXC];
vector<int> updates;
stack<pair<pii, pii>> history;

struct Query {
    int t, x1, y1, x2, y2;
    ll val;
} q[MAXQ];

bool cmpTime(const pii &a, const pii &b) {
    return TIME[a.f][a.s] > TIME[b.f][b.s];
}

ll getValue(int indX, int indY) {
    indX++;
    indY++;
    ll sum = 0;
    for (int x = indX; x > 0; x -= x & -x) {
        for (int y = indY; y > 0; y -= y & -y) {
            sum += BIT[x][y];
        }
    }
    return sum;
}

void update(int indX, int indY, ll value) {
    indX++;
    indY++;
    for (int x = indX; x <= R; x += x & -x) {
        for (int y = indY; y <= C; y += y & -y) {
            BIT[x][y] += value;
        }
    }
}

void update(int x1, int y1, int x2, int y2, ll value) {
    update(x1, y1, value);
    update(x1, y2 + 1, -value);
    update(x2 + 1, y1, -value);
    update(x2 + 1, y2 + 1, value);
}

int find(int p) {
    while (p != PAR[p]) p = PAR[p] = PAR[PAR[p]];
    return p;
}

void join(int p, int q, int t) {
    p = find(p);
    q = find(q);
    if (p == q) return;
    if (SZ[p] > SZ[q]) swap(p, q);
    history.push({{p, q}, {PAR[p], t}});
    PAR[p] = q;
    SZ[q] += SZ[p];
}

void undo() {
    int p = history.top().f.f;
    int q = history.top().f.s;
    int parP = history.top().s.f;
    history.pop();
    PAR[p] = parP;
    SZ[q] -= SZ[p];
}

void addEdge(int x1, int y1, int x2, int y2) {
    if (0 <= x2 && x2 < R && 0 <= y2 && y2 < C && TIME[x1][y1] <= TIME[x2][y2]) join(x1 * C + y1, x2 * C + y2, TIME[x1][y1]);
}

void findTime(vector<pair<pii, ll>> &ind, int cL, int cR) {
    if (cL == cR) {
        for (pair<pii, ll> p : ind) TIME[p.f.f][p.f.s] = updates[cL];
        return;
    }
    int m = cL + (cR - cL) / 2;
    vector<pair<pii, ll>> left, right;
    For(i, cL, m + 1) {
        int j = updates[i];
        update(q[j].x1, q[j].y1, q[j].x2, q[j].y2, q[j].val);
    }
    for (pair<pii, ll> p : ind) {
        ll v = getValue(p.f.f, p.f.s);
        if (p.s + v >= K) left.pb(p);
        else right.pb({p.f, p.s + v});
    }
    For(i, cL, m + 1) {
        int j = updates[i];
        update(q[j].x1, q[j].y1, q[j].x2, q[j].y2, -q[j].val);
    }
    findTime(left, cL, m);
    findTime(right, m + 1, cR);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> R >> C >> K >> Q;
    FOR(i, Q) {
        cin >> q[i].t;
        if (q[i].t == 1) {
            cin >> q[i].x1 >> q[i].y1 >> q[i].x2 >> q[i].y2 >> q[i].val;
            q[i].x1--; q[i].y1--; q[i].x2--; q[i].y2--;
            updates.pb(i);
        } else {
            cin >> q[i].x1 >> q[i].y1 >> q[i].x2 >> q[i].y2;
            q[i].x1--; q[i].y1--; q[i].x2--; q[i].y2--;
        }
    }
    FOR(i, R + 1) FOR(j, C + 1) BIT[i][j] = 0;
    vector<pair<pii, ll>> toCheck;
    for (int i : updates) update(q[i].x1, q[i].y1, q[i].x2, q[i].y2, q[i].val);
    FOR(i, R) {
        FOR(j, C) {
            if (getValue(i, j) >= K) toCheck.pb({{i, j}, 0});
            else TIME[i][j] = Q;
        }
    }
    for (int i : updates) update(q[i].x1, q[i].y1, q[i].x2, q[i].y2, -q[i].val);
    findTime(toCheck, 0, sz(updates) - 1);
    FOR(i, R * C) {
        PAR[i] = i;
        SZ[i] = 1;
        ORD[i] = {i / C, i % C};
    }
    FOR(i, R) {
        FOR(j, C) cout << TIME[i][j] << sp;
        cout << nl;
    }
    sort(ORD, ORD + (R * C), cmpTime);
    FOR(i, R * C) {
        addEdge(ORD[i].f, ORD[i].s, ORD[i].f + 1, ORD[i].s);
        addEdge(ORD[i].f, ORD[i].s, ORD[i].f - 1, ORD[i].s);
        addEdge(ORD[i].f, ORD[i].s, ORD[i].f, ORD[i].s + 1);
        addEdge(ORD[i].f, ORD[i].s, ORD[i].f, ORD[i].s - 1);
    }
    FOR(i, Q) {
        while (!history.empty() && history.top().s.s <= i) undo();
        if (q[i].t == 2) {
            if (find(q[i].x1 * C + q[i].y1) == find(q[i].x2 * C + q[i].y2)) cout << "yes" << nl;
            else cout << "no" << nl;
        }
    }
    return 0;
}
