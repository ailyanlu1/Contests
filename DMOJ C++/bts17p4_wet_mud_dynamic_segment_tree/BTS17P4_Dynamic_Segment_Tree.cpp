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

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

struct DynamicSegmentTree {
    struct Node {
        Node *left = nullptr, *right = nullptr;
        int val = INT_MAX;
    };

private:
    Node *root;
    int N;

    void update(Node *cur, int cL, int cR, int ind, int val) {
        if (cL > ind || cR < ind) return;
        if (cL >= ind && cR <= ind) {
           cur->val = val;
           return;
        }
        int m = cL + (cR - cL) / 2;
        if (cur->left == nullptr) cur->left = new Node();
        update(cur->left, cL, m, ind, val);
        if (cur->right == nullptr) cur->right = new Node();
        update(cur->right, m + 1, cR, ind, val);
        cur->val = min(cur->left->val, cur->right->val);
    }

    pii query(Node *cur, int cL, int cR, int l, int r) {
        if (cur == nullptr || cL > r || cR < l) return mp(INT_MAX, l);
        if (cL >= l && cR <= r) return mp(cur->val, l);
        int m = cL + (cR - cL) / 2;
        pii left = query(cur->left, cL, m, l, r);
        pii right = query(cur->right, m + 1, cR, l, r);
        return min(left, right);
    }

public:
    DynamicSegmentTree(int size) {
        root = new Node();
        N = size;
    }

    void update(int ind, int val) {
        update(root, 1, N, ind, val);
    }

    pii query(int l, int r) {
        return query(root, 1, N, l, r);
    }

    int size() {
        return N;
    }
};

#define MAXN 100005
#define MAXT 1000005

int N, M, J, p, t, tToP[MAXT], pToT[MAXN];
set<int> times;
DynamicSegmentTree *st;

int main() {
    cin >> N >> M >> J;
    st = new DynamicSegmentTree(N);
    FOR(i, M) {
        cin >> p >> t;
        st->update(p, t);
        tToP[t] = p;
        pToT[p] = t;
        times.insert(t);
    }
    int curPos = 0, curTime = 0;
    pii q;
    auto iter = times.begin();
    while (curPos + J <= N) {
        q = st->query(curPos + 1, min(curPos + J, N));
        if (q.f == INT_MAX) {
            cout << -1 << nl;
            return 0;
        }
        MAX(curTime, q.f);
        curPos = q.s;
        while (*iter < curTime) {
            st->update(pToT[*(iter++)], 0);
        }
    }
    cout << curTime << nl;
    return 0;
}
