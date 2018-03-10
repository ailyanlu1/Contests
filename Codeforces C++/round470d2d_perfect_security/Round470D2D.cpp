// http://codeforces.com/contest/948/problem/D
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

struct Node {
    int cnt = 0;
    Node *child[2];
};

void insert(Node *cur, int val, int d) {
    if (d == -1) return;
    bool v = (val >> d) & 1;
    if (!cur->child[v]) cur->child[v] = new Node();
    cur->child[v]->cnt++;
    insert(cur->child[v], val, d - 1);
}

void findAndRemove(Node *cur, int val, int &xval, int d) {
    if (d == -1) return;
    bool v = (val >> d) & 1;
    if (!cur->child[v] || !(cur->child[v]->cnt)) {
        xval |= 1 << d;
        cur->child[!v]->cnt--;
        findAndRemove(cur->child[!v], val, xval, d - 1);
    } else {
        cur->child[v]->cnt--;
        findAndRemove(cur->child[v], val, xval, d - 1);
    }
}

Node *root = new Node();

int N, A[300005];

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) cin >> A[i];
    int p;
    FOR(i, N) {
        cin >> p;
        insert(root, p, 30);
    }
    FOR(i, N) {
        int ans = 0;
        findAndRemove(root, A[i], ans, 30);
        cout << ans << " \n"[i == N - 1];
    }
    return 0;
}
