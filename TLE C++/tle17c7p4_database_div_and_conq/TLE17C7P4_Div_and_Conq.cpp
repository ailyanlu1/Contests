#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
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

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXNS 200005

struct Node {
    Node *prev, *next;
    int i;
    ll hash;

    Node (int i, ll h) : prev(nullptr), next(nullptr), i(i), hash(h) {}
};

bool ltI(const Node *a, const Node *b) {
    return a->i < b->i;
}

bool ltHash(const Node *a, const Node *b) {
    return a->hash < b->hash;
}

string S;
int N, Q, ind[MAXNS];
char ans[MAXNS];
vector<Node*> T[MAXNS];
vector<pair<int, char>> updates;
vector<pair<int, pii>> queries;

bool ltInd(const pair<int, pii> &a, const pair<int, pii> &b) {
    return ind[a.s.f] < ind[b.s.f];
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> S >> N;
    FOR(i, sz(S)) {
        Node *cur = new Node(0, S[i]);
        T[i].pb(cur);
        if (i > 0) {
            T[i - 1].back()->next = cur;
            cur->prev = T[i - 1].back();
        }
    }
    int x, y;
    char c;
    For(i, 1, N) {
        cin >> x >> c;
        x--;
        updates.pb({x, c});
        Node *cur = new Node(i, c);
        T[x].pb(cur);
        if (x > 0) cur->prev = T[x - 1].back();
        if (x < sz(S) - 1) cur->next = T[x + 1].back();
    }
    cin >> Q;
    FOR(i, Q) {
        cin >> x >> y;
        x--; y--;
        queries.pb({i, {x, y}});
    }
    FOR(i, sz(S)) {
        sort(all(T[i]), ltHash);
        ll cur = -1, last = -1;
        for (Node *n : T[i]) {
            if (n->hash != last) cur++;
            last = n->hash;
            n->hash = cur;
        }
        sort(all(T[i]), ltI);
    }
    for (int len = 1; len < sz(S); len *= 2) {
        for (int lo = 0; lo < sz(S); lo += len + len) {
            int half = lo + len;
            if (half >= sz(S)) continue;
            vector<Node*> newNodes;
            int i = 0, j = 0, k = 0;
            while (i < sz(T[lo]) && j < sz(T[half])) {
                Node *n = new Node(k, T[lo][i]->hash * ((ll) 1e6) + T[half][j]->hash);
                n->prev = T[lo][i]->prev;
                n->next = T[half][j]->next;
                newNodes.pb(n);
                if (i == sz(T[lo]) - 1) {
                    j++;
                    if (j < sz(T[half])) k = T[half][j]->i;
                } else if (j == sz(T[half]) - 1) {
                    i++;
                    if (i < sz(T[lo])) k = T[lo][i]->i;
                } else if (T[lo][i + 1]->i < T[half][j + 1]->i) {
                    i++;
                    k = T[lo][i]->i;
                } else {
                    j++;
                    k = T[half][j]->i;
                }
            }
            sort(all(newNodes), ltHash);
            ll cur = -1, last = -1;
            for (Node *n : newNodes) {
                if (n->hash != last) cur++;
                last = n->hash;
                n->hash = cur;
            }
            sort(all(newNodes), ltI);
            T[lo] = newNodes;
        }
    }
    int cur = 0;
    sort(all(T[0]), ltHash);
    for (Node *n : T[0]) ind[cur++] = n->i;
    sort(all(queries), ltInd);
    cur = 1;
    for (pair<int, pii> q : queries) {
        while (cur <= ind[q.s.f]) {
            S[updates[cur - 1].f] = updates[cur - 1].s;
            cur++;
        }
        ans[q.f] = S[q.s.s];
    }
    FOR(i, Q) cout << ans[i] << nl;
    return 0;
}
