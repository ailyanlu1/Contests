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

#define MAXNM 100005

struct Node {
    unordered_map<char, Node*> child;
    int cnt = 0, prefixCnt = 0;

    Node() {};
    Node(Node *n) : child(n->child), cnt(n->cnt), prefixCnt(n->prefixCnt) {};
};

Node *nodes[MAXNM];

Node *insert(Node *root, string &s) {
    Node *newRoot = new Node(root);
    Node *cur = newRoot;
    for (char c : s) {
        if (cur->child.count(c)) cur = cur->child[c] = new Node(cur->child[c]);
        else cur = cur->child[c] = new Node();
        cur->prefixCnt++;
    }
    cur->cnt++;
    return newRoot;
}

int query(Node *root, string &s) {
    int ret = 0;
    Node *cur = root;
    for (char c : s) {
        if (cur->child.count(c)) {
            cur = cur->child[c];
            ret += cur->cnt;
        } else return ret;
    }
    return ret + cur->prefixCnt - cur->cnt;
}

int N, M;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    nodes[0] = new Node();
    string S;
    For(i, 1, N + 1) {
        cin >> S;
        nodes[i] = insert(nodes[i - 1], S);
    }
    int l, r;
    For(i, 1, M + 1) {
        cin >> S >> l >> r;
        cout << query(nodes[r], S) - query(nodes[l - 1], S) << nl;
    }
    return 0;
}
