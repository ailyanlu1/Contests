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

struct Node {
    Node *left = nullptr, *right = nullptr;
    char c = 0;
    ll hash1 = 0, hash2 = 0;

    Node() {}
    Node(Node *left, Node *right) : left(left), right(right) {}
};

#define MAXNS 200005
#define BASE1 ((ll) 10007)
#define MOD1 ((ll) 1e9 + 7)
#define BASE2 ((ll) 137)
#define MOD2 ((ll) 1e9 + 9)

vector<Node*> roots;
int N, Q;
ll POW1[MAXNS], POW2[MAXNS];
string S;

Node *build(int cL, int cR) {
    if (cL == cR) {
        Node *n = new Node();
        n->c = n->hash1 = n->hash2 = S[cL];
        return n;
    }
    int m = cL + (cR - cL) / 2;
    Node *n = new Node(build(cL, m), build(m + 1, cR));
    n->hash1 = (n->left->hash1 * POW1[cR - m] + n->right->hash1) % MOD1;
    n->hash2 = (n->left->hash2 * POW2[cR - m] + n->right->hash2) % MOD2;
    return n;
}

Node *update(Node *cur, int cL, int cR, int ind, char val) {
    if (cL == cR) {
        Node *n = new Node();
        n->c = n->hash1 = n->hash2 = val;
        return n;
    }
    int m = cL + (cR - cL) / 2;
    Node *n = new Node(cur->left, cur->right);
    if (ind <= m) n->left = update(cur->left, cL, m, ind, val);
    else n->right = update(cur->right, m + 1, cR, ind, val);
    n->hash1 = (n->left->hash1 * POW1[cR - m] + n->right->hash1) % MOD1;
    n->hash2 = (n->left->hash2 * POW2[cR - m] + n->right->hash2) % MOD2;
    return n;
}

bool query(const Node *cur, const Node *cur2, int cL, int cR) {
    if (cL == cR) return cur->c < cur2->c;
    int m = cL + (cR - cL) / 2;
    if (cur->left->hash1 != cur2->left->hash1 || cur->left->hash2 != cur2->left->hash2) return query(cur->left, cur2->left, cL, m);
    else return query(cur->right, cur2->right, m + 1, cR);
}

char at(const Node *cur, int cL, int cR, int ind) {
    if (cL == cR) return cur->c;
    int m = cL + (cR - cL) / 2;
    if (ind <= m) return at(cur->left, cL, m, ind);
    else return at(cur->right, m + 1, cR, ind);
}

bool cmp(const Node *a, const Node *b) {
    return query(a, b, 0, sz(S) - 1);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> S >> N;
    POW1[0] = POW2[0] = 1;
    For(i, 1, sz(S)) {
        POW1[i] = POW1[i - 1] * BASE1 % MOD1;
        POW2[i] = POW2[i - 1] * BASE2 % MOD2;
    }
    roots.pb(build(0, sz(S) - 1));
    int x, y;
    char c;
    For(i, 1, N) {
        cin >> x >> c;
        x--;
        roots.pb(update(roots.back(), 0, sz(S) - 1, x, c));
    }
    sort(all(roots), cmp);
    cin >> Q;
    FOR(i, Q) {
        cin >> x >> y;
        x--; y--;
        cout << at(roots[x], 0, sz(S) - 1, y) << nl;
    }
    return 0;
}
