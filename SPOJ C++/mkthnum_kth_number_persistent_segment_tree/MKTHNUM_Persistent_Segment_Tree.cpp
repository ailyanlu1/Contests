// http://www.spoj.com/problems/MKTHNUM/
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

#define MAXN 100005

int N, M, A[MAXN], oriVal[MAXN], L[20 * MAXN], R[20 * MAXN], VAL[20 * MAXN], nodes[MAXN], curNode = 0;
pii B[MAXN];

int build(int cL, int cR) {
    if (cL == cR) {
        VAL[++curNode] = 0;
        return curNode;
    }
    int m = cL + (cR - cL) / 2;
    int k = ++curNode;
    L[k] = build(cL, m);
    R[k] = build(m + 1, cR);
    VAL[k] = VAL[L[k]] + VAL[R[k]];
    return k;
}

int update(int cur, int cL, int cR, int ind, int val) {
    if (cL > ind || cR < ind) return cur;
    if (cL == cR) {
        VAL[++curNode] = VAL[cur] + val;
        return curNode;
    }
    int m = cL + (cR - cL) / 2;
    int k = ++curNode;
    L[k] = update(L[cur], cL, m, ind, val);
    R[k] = update(R[cur], m + 1, cR, ind, val);
    VAL[k] = VAL[L[k]] + VAL[R[k]];
    return k;
}

int query(int curA, int curB, int cL, int cR, int k) {
    if (cL == cR) return cL;
    int m = cL + (cR - cL) / 2;
    int x = VAL[L[curA]] - VAL[L[curB]];
    if (k <= x) return query(L[curA], L[curB], cL, m, k);
    else return query(R[curA], R[curB], m + 1, cR, k - x);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    For(i, 1, N + 1) {
        cin >> A[i];
        B[i] = {A[i], i};
    }
    sort(B + 1, B + N + 1);
    For(i, 1, N + 1) {
        A[B[i].s] = i;
        oriVal[i] = B[i].f;
    }
    nodes[0] = build(1, N);
    For(i, 1, N + 1) nodes[i] = update(nodes[i - 1], 1, N, A[i], 1);
    int l, r, k;
    FOR(i, M) {
        cin >> l >> r >> k;
        cout << oriVal[query(nodes[r], nodes[l - 1], 1, N, k)] << nl;
    }
    return 0;
}
